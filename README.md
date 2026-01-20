# Simple CLI

**A lightweight, header-only C++ CLI parser library.**  
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
#include <simpleCLI/parser.hpp>
#include <iostream>

int main(int argc, char** argv) {
    simpleCLI::Parser parser;
    bool showHelp = false;
    parser.addFlag({"-h", "--help"}, showHelp, []() {
        std::cout << "Help called!" << std::endl;
    });

    std::string output;
    parser.addOption({"-o", "--output"}, output);

    int count = 0;
    parser.addOption<int>({"-c", "--count"}, count);

    std::vector<std::string> items;
    parser.addVariadicOption<std::string>({"-i", "--item"}, items);

    if (auto result = parser.parse(argc, argv); !result) {
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    // Use parsed variables...
    std::cout << "Help: " << showHelp << ", Output: " << output << ", Count: " << count << std::endl;
    std::cout << "Items: ";
    for (const auto& item : items) std::cout << item << " ";
    std::cout << std::endl;
    return 0;
}
```

## License

MIT License (see [LICENCE.md](LICENCE.md))

## Acknowledgments

- Inspired by Python's argparse, CLI11, and other modern argument parsers
- Thanks to contributors and users for feedback!
