#pragma once

namespace Deoxy {
    class Time {
        public:
            void Reset();
            void Update();

            float GetDeltaTime();
            float Get();
        private:
            double s_lastTime = 0.0;
            float s_deltaTime = 0.0f;
    };
}