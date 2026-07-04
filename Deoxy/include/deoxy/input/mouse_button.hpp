#pragma once

namespace Deoxy {
    /**
     * @ingroup Input
     * @brief Mouse button identifiers.
     *
     * Represents mouse buttons supported by the input system.
     */
    enum class MouseButton {
        /**
         * @brief Invalid or unknown mouse button.
         */
        Unknown = -1,

        /**
         * @brief Left mouse button.
         */
        Left,

        /**
         * @brief Right mouse button.
         */
        Right,

        /**
         * @brief Middle mouse button (mouse wheel button).
         */
        Middle,

        /**
         * @brief Total number of mouse buttons.
         * 
         * Used internally for array sizing and iteration.
         */
        Count
    };
}