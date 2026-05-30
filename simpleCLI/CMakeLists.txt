function(move_global_module_fragment_to_top input output)
    file(READ "${input}" source)

    # Module builds need the global module fragment to be the first token.
    string(REGEX REPLACE "(^|\n)[ \t]*module[ \t]*;[^\n]*(\n|$)" "\\1" source "${source}")

    get_filename_component(output_dir "${output}" DIRECTORY)
    file(MAKE_DIRECTORY "${output_dir}")
    file(WRITE "${output}" "module;\n\n${source}")

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${input}")
endfunction()

set(SIMPLE_CLI_SOURCE_DIR "${SIMPLE_CLI}")
set(SIMPLE_CLI_HEADER_DIR "${SIMPLE_CLI}")

set(SIMPLE_CLI_IMPLEMENTATION_FILES
    "${SIMPLE_CLI}/arguments.cpp"
    "${SIMPLE_CLI}/errors.cpp"
    "${SIMPLE_CLI}/parser.cpp"
)

set(SIMPLE_CLI_MODULE_FILES
    "${SIMPLE_CLI}/simpleCli.mpp"
    "${SIMPLE_CLI}/arguments.mpp"
    "${SIMPLE_CLI}/errors.mpp"
    "${SIMPLE_CLI}/parser.mpp"
)

if(SIMPLE_CLI_USE_MODULES)
    set(SIMPLE_CLI_MODULE_SOURCE_FILES)

    foreach(SOURCE_FILE IN LISTS SIMPLE_CLI_IMPLEMENTATION_FILES)
        get_filename_component(SOURCE_NAME "${SOURCE_FILE}" NAME)
        set(MODULE_SOURCE_FILE "${CMAKE_CURRENT_BINARY_DIR}/module-mode/${SOURCE_NAME}")

        move_global_module_fragment_to_top("${SOURCE_FILE}" "${MODULE_SOURCE_FILE}")
        list(APPEND SIMPLE_CLI_MODULE_SOURCE_FILES "${MODULE_SOURCE_FILE}")
    endforeach()

    add_library(SimpleCLI STATIC ${SIMPLE_CLI_MODULE_SOURCE_FILES})
    target_compile_definitions(SimpleCLI PRIVATE SIMPLE_CLI_USE_MODULES=1)
    target_include_directories(SimpleCLI PRIVATE "${SIMPLE_CLI_HEADER_DIR}")

    set_source_files_properties(${SIMPLE_CLI_MODULE_FILES} PROPERTIES LANGUAGE CXX)

    target_sources(SimpleCLI
        PUBLIC
            FILE_SET cxx_modules
            TYPE CXX_MODULES
            BASE_DIRS "${SIMPLE_CLI_SOURCE_DIR}"
            FILES ${SIMPLE_CLI_MODULE_FILES}
    )

    set_target_properties(SimpleCLI PROPERTIES CXX_SCAN_FOR_MODULES ON)
else()
    add_library(SimpleCLI STATIC ${SIMPLE_CLI_IMPLEMENTATION_FILES})
    set_target_properties(SimpleCLI PROPERTIES CXX_SCAN_FOR_MODULES OFF)
endif()

target_include_directories(SimpleCLI PUBLIC
    "${INCLUDE}"
    "${SIMPLE_CLI_HEADER_DIR}"
)

target_compile_features(SimpleCLI PUBLIC cxx_std_23)

if(SIMPLE_CLI_USE_MODULES)
    set(SIMPLE_CLI_OUTPUT_NAME "simpleCli-modules")
else()
    set(SIMPLE_CLI_OUTPUT_NAME "simpleCli")
endif()

set_target_properties(SimpleCLI PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${ROOT_DIR}/lib/$<LOWER_CASE:$<CONFIG>>"
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "${SIMPLE_CLI_OUTPUT_NAME}"
    PREFIX ""
    SUFFIX ".lib"
)
