#include "arguments.hpp" // #INCLUDE: arguments.hpp, Module Header

namespace simpleCLI::arguments{ // #SCOPE: arguments

// #SCOPE: Bindable

// #DIV: Public Methods

    // #FUNCTION: takesValue(), Const Override Method
    bool Bindable::takesValue()const{
        return true;
    } // #END: takesValue()

// #END: Bindable

// #SCOPE: Callable

// #DIV: Public Methods

    // #FUNCTION: takesValue(), Const Override Method
    bool Callable::takesValue()const{
        return false;
    } // #END: takesValue()

// #END: Callable

// #SCOPE: Flag

// #DIV: Public Factory Methods

    // #FUNCTION: Flag(bool* const), Constructor
    Flag::Flag(bool* const p_bind){
        m_bind = p_bind;
        *m_bind = false;
    } // #END: Flag::Flag(bool* const)

    // #FUNCTION: Flag(const std::function<void()>&), Constructor
    Flag::Flag(const std::function<void()>& p_callback){
        m_callback = p_callback;
    } // #END: Flag(const std::function<void()>&)

    // #FUNCTION: Flag(std::function<void()>&&), Constructor
    Flag::Flag(std::function<void()>&& p_callback){
        m_callback = std::move(p_callback);
    } // #END: Flag(std::function<void()>&&)

    // #FUNCTION: Flag(bool* const, const std::function<void()>&), Constructor
    Flag::Flag(bool* const p_bind, const std::function<void()>& p_callback){
        m_bind = p_bind;
        m_callback = p_callback;
        *m_bind = false;
    } // #END: Flag(bool* const, const std::function<void()>&)

    // #FUNCTION: Flag(bool* const, std::function<void()>&&), Constructor
    Flag::Flag(bool* const p_bind, std::function<void()>&& p_callback){
        m_bind = p_bind;
        m_callback = std::move(p_callback);
        *m_bind = false;
    } // #END: Flag(bool* const, std::function<void()>&&)

// #DIV: Public Methods

    // #FUNCTION: type(), Const Override Method
    Argument::Type Flag::type()const{
        return Type::FLAG;
    } // #END: type()

    // #FUNCTION: flag(), Override Method
    void Flag::flag(){
        if(m_bind){
            *m_bind = true;
        }
    } // #END: flag()

    // #FUNCTION: callback(), Override Method
    void Flag::callback(){
        if(m_callback){
            m_callback();
        }
    } // #END: callback()

// #END: Flag

} // #END: arguments