#include <simpleCLI/parser.hpp>

#include <iostream>

class A{

};

std::expected<A, simpleCLI::Error> myConverter(const std::string& str){
    A a;
    return a;
}

int main(int argc, char** argv){

    std::function<void()> helpCallback = [](){
        std::cout << "Help called!" << std::endl;
        // Help called!
    };
    bool bind = true;

    simpleCLI::Parser parser;
    
    if(auto result = parser.addFlag({"-h", "--help"}, bind, helpCallback); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    std::string optionValue;
    if(auto result = parser.addOption({"-o", "--option"}, optionValue); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    A aValue;
    if(auto result = parser.addOption<A>({"--a-value"}, aValue, &myConverter); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    int bindInt;
    if(auto result = parser.addOption<int>({"-i", "--int"}, bindInt); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    std::vector<std::string> binds;
    if(auto result = parser.addVariadicOption<std::string>({"-s", "--strings"}, binds); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    if(auto result = parser.parse(argc, argv); !result){
        std::cout << result.error().message() << std::endl;
        return 1;
    }

    std::cout << "Bind int: " << bindInt << std::endl;
    std::cout << "Bind: " << bind << std::endl;
    std::cout << "Option Value: " << optionValue << std::endl;
    std::cout << "Strings: ";
    for(const std::string& str: binds){
        std::cout << str << " ";
    }

    return 0;
}   