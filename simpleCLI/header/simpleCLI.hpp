#pragma once

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