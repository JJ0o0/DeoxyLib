#pragma once

#include "../utilities/color.hpp"
#include "../utilities/math.hpp"
#include <string>

struct GLFWwindow;
namespace Deoxy {
    /**
     * @ingroup GUI
     * @brief Built-in GUI themes.
     */
    enum class GUITheme {
        /// Dear ImGui default theme.
        Default,

        /// Rest style by AaronBeardless from ImThemes.
        Rest
    };

    /**
     * @ingroup GUI
     * @brief Stores GUI configuration and appearance settings.
     */
    class GUISettings {
        public:
            /**
             * @brief Restores all GUI settings to their default values.
             */
            void SetDefault();

            /**
             * @brief Enables or disables docking support.
             *
             * @param isDocked True to enable docking.
             */
            void SetDocked(bool isDocked);

            /**
             * @brief Restores the current theme to its default state.
             */
            void ResetTheme();

            /**
             * @brief Applies a predefined GUI theme.
             *
             * @param theme Theme to apply.
             */
            void SetTheme(GUITheme theme);

            /**
             * @brief Returns the currently active theme.
             */
            GUITheme GetTheme() const { return m_theme; }

            /**
             * @brief Returns whether docking is enabled.
             */
            bool IsDocked() const { return m_docked; }
        private:
            GUITheme m_theme = GUITheme::Default;
            bool m_docked = false;

            void setupDefaultTheme();
            void setupRestTheme();
    };

    /**
     * @ingroup GUI
     * @brief Provides Dear ImGui integration and utilities.
     *
     * Responsible for initializing Dear ImGui,
     * creating new frames and providing helper
     * functions for drawing overlays.
     */
    class GUI {
        public:
            /**
             * @brief Initializes the GUI system.
             * 
             * @param glfwWindow Native GLFW window.
             */
            void Init(GLFWwindow* glfwWindow);
            
            /**
             * @brief Shuts down the GUI system.
             */
            void Destroy();

            /**
             * @brief Begins a new ImGui frame.
             */
            void NewFrame();

            /**
             * @brief Ends the current ImGui frame and renders it.
             */
            void EndFrame();

            /**
             * @brief Centers the next ImGui window on the screen.
             * 
             * @param offsetFromCenter Offset from the screen center in pixels.
             */
            void SetNextWindowCentered(const Math::Vector2& offsetFromCenter);

            /**
             * @brief Draws text on the foreground draw list.
             * 
             * @param x X position in pixels.
             * @param y Y position in pixels.
             * @param color Text color.
             * @param text Text to draw.
             */
            void DrawText(float x, float y, const Color color, const std::string& text);

            /**
             * @brief Draws text on the foreground draw list.
             * 
             * @param x X position in pixels.
             * @param y Y position in pixels.
             * @param color32 Text color in RGBA8 format.
             * @param text Text to draw.
             */
            void DrawText(float x, float y, const Color32 color32, const std::string&text);

            /**
             * @brief Returns the GUI settings.
             */
            GUISettings& GetSettings() { return m_settings; }
            const GUISettings& GetSettings() const { return m_settings; }
        private:
            GUISettings m_settings;
    };
}