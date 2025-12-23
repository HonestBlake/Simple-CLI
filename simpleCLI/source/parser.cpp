#include "parser.hpp" // #INCLUDE: parser.hpp, Module Header
#include "arguments.hpp"
#include <expected>
#include <memory>

#include <iostream>

namespace simpleCLI::parser{ // #SCOPE: parser

// #SCOPE: Parser

// #DIV: Public Methods

    // #FUNCTION: parse(), Const Method
    std::expected<bool, Error> Parser::parse(const int argc, char** const argv)const{
        if(argc < 1 || argv == nullptr){ // Empty or invalid command line
            return std::unexpected<Error>({Error::Type::INVALID_COMMAND_LINE});
        }
        if(argc == 1){ // No arguments provided
            return false;
        }
        // Handle Program Name
        if(m_program){
            if(auto result = bind(m_program, std::string(argv[0])); !result){
                return std::unexpected<Error>(result.error());
            }
        }
        std::vector<std::string> commandLine = std::vector<std::string>(argv + 1, argv + argc);
        if(auto result = preprocess(commandLine); !result){
            return std::unexpected<Error>(result.error());
        }
        bool previousTakesValue = false;
        std::string previousTag = "";
        for(const std::string& arg: commandLine){
            if(auto argument = getArgument(arg)){ // Is a known tag
                if(previousTakesValue && m_arguments.at(previousTag)->type() != Argument::Type::VARIADIC_OPTION){ // Previous was option that was not given a value
                    return std::unexpected<Error>({Error::Type::NO_VALUE_PROVIDED, previousTag});
                }
                if(argument->type() == Argument::Type::FLAG){ // Is flag
                    if(auto result = flag(argument); !result){
                        return std::unexpected<Error>(result.error());
                    }
                }
                previousTag = arg;
                previousTakesValue = argument->takesValue();
            }else if(previousTakesValue){ // Previous was option taking value
                if(auto argument = getArgument(previousTag)){ // Previous is known tag
                    if(auto result = bind(argument, arg); !result){
                        return std::unexpected<Error>(result.error());
                    }
                    if(argument->type() != Argument::Type::VARIADIC_OPTION){
                        previousTakesValue = false; 
                    }
                }
            }else{ // Is positional
                if(m_positionals){
                    if(auto result = bind(m_positionals, arg); !result){
                        return std::unexpected<Error>(result.error());
                    }
                }else{
                    return std::unexpected<Error>({Error::Type::POSITIONALS_NOT_SUPPORTED, arg});
                }
            }
        }
        if(previousTakesValue && m_arguments.at(previousTag)->type() != Argument::Type::VARIADIC_OPTION){ // Previous was option that was not given a value
            return std::unexpected<Error>({Error::Type::NO_VALUE_PROVIDED, previousTag});
        }
        return true; // Successfully parsed arguments
    } // #END: parse()

    // #FUNCTION: addFlag(const std::initializer_list<std::string_view>, bool&), Method
    std::expected<void, Error> Parser::addFlag(const std::initializer_list<std::string_view> p_tags, bool& p_bind){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Flag>(&p_bind);
        }
        return {};
    } // #END: addFlag(const std::initializer_list<std::string_view>, bool&)

    // #FUNCTION: addFlag(const std::initializer_list<std::string_view>, const std::function<void()>&), Method
    std::expected<void, Error> Parser::addFlag(const std::initializer_list<std::string_view> p_tags, const std::function<void()>& p_callback){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Flag>(p_callback);
        }
        return {};
    } // #END: addFlag(const std::initializer_list<std::string_view>, const std::function<void()>&)

    // #FUNCTION: addFlag(const std::initializer_list<std::string_view>, std::function<void()>&&), Method
    std::expected<void, Error> Parser::addFlag(const std::initializer_list<std::string_view> p_tags, std::function<void()>&& p_callback){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Flag>(std::move(p_callback));
        }
        return {};
    } // #END: addFlag(const std::initializer_list<std::string_view>, std::function<void()>&&)

    // #FUNCTION: addFlag(const std::initializer_list<std::string_view>, bool&, const std::function<void()>&), Method
    std::expected<void, Error> Parser::addFlag(const std::initializer_list<std::string_view> p_tags, bool& p_bind, const std::function<void()>& p_callback){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Flag>(&p_bind, p_callback);
        }
        return {};
    } // #END: addFlag(const std::initializer_list<std::string_view>, bool&, const std::function<void()>&)

    // #FUNCTION: addFlag(const std::initializer_list<std::string_view>, bool&, std::function<void()>&&), Method
    std::expected<void, Error> Parser::addFlag(std::initializer_list<std::string_view> p_tags, bool& p_bind, std::function<void()>&& p_callback){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Flag>(&p_bind, std::move(p_callback));
        }
        return {};
    } // #END: addFlag(const std::initializer_list<std::string_view>, bool&, std::function<void()>&&)

// #DIV: Private Methods

    // #FUNCTION: isUniqueTag(const std::string_view&), Method
    bool Parser::isUniqueTag(const std::string& p_tag)const{
        return !m_arguments.contains(p_tag);
    } // #END: Private Methods
    
    // #FUNCTION: isValidTag(const std::string_view&), Method
    bool Parser::isValidTag(const std::string& p_tag)const{
        if(p_tag.size() >= LONG_TAG_MIN_SIZE){ // Long Tag
            return p_tag[0] == '-' && p_tag[1] == '-';
        }else if(p_tag.size() == SHORT_TAG_SIZE){ // Short Tag
            return p_tag[0] == '-';
        }else{
            return false;
        }
    } // #END: Private Methods

    // #FUNCTION: isValidValue(const std::string&), Method
    bool Parser::isValidValue(const std::string& p_value)const{
        if(p_value.size() == 1 && p_value[0] == '-'){ // Single dash is not valid value
            return false;
        }
        if(p_value.size() == 2 && p_value[0] == '-'){ // Looks like a short tag
            try{
                std::stoi(p_value);
                return true; // Is a negative single digit number
            }catch(...){
                return false; // Not a valid short tag
            }
        }
        if(p_value[0] == '-' && p_value[1] == '-') return false; // Invalid long tag
        return true;
    } // #END: isValidValue(const std::string&)

    // #FUNCTION: preprocess(std::vector<std::string>&), Const Method
    std::expected<void, Error> Parser::preprocess(std::vector<std::string>& p_commandLine)const{
        for(std::size_t position = 0; position < p_commandLine.size(); position++){
            // Remove empty argument
            if(p_commandLine[position].empty()){ // Is empty arg
                p_commandLine.erase(p_commandLine.begin() + position); // Erase arg
                position--; // Adjust position after erase
                continue;
            }
            // Separate inline value
            if(auto it = p_commandLine[position].find(OPTION_VALUE_SEPARATOR); it != std::string::npos){ // Has inline value
                std::string newTag = p_commandLine[position].substr(0, it); // Extract tag
                std::string newValue = p_commandLine[position].substr(it + 1); // Extract value
                if(auto argument = getArgument(newTag)){ // Known tag with inline assignment
                    if(!argument->takesValue()){ // Tag does not take value
                        return std::unexpected<Error>({Error::Type::ARGUMENT_DOES_NOT_TAKE_VALUE, p_commandLine[position]});
                    }
                    p_commandLine[position] = newTag; // Update tag
                }else{ // Unknown tag with inline assignment
                    if(newTag.empty()){ // Dangling '=' at start
                        return std::unexpected<Error>({Error::Type::EMPTY_OPTION_TAG, p_commandLine[position]});
                    }else{
                        continue; 
                    }
                }
                if(m_arguments.contains(newValue)){ // Value is a tag
                    return std::unexpected<Error>({Error::Type::INVALID_INLINE_ASSIGNMENT, newTag + OPTION_VALUE_SEPARATOR + newValue});
                }
                if(!newValue.empty()){ // Has value
                    p_commandLine.insert(p_commandLine.begin() + position + 1, std::move(newValue)); // Insert value after tag
                }else{ // No value
                    return std::unexpected<Error>({Error::Type::EMPTY_OPTION_VALUE, p_commandLine[position] + OPTION_VALUE_SEPARATOR});
                }
            }
        }
        return {}; // Successful void return
    } // #END: preprocess(std::vector<std::string>&)

    // #FUNCTION: bind(const std::shared_ptr<Argument>, const std::string&), Method
    std::expected<void, Error> Parser::bind(const std::shared_ptr<Argument>& p_bindable, const std::string& p_value)const{
        if(auto bindable = std::dynamic_pointer_cast<Bindable>(p_bindable)){
            if(!isValidValue(p_value)){
                return std::unexpected<Error>({Error::Type::INVALID_VALUE, p_value});
            }
            return bindable->bind(p_value); 
        }else{
            return std::unexpected<Error>({Error::Type::NOT_BINDABLE});
        }
    } // #END: bind(const std::shared_ptr<Argument>, const std::string&)

    // #FUNCTION: bind(const std::unique_ptr<Bindable>, const std::string&), Method
    std::expected<void, Error> Parser::bind(const std::unique_ptr<Bindable>& p_bindable, const std::string& p_value)const{
        if(!isValidValue(p_value)){
            return std::unexpected<Error>({Error::Type::INVALID_VALUE, p_value});
        }
        return p_bindable->bind(p_value); 
    } // #END: bind(const std::unique_ptr<Bindable>, const std::string&)

    // #FUNCTION: flag(const std::shared_ptr<Argument>), Method
    std::expected<void, Error> Parser::flag(const std::shared_ptr<Argument>& p_flaggable)const{
        if(auto flaggable = std::dynamic_pointer_cast<Flaggable>(p_flaggable)){
            flaggable->flag();
            flaggable->callback();
            return {}; // Successful void return
        }else{
            return std::unexpected<Error>({Error::Type::NOT_FLAGGABLE});
        }
    } // #END: flag(const std::shared_ptr<Argument>)

    // #FUNCTION: callback(const std::shared_ptr<Argument>), Method
    std::expected<void, Error> Parser::callback(const std::shared_ptr<Argument>& p_callable)const{
        if(auto callable = std::dynamic_pointer_cast<Callable>(p_callable)){
            callable->callback();
            return {}; // Successful void return
        }else{
            return std::unexpected<Error>({Error::Type::NOT_CALLABLE});
        }
    } // #END: callback(const std::shared_ptr<Argument>)

    // #FUNCTION: getArgument(const std::string&), Const Method
    std::shared_ptr<Argument> Parser::getArgument(const std::string& p_tag)const{
        if(auto it = m_arguments.find(p_tag); it != m_arguments.end()){
            return it->second;
        }
        return nullptr;
    } // #END: getArgument(const std::string&)

// #END: Parser

} // #END: parser