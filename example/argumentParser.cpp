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
