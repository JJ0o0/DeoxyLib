#pragma once

#include <cstdint>
namespace Deoxy {
    class Time {
        public:
            void Reset();
            void Update();

            int GetFPSApprox();
            float GetFPS();
            float GetDeltaTime();
            float Get();
        private:
            double m_lastTime = 0.0;

            float m_deltaTime = 0.0f;
            float m_fps = 0.0f;
            float m_fpsTimer = 0.0f;

            uint32_t m_frameCount = 0;
    };
}