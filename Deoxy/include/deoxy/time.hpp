#pragma once

#include <cstdint>
namespace Deoxy {
    /**
     * @ingroup Core
     * @brief Provides time and frame timing information.
     *
     * The Time class tracks delta time, frames per second and
     * the elapsed time since the application started.
     */
    class Time {
        public:
            /**
             * @brief Reset time state.
             * 
             * Called internally when the application starts.
             */
            void Reset();

            /**
             * @brief Updates the time state.
             * 
             * Computes delta time and updates the FPS counters.
             * Called once per frame by the engine.
             */
            void Update();

            /**
             * @brief Returns the approximate frames per second.
             * 
             * @return Frames per second rounded to an integer value. 
             */
            int GetFPSApprox();

            /**
             * @brief Returns the current frames per second.
             * 
             * @return Current FPS value.
             */
            float GetFPS();

            /**
             * @brief Returns the delta time of the last frame.
             * 
             * @return Delta time in seconds.
             */
            float GetDeltaTime();

            /**
             * @brief Returns the elapsed time since startup.
             * 
             * @return Time in seconds.
             */
            float Get();
        private:
            double m_lastTime = 0.0;

            float m_deltaTime = 0.0f;
            float m_fps = 0.0f;
            float m_fpsTimer = 0.0f;

            uint32_t m_frameCount = 0;
    };
}