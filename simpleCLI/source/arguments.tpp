#pragma once

#include "arguments.hpp" // #INCLUDE: arguments.hpp, Module Header

namespace simpleCLI::arguments{ // #SCOPE: arguments

// #SCOPE: Argument

// #DIV: Public Static Methods

    // #FUNCTION: convert<T_Arg>(const std::string&), Template Method
    template<class T_Arg> std::expected<T_Arg, Error> Argument::convert(const std::string& p_value){
        static_assert(false, "Unsupported type, must provide a conversion function to use this type");
    } // #END: convert<T_Arg>(const std::string&)

    // #FUNCTION: convert<std::string>(const std::string&), Inline Specialized Template Method
    template<> inline std::expected<std::string, Error> Argument::convert(const std::string& p_value){
        return p_value;
    } // #END: convert<std::string>(const std::string&)

    // #FUNCTION: convert<char*>(std::string&), Inline Specialized Template Method
    template<> inline std::expected<char*, Error> Argument::convert(const std::string& p_value){
        char* cstr = new char[p_value.size() + 1];
        std::strcpy(cstr, p_value.c_str());
        return cstr;
    } // #END: convert<char*>(const std::string&)

    // #FUNCTION: convert<char>(const std::string&), Inline Specialized Template Method
    template<> inline std::expected<char, Error> Argument::convert(const std::string& p_value){
        if(p_value.size() != 1){
            return std::unexpected<Error>({Error::Type::CHAR_CONVERSION_FAILURE, p_value});
        }
        return p_value[0];
    } // #END: convert<char>(const std::string&)

    // #FUNCTION: convert<int>(const std::string&), Inline Specialized Template Method
    template<> inline std::expected<int, Error> Argument::convert(const std::string& p_value){
        try{
            return std::stoi(p_value);
        }catch(...){
            return std::unexpected<Error>({Error::Type::INT_CONVERSION_FAILURE, p_value});
        }
    } // #END: convert<int>(const std::string&)

    // #FUNCTION: convert<float>(const std::string&), Inline Specialized Template Method
    template<> inline std::expected<float, Error> Argument::convert(const std::string& p_value){
        try{
            return std::stof(p_value);
        }catch(...){
            return std::unexpected<Error>({Error::Type::FLOAT_CONVERSION_FAILURE, p_value});
        }
    } // #END: convert<float>(const std::string&)

// #END: Argument

// #SCOPE: Option<T_Bind>

// #DIV: Public Factory Methods

    // #FUNCTION: Option(T_Bind* const, const Converter<T_Bind>&), Template Constructor
    template<class T_Bind> Option<T_Bind>::Option(T_Bind* const p_bind, const Converter<T_Bind>& p_converter){
        m_bind = p_bind;
        m_converter = p_converter;
    } // #END: Option(T_Bind* const, const Converter<T_Bind>&)

    // #FUNCTION: Option(T_Bind* const, Converter<T_Bind>&&), Template Constructor
    template<class T_Bind> Option<T_Bind>::Option(T_Bind* const p_bind, Converter<T_Bind>&& p_converter){
        m_bind = p_bind;
        m_converter = std::move(p_converter);
    } // #END: Option(T_Bind* const, Converter<T_Bind>&&)

// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Bind> Argument::Type Option<T_Bind>::type()const{
        return Type::OPTION;
    } // #END: type()

    // #FUNCTION: bind(const std::string&), Override Method
    template<class T_Bind> std::expected<void, Error> Option<T_Bind>::bind(const std::string& p_bind){
        if(m_bind && m_converter){
            if(auto result = m_converter(p_bind); result){
                *m_bind = result.value();
                return {}; // Success return void
            }else{
                return std::unexpected<Error>(result.error());
            }
        }else{
            return std::unexpected<Error>({Error::Type::NULL_BIND_OR_CONVERTER, p_bind});
        }
    } // #END: bind(const std::string&)

// #END: Option<T_Bind>

// #SCOPE: RepeatableOption<T_Bind>

// #DIV: Public Factory Methods

    // #FUNCTION: RepeatableOption(std::vector<T_Bind>* const, const Converter<T_Bind>&), Template Constructor
    template<class T_Bind> RepeatableOption<T_Bind>::RepeatableOption(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter){
        m_bind = p_bind;
        m_converter = p_converter;
    } //#END: RepeatableOption(std::vector<T_Bind>* const, const Converter<T_Bind>&)

    // #FUNCTION: RepeatableOption(std::vector<T_Bind>* const, Converter<T_Bind>&&), Template Constructor
    template<class T_Bind> RepeatableOption<T_Bind>::RepeatableOption(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter){
        m_bind = p_bind;
        m_converter = std::move(p_converter);
    } //#END: RepeatableOption(std::vector<T_Bind>* const, Converter<T_Bind>&&)


// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Bind> Argument::Type RepeatableOption<T_Bind>::type()const{
        return Type::REPEATABLE_OPTION;
    } // #END: type()

    // #FUNCTION: bind(const std::string&), Override Method
    template<class T_Bind> std::expected<void, Error> RepeatableOption<T_Bind>::bind(const std::string& p_bind){
        if(m_bind && m_converter){
            if(auto result = m_converter(p_bind); result){
                m_bind->push_back(result.value());
                return {}; // Success return void
            }else{
                return std::unexpected<Error>(result.error());
            }
        }else{
            return std::unexpected<Error>({Error::Type::NULL_BIND_OR_CONVERTER, p_bind});
        }
    } // #END: bind(const std::string&)

// #END: RepeatableOption<T_Bind>

// #SCOPE: VariadicOption<T_Bind>

