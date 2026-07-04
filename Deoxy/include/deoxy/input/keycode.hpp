#pragma once

namespace Deoxy {
    /**
     * @ingroup Input
     * @brief Keyboard key identifiers.
     *
     * Represents keyboard keys supported by the input system.
     */
    enum class KeyCode {
        /**
         * @brief Invalid or unknown key.
         */
        Unknown = -1,

        Q, W, E, R, T, Y, U, I, O, P,
        A, S, D, F, G, H, J, K, L,
        Z, X, C, V, B, N, M,

        /**
         * @brief The Ç key found on Brazilian keyboards.
         */
        Ccedilla,

        LeftShift, RightShift,
        LeftControl, RightControl,
        LeftAlt, RightAlt,

        One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        Enter, Space, Escape, Super,

        Up, Down, Left, Right,

        /**
         * @brief Total number of key codes.
         * 
         * Used internally for array sizing and iteration.
         */
        Count
    };
}