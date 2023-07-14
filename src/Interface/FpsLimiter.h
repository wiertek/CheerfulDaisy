#ifndef FPSLIMITER_H
#define FPSLIMITER_H

#include <chrono>
#include <thread>

constexpr int operator""_fps(unsigned long long framesPerSecond) { return static_cast<int>(framesPerSecond); }

class FpsLimiter {
  public:
    FpsLimiter(int targetFps) : milisPerFrame_(1000 / targetFps) {}

    void frameEnd() {
        if (lastCycle_.time_since_epoch().count() == 0) {
            lastCycle_ = std::chrono::steady_clock::now();
        } else {
            auto now = std::chrono::steady_clock::now();
            auto milisElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCycle_).count();
            if (milisElapsed < milisPerFrame_) {
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(milisPerFrame_ - milisElapsed));
            }
            lastCycle_ = std::move(now);
        }
    }

  private:
    int milisPerFrame_;
    std::chrono::steady_clock::time_point lastCycle_;
};

#endif