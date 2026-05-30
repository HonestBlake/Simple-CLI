# Simple CLI

**A lightweight, customizable C++ CLI parser library.**  
Effortlessly handle command-line flags, options, and arguments in C++ with modern, type-safe APIs.

## Features
- **Type-Safe Option Parsing:** Supports automatic conversion of CLI arguments to native types, with custom converters possible for user-defined types.
- **Flexible Flag and Option Handling:** Easily bind variables to flags, single-value options, and variadic (repeatable) options.
- **Callback Support:** Attach actions to flags or options for dynamic handling (e.g., display help).
- **Descriptive Error Reporting:** Informative error messages aid development and debugging.
- **Extensible:** Define converters and integrate with any project structure.

## Getting Started

### Prerequisites
- C++20 or newer compiler GCC, Clang (Both Tested)
- Runs on Windows(Tested), Linux, macOS
- No external libraries required

### Quick Start Example

```cpp
#include <iostream>
#include <string>
#include <vector>

#ifdef SIMPLE_CLI_USE_MODULES
import simpleCli;
#else
#include <simpleCli/simpleCli.hpp>
#endif

int main(int argc, char** argv){
    simpleCli::Parser parser;

    bool showHelp = false;
    std::string output;
    int count = 0;
    std::vector<std::string> items;

    if(auto result = parser.addFlag({"-h", "--help"}, showHelp, [](){
        std::cout << "Help called!" << std::endl;
    }); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    if(auto result = parser.addOption({"-o", "--output"}, output); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    if(auto result = parser.addOption<int>({"-c", "--count"}, count); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    if(auto result = parser.addContinuousOption<std::string>({"-i", "--item"}, items); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    if(auto result = parser.parse(argc, argv); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    std::cout << "Show Help: " << std::boolalpha << showHelp << std::endl;
    std::cout << "Output: " << output << std::endl;
    std::cout << "Count: " << count << std::endl;
    std::cout << "Items: ";
    for(const std::string& item: items){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

Example call:

```powershell
.\example\bin\debug\example.exe -h --output result.txt --count 3 --item alpha beta
```

Example output:

```text
Help called!
Show Help: true
Output: result.txt
Count: 3
Items: alpha beta
```

## CMake Integration

### Header Mode With FetchContent

```cmake
cmake_minimum_required(VERSION 4.0.2)
project(MyApp LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    SimpleCLI
    GIT_REPOSITORY https://github.com/HonestBlake/Simple-CLI.git
    GIT_TAG main
)

set(SIMPLE_CLI_USE_MODULES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SimpleCLI)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE SimpleCLI)
target_compile_features(MyApp PRIVATE cxx_std_23)
```

### Module Mode With FetchContent

```cmake
cmake_minimum_required(VERSION 4.0.2)
project(MyApp LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    SimpleCLI
    GIT_REPOSITORY https://github.com/HonestBlake/Simple-CLI.git
    GIT_TAG main
)

set(SIMPLE_CLI_USE_MODULES ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

FetchContent_MakeAvailable(SimpleCLI)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE SimpleCLI)
target_compile_features(MyApp PRIVATE cxx_std_23)
target_compile_definitions(MyApp PRIVATE SIMPLE_CLI_USE_MODULES=1)
set_target_properties(MyApp PROPERTIES CXX_SCAN_FOR_MODULES ON)
```

### Header Mode With add_subdirectory

```cmake
cmake_minimum_required(VERSION 4.0.2)
project(MyApp LANGUAGES CXX)

set(SIMPLE_CLI_USE_MODULES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/Simple-CLI)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE SimpleCLI)
target_compile_features(MyApp PRIVATE cxx_std_23)
```

### Module Mode With add_subdirectory

```cmake
cmake_minimum_required(VERSION 4.0.2)
project(MyApp LANGUAGES CXX)

set(SIMPLE_CLI_USE_MODULES ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(external/Simple-CLI)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE SimpleCLI)
target_compile_features(MyApp PRIVATE cxx_std_23)
target_compile_definitions(MyApp PRIVATE SIMPLE_CLI_USE_MODULES=1)
set_target_properties(MyApp PROPERTIES CXX_SCAN_FOR_MODULES ON)
```

## Presets

The project includes CMake presets for header and module builds:

```powershell
cmake --fresh --preset Debug
cmake --build --preset Debug

cmake --fresh --preset Release
cmake --build --preset Release

cmake --fresh --preset Debug-Modules
cmake --build --preset Debug-Modules

cmake --fresh --preset Release-Modules
cmake --build --preset Release-Modules
```

`Clangd-Modules` is provided for configuring a module-aware build database for clangd.

## VS Code Tasks

The `.vscode` folder includes tasks for selecting GCC or Clang and configuring CMake. `CMake: Configure` opens the CMake Tools configure preset picker, updates the active CMake preset selection, and runs `cmake --fresh --preset <selected-preset>` with the selected compiler environment.

## Manual Builds And Manual CMake Wiring

### Header Mode

```powershell
cmake -S path/to/Simple-CLI -B path/to/Simple-CLI/build/header -G Ninja -DSIMPLE_CLI_USE_MODULES=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build path/to/Simple-CLI/build/header
```

### Module Mode

Clang requires `module;` to be the first token in each module implementation source. If the implementation `.cpp` files keep includes or conditionals before `module;`, generate build-directory copies with the global module fragment moved to the top:

```cmake
function(move_global_module_fragment_to_top input output)
    file(READ "${input}" source)

    string(REGEX REPLACE "(^|\n)[ \t]*module[ \t]*;[^\n]*(\n|$)" "\\1" source "${source}")

    get_filename_component(output_dir "${output}" DIRECTORY)
    file(MAKE_DIRECTORY "${output_dir}")
    file(WRITE "${output}" "module;\n\n${source}")

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${input}")
endfunction()

set(SIMPLE_CLI_MODULE_SOURCE_FILES)

foreach(SOURCE_FILE IN LISTS SIMPLE_CLI_IMPLEMENTATION_FILES)
    get_filename_component(SOURCE_NAME "${SOURCE_FILE}" NAME)
    set(MODULE_SOURCE_FILE "${CMAKE_CURRENT_BINARY_DIR}/module-mode/${SOURCE_NAME}")

    move_global_module_fragment_to_top("${SOURCE_FILE}" "${MODULE_SOURCE_FILE}")
    list(APPEND SIMPLE_CLI_MODULE_SOURCE_FILES "${MODULE_SOURCE_FILE}")
endforeach()
```

Use the generated implementation `.cpp` files as sources and register `.mpp` files as a C++ module file set:

```cmake
add_library(SimpleCLI STATIC ${SIMPLE_CLI_MODULE_SOURCE_FILES})
target_compile_definitions(SimpleCLI PRIVATE SIMPLE_CLI_USE_MODULES=1)

target_sources(SimpleCLI
    PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        BASE_DIRS "${SIMPLE_CLI_ROOT}/simpleCli"
        FILES ${SIMPLE_CLI_MODULE_FILES}
)
```

C++ module artifacts are compiler and build-directory specific. For module mode, building Simple CLI as part of the consuming CMake build is more reliable than trying to reuse only a prebuilt static library.

Clang is strict about the global module fragment: `module;` must be the first token in a module implementation source. Simple CLI's CMake handles this by generating build-directory copies of `.cpp` files with `module;` moved to the top.

## License

MIT License. See [LICENCE.md](LICENCE.md).