// #DIV: Public Factory Methods

    // #FUNCTION: VariadicOption(std::vector<T_Bind>* const, const Converter<T_Bind>&), Template Constructor
    template<class T_Bind> VariadicOption<T_Bind>::VariadicOption(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter){
        m_bind = p_bind;
        m_converter = p_converter;
    } // #END: VariadicOption(std::vector<T_Bind>* const, const Converter<T_Bind>&)

    // #FUNCTION: VariadicOption(std::vector<T_Bind>* const, Converter<T_Bind>&&), Template Constructor
    template<class T_Bind> VariadicOption<T_Bind>::VariadicOption(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter){
        m_bind = p_bind;
        m_converter = std::move(p_converter);
    } // #END: VariadicOption(std::vector<T_Bind>* const, Converter<T_Bind>&&)


// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Bind> Argument::Type VariadicOption<T_Bind>::type()const{
        return Type::VARIADIC_OPTION;
    } // #END: type()

    // #FUNCTION: bind(const std::string&), Override Method
    template<class T_Bind> std::expected<void, Error> VariadicOption<T_Bind>::bind(const std::string& p_bind){
        if(m_bind && m_converter){
            if(auto result = m_converter(p_bind)){
                m_bind->push_back(result.value());
                return {}; // Success return void
            }else{
                return std::unexpected<Error>(result.error());
            }
        }else{
            return std::unexpected<Error>({Error::Type::NULL_BIND_OR_CONVERTER, p_bind});
        }
    } // #END: bind(const std::string&)

// #END: VariadicOption<T_Bind>

// #SCOPE: Command<T_Call>

// #DIV: Public Factory Methods

    // #FUNCTION: Command(const std::function<T_Call>&), Template Constructor
    template<class T_Call> Command<T_Call>::Command(const std::function<T_Call>& p_callback){
        m_callback = p_callback;
    } // #END: Command(const std::function<T_Call>&)

    // #FUNCTION: Command(std::function<T_Call>&&), Template Constructor
    template<class T_Call> Command<T_Call>::Command(std::function<T_Call>&& p_callback){
        m_callback = std::move(p_callback);
    } // #END: Command(std::function<T_Call>&&)

// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Call> Argument::Type Command<T_Call>::type()const{
        return Type::COMMAND;
    } // #END: type()

    // #FUNCTION: callback(), Override Method
    template<class T_Call> void Command<T_Call>::callback(){
        if(m_callback){
            m_callback();
        }
    } // #END: callback()

// #END: Command<T_Call>

// #SCOPE: Positional<T_Bind>

// #DIV: Public Factory Methods

    // #FUNCTION: Positional(std::vector<T_Bind>* const, const Converter<T_Bind>&), Template Constructor
    template<class T_Bind> Positional<T_Bind>::Positional(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter){
        m_bind = p_bind;
        m_converter = p_converter;
    } // #END: Positional(std::vector<T_Bind>* const, const Converter<T_Bind>&)
    
    // #FUNCTION: Positional(std::vector<T_Bind>* const, Converter<T_Bind>&&), Template Constructor
    template<class T_Bind> Positional<T_Bind>::Positional(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter){
        m_bind = p_bind;
        m_converter = std::move(p_converter);
    } // #END: Positional(std::vector<T_Bind>* const, Converter<T_Bind>&&)

// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Bind> Argument::Type Positional<T_Bind>::type()const{
        return Type::POSITIONAL;
    } // #END: type()

    // #FUNCTION: bind(const std::string&), Override Method
    template<class T_Bind> std::expected<void, Error> Positional<T_Bind>::bind(const std::string& p_bind){
        if(m_bind && m_converter){
            if(auto result = m_converter(p_bind); result){
                m_bind->push_back(result.value());
                return {}; // Success return void
            }else{
                return std::unexpected<Error>(result.error());
            }
        }else{
            return std::unexpected<Error>({Error::Type::NULL_BIND_OR_CONVERTER, p_bind});
        }
    } // #END: bind(const std::string&)

// #END: Positional<T_Bind>

// #SCOPE: Program<T_Bind>

// #DIV: Public Factory Methods

    // #FUNCTION: Program(T_Bind* const, const Converter<T_Bind>&), Template Constructor
    template<class T_Bind> Program<T_Bind>::Program(T_Bind* const p_bind, const Converter<T_Bind>& p_converter){
        m_bind = p_bind;
        m_converter = p_converter;
    } // #END: Program(T_Bind* const, const Converter<T_Bind>&)

    // #FUNCTION: Program(T_Bind* const, Converter<T_Bind>&&), Template Constructor
    template<class T_Bind> Program<T_Bind>::Program(T_Bind* const p_bind, Converter<T_Bind>&& p_converter){
        m_bind = p_bind;
        m_converter = std::move(p_converter);
    } // #END: Program(T_Bind* const, Converter<T_Bind>&&)

// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    template<class T_Bind> Argument::Type Program<T_Bind>::type()const{
        return Type::PROGRAM;
    } // #END: type()

    // #FUNCTION: bind(const std::string&), Override Method
    template<class T_Bind> std::expected<void, Error> Program<T_Bind>::bind(const std::string& p_bind){
        if(m_bind && m_converter){
            if(auto result = m_converter(p_bind); result){
                *m_bind = result.value();
                return {}; // Success return void
            }else{
                return std::unexpected<Error>(result.error());
            }
        }else{
            return std::unexpected<Error>({Error::Type::NULL_BIND_OR_CONVERTER, p_bind});
        }
    } // #END: bind(const std::string&)

// #END: Program<T_Bind>

} // #END: arguments

