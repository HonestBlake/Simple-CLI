# Package CMake List File

set(SOURCE_FILES 
    "${SIMPLE_CLI}/${SOURCE}/arguments.cpp"
    "${SIMPLE_CLI}/${SOURCE}/parser.cpp"
    "${SIMPLE_CLI}/${SOURCE}/errors.cpp"
)
set(INCLUDE_DIR
    "${ROOT_DIR}/include"
    "${SIMPLE_CLI}/${SOURCE}"
    "${SIMPLE_CLI}/${HEADER}"
)
# Create SimpleCLI static library
add_library(SimpleCLI STATIC)

# Add source and module files
target_sources(SimpleCLI
    PRIVATE ${SOURCE_FILES}
)

# Link include directories
target_include_directories(SimpleCLI 
    PUBLIC ${INCLUDE_DIR}
)

# Set library output properties
set_target_properties(SimpleCLI PROPERTIES
    PREFIX ""
    SUFFIX ".lib"
    OUTPUT_NAME "SimpleCLI"
    ARCHIVE_OUTPUT_DIRECTORY "${SIMPLE_CLI}"
)
