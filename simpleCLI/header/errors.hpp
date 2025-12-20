#pragma once

#include "simpleCLI.hpp" // #INCLUDE: simpleCLI.hpp, Project Header

namespace simpleCLI::errors{ // #SCOPE: errors

    // #STRUCT: Error, Final Struct
    struct Error final{
    // Types
        enum class Type: std::uint8_t;
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

    // #ENUM: Error::Type, std::uint8_t Enum Class
    enum class Error::Type: std::uint8_t{
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
    }; // #END: Error::Type

} // #END: errors
