#pragma once

namespace Deoxy {
    enum class KeyCode {
        Unknown = -1,

        Q, W, E, R, T, Y, U, I, O, P,
        A, S, D, F, G, H, J, K, L,
        Z, X, C, V, B, N, M,

        Ccedilla,

        LeftShift, RightShift,
        LeftControl, RightControl,
        LeftAlt, RightAlt,

        One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        Enter, Space, Escape, Super,

        Up, Down, Left, Right,

        Count
    };
}