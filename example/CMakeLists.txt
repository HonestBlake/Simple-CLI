
add_executable(Example "argumentParser.cpp")
target_link_libraries(Example PRIVATE SimpleCLI)
set_target_properties(Example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE})