#pragma once

#include "parser.hpp" // #INCLUDE: parser.hpp, Module Header

namespace simpleCLI::parser{ // #SCOPE: parser

// #SCOPE: Parser

// #DIV: Public Methods

    // #FUNCTION: addOption(const std::initializer_list<std::string_view>, T_Bind&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Option<T_Bind>>(&p_bind, p_converter);
        }
        return {}; // #END: addOption(const std::initializer_list<std::string_view>, T_Bind&, const Converter<T_Bind>&)
    } // #END: 

    // #FUNCTION: addOption(const std::initializer_list<std::string_view>, T_Bind&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Option<T_Bind>>(&p_bind, std::move(p_converter));
        }
        return {}; // #END: addOption(const std::initializer_list<std::string_view>, T_Bind&, Converter<T_Bind>&&)
    } // #END: 

    // #FUNCTION: addOption(const std::initializer_list<std::string_view>, T_Bind&, const T_Bind&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const T_Bind& p_default, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Option<T_Bind>>(&p_bind, p_converter);
            p_bind = p_default;
        }
        return {};
    } // #END: addOption(const std::initializer_list<std::string_view>, T_Bind&, const T_Bind&, const Converter<T_Bind>&)

    // #FUNCTION: addOption(const std::initializer_list<std::string_view>, T_Bind&, const T_Bind&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const T_Bind& p_default, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<Option<T_Bind>>(&p_bind, std::move(p_converter));
            p_bind = p_default;
        }
        return {};
    } // #END: addOption(const std::initializer_list<std::string_view>, T_Bind&, const T_Bind&, Converter<T_Bind>&&)

    // #FUNCTION: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<RepeatableOption<T_Bind>>(&p_bind, p_converter);
        }
        return {};
    } // #END: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const Converter<T_Bind>&)

    // #FUNCTION: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<RepeatableOption<T_Bind>>(&p_bind, std::move(p_converter));
        }
        return {};
    } // #END: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, Converter<T_Bind>&&)

    // #FUNCTION: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<RepeatableOption<T_Bind>>(&p_bind, p_converter);
            p_bind = p_default;
        }
        return {};
    } // #END: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, const Converter<T_Bind>&)

    // #FUNCTION: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<RepeatableOption<T_Bind>>(&p_bind, std::move(p_converter));
            p_bind = p_default;
        }
        return {};
    } // #END: addRepeatableOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, Converter<T_Bind>&&)

    // #FUNCTION: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<VariadicOption<T_Bind>>(&p_bind, p_converter);
        }
        return {};
    } // #END: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const Converter<T_Bind>&)

    // #FUNCTION: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<VariadicOption<T_Bind>>(&p_bind, std::move(p_converter));
        }
        return {};
    } // #END: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, Converter<T_Bind>&&)

    // #FUNCTION: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, const Converter<T_Bind>& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<VariadicOption<T_Bind>>(&p_bind, p_converter);
            p_bind = p_default;
        }
        return {};
    } // #END: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, const Converter<T_Bind>&)

    // #FUNCTION: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> std::expected<void, Error> Parser::addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, Converter<T_Bind>&& p_converter){
        for(const std::string_view& tagView: p_tags){
            std::string tag = std::string(tagView);
            if(!isValidTag(tag)) return std::unexpected<Error>({Error::Type::INVALID_TAG, std::move(tag)});
            if(!isUniqueTag(tag)) return std::unexpected<Error>({Error::Type::REPEATED_TAG, std::move(tag)});
            m_arguments[std::move(tag)] = std::make_shared<VariadicOption<T_Bind>>(&p_bind, p_converter);
            p_bind = p_default;
        }
        return {};
    } // #END: addVariadicOption(const std::initializer_list<std::string_view>, std::vector<T_Bind>&, const std::vector<T_Bind>&, Converter<T_Bind>&&)

    // #FUNCTION: addPositional(const std::vector<T_Bind>&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> void Parser::addPositional(std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter){
        m_positionals = std::make_unique<Positional<T_Bind>>(&p_bind, p_converter);
    } // #END: addPositional(const std::vector<T_Bind>&, const Converter<T_Bind>&)

    // #FUNCTION: addPositional(const std::vector<T_Bind>&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> void Parser::addPositional(std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter){
        m_positionals = std::make_unique<Positional<T_Bind>>(&p_bind, std::move(p_converter));
    } // #END: addPositional(const std::vector<T_Bind>&, Converter<T_Bind>&&)

    // #FUNCTION: addProgram(const T_Bind&, const Converter<T_Bind>&), Template Method
    template<class T_Bind> void Parser::addProgram(T_Bind& p_bind, const Converter<T_Bind>& p_converter){
        m_program = std::make_unique<Program<T_Bind>>(&p_bind, p_converter);
    } // #END: addProgram(const T_Bind&, const Converter<T_Bind>&)

    // #FUNCTION: addProgram(const T_Bind&, Converter<T_Bind>&&), Template Method
    template<class T_Bind> void Parser::addProgram(T_Bind& p_bind, Converter<T_Bind>&& p_converter){
        m_program = std::make_unique<Program<T_Bind>>(&p_bind, std::move(p_converter));
    } // #END: addProgram(const T_Bind&, Converter<T_Bind>&&)

// #END: Parser

} // #END: parser