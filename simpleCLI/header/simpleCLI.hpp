#pragma once


//    _____ _                 _       _____ _      _____        __   ___        
//   / ____(_)               | |     / ____| |    |_   _|      /_ | / _ \       
//  | (___  _ _ __ ___  _ __ | | ___| |    | |      | |   __   _| || | | |__  __
//   \___ \| | '_ ` _ \| '_ \| |/ _ \ |    | |      | |   \ \ / / || | | |\ \/ /
//   ____) | | | | | | | |_) | |  __/ |____| |____ _| |_   \ V /| || |_| | >  < 
//  |_____/|_|_| |_| |_| .__/|_|\___|\_____|______|_____|   \_/ |_(_)___(_)_/\_\
//                     | |                                                      
//                     |_|                                                                             
//  simpleCLI: A simple command line interface parser for C++
                       
                       
#include "externalLibraries.hpp" // #INCLUDE: externalLibraries.hpp, Header

#define PURE_VIRTUAL 0

#ifdef SIMPLE_CLI_HEADER_ONLY
    #define SIMPLE_CLI_INLINE inline
#else
    #define SIMPLE_CLI_INLINE
#endif // SIMPLE_CLI_HEADER_ONLY
    


// #NAMESPACE: simpleCLI, Project Namespace
namespace simpleCLI{

    inline namespace errors{
        struct Error;
    } // #END: errors

    // #NAMESPACE: arguments, Inline Module Namespace
    inline namespace arguments{
        class Argument;
        class Flaggable;
        class Bindable;
        class Callable;
        template<class T_Bind> class Option;
        template<class T_Bind> class RepeatableOption;
        template<class T_Bind> class VariadicOption;
        template<class T_Call> class Command;
        template<class T_Bind> class Positional;
        template<class T_Bind> class Program;
    } // #END: arguments

    // #NAMESPACE: parser, Inline Module Namespace
    inline namespace parser{
        class Parser;
    } // #END: parser

} // #END: simpleCLI