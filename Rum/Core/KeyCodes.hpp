#pragma once
// Std libs
#include <cstdint>

namespace Rum::Core::Keyboard
{
    // The underlying type for Key
    using KeyCode = int16_t;

    // Keys
    enum class Key : KeyCode
    {
        // From glfw.h
        Unknown = -1, //!< Unhandled key
        Space = 0,    //!< The Space key
        Quote,        //!< The ' key
        Comma,        //!< The , key
        Hyphen,       //!< The - key (hyphen)
        Period,       //!< The . key
        Slash,        //!< The / key
        Num0,         //!< The 0 key
        Num1,         //!< The 1 key
        Num2,         //!< The 2 key
        Num3,         //!< The 3 key
        Num4,         //!< The 4 key
        Num5,         //!< The 5 key
        Num6,         //!< The 6 key
        Num7,         //!< The 7 key
        Num8,         //!< The 8 key
        Num9,         //!< The 9 key
        Semicolon,    //!< The ; key
        Equal,        //!< The = key
        A,            //!< The A key
        B,            //!< The B key
        C,            //!< The C key
        D,            //!< The D key
        E,            //!< The E key
        F,            //!< The F key
        G,            //!< The G key
        H,            //!< The H key
        I,            //!< The I key
        J,            //!< The J key
        K,            //!< The K key
        L,            //!< The L key
        M,            //!< The M key
        N,            //!< The N key
        O,            //!< The O key
        P,            //!< The P key
        Q,            //!< The Q key
        R,            //!< The R key
        S,            //!< The S key
        T,            //!< The T key
        U,            //!< The U key
        V,            //!< The V key
        W,            //!< The W key
        X,            //!< The X key
        Y,            //!< The Y key
        Z,            //!< The Z key
        LBracket,     //!< The [ key
        Backslash,    //!< The \ key
        RBracket,     //!< The ] key
        Grave,        //!< The ` key
        World1,       //!< non-US #1
        World2,       //!< non-US #2
        Escape,       //!< The Escape key
        Enter,        //!< The Enter/Return keys
        Tab,          //!< The Tabulation key
        Backspace,    //!< The Backspace key
        Insert,       //!< The Insert key
        Delete,       //!< The Delete key
        Right,        //!< Right arrow
        Left,         //!< Left arrow
        Down,         //!< Down arrow
        Up,           //!< Up arrow
        PageUp,       //!< The Page up key
        PageDown,     //!< The Page down key
        Home,         //!< The Home key
        End,          //!< The End key
        CapsLock,     //!< The caps lock button
        ScrollLock,   //!< The scroll lock button
        NumLock,      //!< The num lock button
        PrintScreen,  //!< The print screen button
        Pause,        //!< The Pause key
        F1,           //!< The F1 key
        F2,           //!< The F2 key
        F3,           //!< The F3 key
        F4,           //!< The F4 key
        F5,           //!< The F5 key
        F6,           //!< The F6 key
        F7,           //!< The F7 key
        F8,           //!< The F8 key
        F9,           //!< The F9 key
        F10,          //!< The F10 key
        F11,          //!< The F11 key
        F12,          //!< The F12 key
        F13,          //!< The F13 key
        F14,          //!< The F14 key
        F15,          //!< The F15 key
        F16,          //!< The F16 key
        F17,          //!< The F17 key
        F18,          //!< The F18 key
        F19,          //!< The F19 key
        F20,          //!< The F20 key
        F21,          //!< The F21 key
        F22,          //!< The F22 key
        F23,          //!< The F23 key
        F24,          //!< The F24 key
        F25,          //!< The F25 key
        Numpad0,      //!< The numpad 0 key
        Numpad1,      //!< The numpad 1 key
        Numpad2,      //!< The numpad 2 key
        Numpad3,      //!< The numpad 3 key
        Numpad4,      //!< The numpad 4 key
        Numpad5,      //!< The numpad 5 key
        Numpad6,      //!< The numpad 6 key
        Numpad7,      //!< The numpad 7 key
        Numpad8,      //!< The numpad 8 key
        Numpad9,      //!< The numpad 9 key
        Decimal,      //!< The numpad . key
        Divide,       //!< The numpad / key
        Multiply,     //!< The numpad * key
        Subtract,     //!< The numpad - key
        Add,          //!< The numpad + key
        NumpadEnter,  //!< The numpad enter key
        NumpadEqual,  //!< The numpad = key
        LShift,       //!< The left Shift key
        LControl,     //!< The left Control key
        LAlt,         //!< The left Alt key
        LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RShift,       //!< The right Shift key
        RControl,     //!< The right Control key
        RAlt,         //!< The right Alt key
        RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,         //!< The Menu key
        KeyCount      //!< Count number of supported keys. KEEP LAST!!!
    };

    constexpr KeyCode getKeyCount()
    {
        return static_cast<KeyCode>(Key::KeyCount);
    }

} // namespace Rum::Core::Keyboard
