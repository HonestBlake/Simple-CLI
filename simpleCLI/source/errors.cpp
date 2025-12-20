#include "errors.hpp" // #INCLUDE: errors.hpp, Module Header

namespace simpleCLI::errors{ // #SCOPE: errors

// #SCOPE: Error

// #DIV: Public Factory Methods

    // #FUNCTION: Error(const Type, const std::string&), Public Constructor
    Error::Error(const Type p_type, const std::string& p_body): type(p_type), body(p_body){

    } // #END: Error(const Type, const std::string&)

    // #FUNCTION: Error(const Type), Public Constructor
    Error::Error(const Type p_type): type(p_type){

    } // #END: Error(const Type)

// DIV: Public Methods

    // #FUNCTION: message(), Public Method
    std::string Error::message(){
        switch(type){
            case Type::REPEATED_TAG: {
                return "Repeated Tag: " + body;
            }case Type::INVALID_TAG: {
                return "Invalid Tag: " + body;
            }case Type::CONVERSION_FAILURE: {
                return "Failure To Convert \"" + body + "\" From String To Desired Type";
            }case Type::CHAR_CONVERSION_FAILURE: {
                return "Failure To Convert \"" + body + "\" From String To char";
            }case Type::INT_CONVERSION_FAILURE: {
                return "Failure To Convert \"" + body + "\" From String To int";
            }case Type::FLOAT_CONVERSION_FAILURE: {
                return "Failure To Convert \"" + body + "\" From String To float";
            }case Type::NULL_BIND_OR_CONVERTER: {
                return "Null Bind or Converter When Binding Value From: " + body;
            }case Type::NULL_CALLBACK: {
                return "Null Callback When Invoking Callback For: " + body;
            }case Type::INVALID_COMMAND_LINE: {
                return "Invalid Or Empty Command Line";
            }case Type::EMPTY_OPTION_TAG: {
                return "No Option Tag Provided On Inline Assignment: " + body;
            }case Type::EMPTY_OPTION_VALUE: {
                return "No Option Value Provided On Inline Assignment: " + body;
            }case Type::NO_VALUE_PROVIDED: {
                return "No Value Provided For Option: " + body;
            }case Type::NOT_BINDABLE: {
                return "Tried To Bind On Not-Bindable Argument Type";
            }case Type::NOT_FLAGGABLE: {
                return "Tried To Flag On Not-Flaggable Argument Type";
            }case Type::NOT_CALLABLE: {
                return "Tried To Call On Not-Callable Argument Type";
            }case Type::INVALID_VALUE: {
                return "Invalid Value Provided: " + body;
            }case Type::ARGUMENT_DOES_NOT_TAKE_VALUE: {
                return "Argument That Does Not Take Value Given Inline Assignment: " + body;
            }case Type::POSITIONALS_NOT_SUPPORTED: {
                return "Positional Argument \"" + body + "\" Passed But No Positional Support Configured";
            }case Type::INVALID_INLINE_ASSIGNMENT: {
                return "Option Given A Tag As Value On Inline Assignment: " + body;
            }default: {
                return "Unknown Error";
            }
        }
    } // #END: message()

// #END: Error

} // #END: errors