add_executable(Example
    "${EXAMPLE}/argumentParser.cpp"
)

target_link_libraries(Example PRIVATE SimpleCLI)

if(SIMPLE_CLI_USE_MODULES)
    target_compile_definitions(Example PRIVATE SIMPLE_CLI_USE_MODULES=1)
    set_target_properties(Example PROPERTIES CXX_SCAN_FOR_MODULES ON)
else()
    set_target_properties(Example PROPERTIES CXX_SCAN_FOR_MODULES OFF)
endif()

if(SIMPLE_CLI_USE_MODULES)
    set(SIMPLE_CLI_EXAMPLE_OUTPUT_NAME "example-modules")
else()
    set(SIMPLE_CLI_EXAMPLE_OUTPUT_NAME "example")
endif()

set_target_properties(Example PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${EXAMPLE}/bin/$<LOWER_CASE:$<CONFIG>>"
    OUTPUT_NAME "${SIMPLE_CLI_EXAMPLE_OUTPUT_NAME}"
)
