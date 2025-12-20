#pragma once

#include "simpleCLI.hpp" // #INCLUDE: simpleCLI.hpp, Project Header
#include "arguments.hpp" // #INCLUDE: arguments.hpp, Module Header
#include "errors.hpp" // #INCLUDE: errors.hpp, Module Header

namespace simpleCLI::parser{ // #SCOPE: parser
    
    // #CLASS: Parser, Class
    class Parser{
    public:
    // Public Factory Methods
        Parser() = default;
        ~Parser() = default;
    // Public Methods
        std::expected<bool, Error> parse(const int argc, char** const argv)const;
        std::expected<void, Error> addFlag(const std::initializer_list<std::string_view> p_tags, bool& p_bind);
        std::expected<void, Error> addFlag(const std::initializer_list<std::string_view> p_tags, const std::function<void()>& p_callback);
        std::expected<void, Error> addFlag(const std::initializer_list<std::string_view> p_tags, std::function<void()>&& p_callback);
        std::expected<void, Error> addFlag(const std::initializer_list<std::string_view> p_tags, bool& p_bind, const std::function<void()>& p_callback);
        std::expected<void, Error> addFlag(const std::initializer_list<std::string_view> p_tags, bool& p_bind, std::function<void()>&& p_callback);
        template<class T_Bind> std::expected<void, Error> addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, Converter<T_Bind>&& p_converter);
        template<class T_Bind> std::expected<void, Error> addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const T_Bind& p_default, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addOption(const std::initializer_list<std::string_view> p_tags, T_Bind& p_bind, const T_Bind& p_default, Converter<T_Bind>&& p_converter);
        template<class T_Bind> std::expected<void, Error> addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter);
        template<class T_Bind> std::expected<void, Error> addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addRepeatableOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, Converter<T_Bind>&& p_converter);
        template<class T_Bind> std::expected<void, Error> addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter);
        template<class T_Bind> std::expected<void, Error> addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> std::expected<void, Error> addVariadicOption(const std::initializer_list<std::string_view> p_tags, std::vector<T_Bind>& p_bind, const std::vector<T_Bind>& p_default, Converter<T_Bind>&& p_converter);
        template<class T_Bind> void addPositional(std::vector<T_Bind>& p_bind, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> void addPositional(std::vector<T_Bind>& p_bind, Converter<T_Bind>&& p_converter);
        template<class T_Bind> void addProgram(T_Bind& p_bind, const Converter<T_Bind>& p_converter = &Argument::convert<T_Bind>);
        template<class T_Bind> void addProgram(T_Bind& p_bind, Converter<T_Bind>&& p_converter);
    // Public Members
        static inline constexpr std::uint8_t SHORT_TAG_SIZE = 2;
        static inline constexpr std::uint8_t LONG_TAG_MIN_SIZE = 4;
        static inline constexpr char OPTION_VALUE_SEPARATOR = '=';
    private:
    // Private Methods
        bool isUniqueTag(const std::string& p_tag)const;
        bool isValidTag(const std::string& p_tag)const;
        bool isValidValue(const std::string& p_value)const;
        std::expected<void, Error> preprocess(std::vector<std::string>& p_commandLine)const;
        std::expected<void, Error> bind(const std::shared_ptr<Argument>& p_bindable, const std::string& p_value)const;
        std::expected<void, Error> bind(const std::unique_ptr<Bindable>& p_bindable, const std::string& p_value)const;  
        std::expected<void, Error> flag(const std::shared_ptr<Argument>& p_flaggable)const;
        std::expected<void, Error> callback(const std::shared_ptr<Argument>& p_callable)const;
        std::shared_ptr<Argument> getArgument(const std::string& p_tag)const;
    // Private Members
        std::unordered_map<std::string, std::shared_ptr<Argument>> m_arguments;
        std::unique_ptr<Bindable> m_positionals;
        std::unique_ptr<Bindable> m_program;
    }; // #END: Parser

} // #END: parser

#include "parser.tpp" // #INCLUDE: parser.tpp, Template Implementation