#pragma once

#if defined(SIMPLE_CLI_USE_MODULES) && defined(INCLUDED_BY_MODULE)
    #define MODULE_EXPORT export
#else
    #include "simpleCli.hpp" // #INCLUDE: simpleCli.hpp, Project Header
    #define MODULE_EXPORT
#endif

namespace simpleCli{ // #SCOPE: simpleCli

    // #STRUCT: Error, Final Struct
    MODULE_EXPORT struct Error final{
    // Types
        enum class Type: std::uint8_t{
            REPEATED_TAG,
            INVALID_TAG,
            CONVERSION_FAILURE,
            CHAR_CONVERSION_FAILURE,
            INT_CONVERSION_FAILURE,
            FLOAT_CONVERSION_FAILURE,
            NULL_BIND_OR_CONVERTER,
            NULL_CALLBACK,
            INVALID_COMMAND_LINE,
            EMPTY_OPTION_TAG,
            EMPTY_OPTION_VALUE,
            NO_VALUE_PROVIDED,
            NOT_BINDABLE,
            NOT_FLAGGABLE,
            NOT_CALLABLE,
            INVALID_VALUE,
            ARGUMENT_DOES_NOT_TAKE_VALUE,
            POSITIONALS_NOT_SUPPORTED,
            INVALID_INLINE_ASSIGNMENT
        };
    // Factory Methods
        Error() = default;
        Error(const Type p_type, const std::string& p_body);
        Error(const Type p_type);
    // Static Methods
        std::string message();
    // Members
        Type type;
        std::string body;
    }; // #END: Error

} // #END: simpleCli

#undef MODULE_EXPORT
