#include <chrono>
#include <thread>
#ifndef FPSLIMITER_H
#define FPSLIMITER_H

constexpr int operator ""_fps(unsigned long long framesPerSecond) { return framesPerSecond; }

class FpsLimiter {
public:
    FpsLimiter(int targetFps): _targetFps{targetFps}, _milisPerFrame(1000/targetFps) {}

    void FrameEnd() {
        if(_lastCycle.time_since_epoch().count() == 0) {
            _lastCycle = std::chrono::steady_clock::now();
        } else {
            auto now = std::chrono::steady_clock::now();
            auto milisElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastCycle).count();
            if (milisElapsed < _milisPerFrame) {
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(_milisPerFrame - milisElapsed));
            }
            _lastCycle = std::move(now);
        }
    }

private: 
    int _targetFps;
    int _milisPerFrame;
    std::chrono::steady_clock::time_point _lastCycle;
};

#endif