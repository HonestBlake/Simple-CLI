#pragma once


//    _____ _                 _       _____ _      _____        __   ___        
//   / ____(_)               | |     / ____| |    |_   _|      /_ | / _ \       
//  | (___  _ _ __ ___  _ __ | | ___| |    | |      | |   __   _| || | | |__  __
//   \___ \| | '_ ` _ \| '_ \| |/ _ \ |    | |      | |   \ \ / / || | | |\ \/ /
//   ____) | | | | | | | |_) | |  __/ |____| |____ _| |_   \ V /| || |_| | >  < 
//  |_____/|_|_| |_| |_| .__/|_|\___|\_____|______|_____|   \_/ |_(_)___(_)_/\_\
//                     | |                                                      
//                     |_|                                                                             
//  simpleCli: A simple command line interface parser for C++
                       
                       
#include "stdIncludes.hpp" // #INCLUDE: stdIncludes.hpp, Header


// #NAMESPACE: simpleCli, Project Namespace
namespace simpleCli{

    struct Error;

    class Argument;
    class Flag;
    class Flaggable;
    class Bindable;
    class Callable;
    template<class T_Bind> class Option;
    template<class T_Bind> class RepeatableOption;
    template<class T_Bind> class ContinuousOption;
    template<class T_Call> class Command;
    template<class T_Bind> class Positional;
    template<class T_Bind> class Program;

    class Parser;

} // #END: simpleCli
