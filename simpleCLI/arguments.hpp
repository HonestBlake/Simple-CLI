#pragma once

#if defined(SIMPLE_CLI_USE_MODULES) && defined(INCLUDED_BY_MODULE)
    #define MODULE_EXPORT export
#else
    #include "simpleCli.hpp" // #INCLUDE: simpleCli.hpp, Project Header
    #include "errors.hpp" // #INCLUDE: errors.hpp, Module Header
    #define MODULE_EXPORT
#endif

namespace simpleCli{ // #SCOPE: simpleCli

    MODULE_EXPORT template<class T_Arg> using Converter = std::function<std::expected<T_Arg, Error>(const std::string&)>;

    // #CLASS: Argument, Abstract Class
    MODULE_EXPORT class Argument{
    public:
    // Public Factory Methods
        virtual ~Argument() = default;
    // Public Types
        enum class Type: std::uint8_t{
            DEFAULT,
            FLAG,
            OPTION,
            REPEATABLE_OPTION,
            CONTINUOUS_OPTION,
            COMMAND,
            POSITIONAL,
            PROGRAM
        };
    // Public Static Methods
        template<class T_Arg> static std::expected<T_Arg, Error> convert(const std::string& p_value);
    // Public Methods
        virtual Type type()const = 0;
        virtual bool takesValue()const = 0;
    }; // #END: Argument

    // #CLASS: Bindable, Abstract Class
    MODULE_EXPORT class Bindable: public Argument{
    public:
    // Public Factory Methods
        Bindable() = default;
        virtual ~Bindable() = default;
    // Public Methods
        virtual std::expected<void, Error> bind(const std::string& p_bind) = 0;
        bool takesValue()const override;
    }; // #END: Bindable

    // #CLASS: Callable, Abstract Class
    MODULE_EXPORT class Callable: public Argument{
    public:
    // Public Factory Methods
        Callable() = default;
        virtual ~Callable() = default;
    // Public Methods
        virtual void callback() = 0;
        bool takesValue()const override;
    }; // #END: Callable

    // #CLASS: Flaggable, Abstract Class
    MODULE_EXPORT class Flaggable: public Callable{
    public:
    // Public Factory Methods
        Flaggable() = default;
        virtual ~Flaggable() = default;
    // Public Methods
        virtual void flag() = 0;
    }; // #END: Flaggable

    // #CLASS: Flag, Final Class
    MODULE_EXPORT class Flag final: public Flaggable{
    public:
    // Public Factory Methods
        Flag(bool* const p_bind);
        Flag(const std::function<void()>& p_callback);
        Flag(std::function<void()>&& p_callback);
        Flag(bool* const p_bind, const std::function<void()>& p_callback);
        Flag(bool* const p_bind, std::function<void()>&& p_callback);
    // Public Methods
        Type type()const override;
        void flag()override;
        void callback()override;
    private:
    // Private Members
        bool* m_bind; // External bind
        std::function<void()> m_callback; // Optional callback
    }; // #END: Flag

    // #CLASS: Option<T_Bind>, Template Final Class
    MODULE_EXPORT template<class T_Bind> class Option final: public Bindable{
    public:
    // Public Factory Methods
        Option(T_Bind* const p_bind, const Converter<T_Bind>& p_converter);
        Option(T_Bind* const p_bind, Converter<T_Bind>&& p_converter);
    // Public Methods
        Type type()const override;
        std::expected<void, Error> bind(const std::string& p_bind)override;
    private:
    // Private Members
        T_Bind* m_bind; // External bind
        Converter<T_Bind> m_converter; // Arg value converter
    }; // #END: Option<T_Bind>

    // #CLASS: RepeatableOption<T_Bind>, Template Final Class
    MODULE_EXPORT template<class T_Bind> class RepeatableOption final: public Bindable{
    public:
    // Public Factory Methods
        RepeatableOption(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter);
        RepeatableOption(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter);
    // Public Methods
        Type type()const override;
        std::expected<void, Error> bind(const std::string& p_bind)override;
    private:
    // Private Members
        std::vector<T_Bind>* m_bind; // External bind
        Converter<T_Bind> m_converter; // Arg value converter
    }; // #END: RepeatableOption<T_Bind>

    // #CLASS: ContinuousOption<T_Bind>, Template Final Class
    MODULE_EXPORT template<class T_Bind> class ContinuousOption final: public Bindable{
    public:
    // Public Factory Methods
        ContinuousOption(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter);
        ContinuousOption(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter);
    // Public Methods
        Type type()const override;
        std::expected<void, Error> bind(const std::string& p_bind)override;
    private:
    // Private Members
        std::vector<T_Bind>* m_bind; // External bind
        Converter<T_Bind> m_converter; // Arg value converter
    }; // #END: ContinuousOption<T_Bind>

    // #CLASS: Command<T_Call>, Template Final Class
    MODULE_EXPORT template<class T_Call> class Command final: public Callable{
    public:
    // Public Factory Methods
        Command(const std::function<T_Call>& p_callback);
        Command(std::function<T_Call>&& p_callback);
    // Public Methods
        Type type()const override;
        void callback()override;
    private:
    // Private Members
        std::function<T_Call> m_callback; // Command callback
    }; // #END: Command<T_Call>

    // #CLASS: Positional<T_Bind>, Template Final Class
    MODULE_EXPORT template<class T_Bind> class Positional final: public Bindable{
    public:
    // Public Factory Methods
        Positional(std::vector<T_Bind>* const p_bind, const Converter<T_Bind>& p_converter);
        Positional(std::vector<T_Bind>* const p_bind, Converter<T_Bind>&& p_converter);
    // Public Methods
        Type type()const override;
        std::expected<void, Error> bind(const std::string& p_bind)override;
    private:
    // Private Members
        std::vector<T_Bind>* m_bind; // External bind
        Converter<T_Bind> m_converter; // Arg value converter
    }; // #END: Positional<T_Bind>

    // #CLASS: Program<T_Bind>, Template Final Class
    MODULE_EXPORT template<class T_Bind> class Program final: public Bindable{
    public:
    // Public Factory Methods
        Program(T_Bind* const p_bind, const Converter<T_Bind>& p_converter);
        Program(T_Bind* const p_bind, Converter<T_Bind>&& p_converter);
    // Public Methods
        Type type()const override;
        std::expected<void, Error> bind(const std::string& p_bind)override;
    private:
    // Private Members
        T_Bind* m_bind; // External bind
        Converter<T_Bind> m_converter; // Arg value converter
    }; // #END: Program<T_Bind>

} // #END: simpleCli

#undef MODULE_EXPORT

#include "arguments.tpp" // #INCLUDE: arguments.tpp, Template Implementation
