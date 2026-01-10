#pragma once

#include <chrono>
#include <functional>
#include <utility>
#include <stdexcept>

namespace unitimer {

using Duration = long long;

enum class Measurement {
    Seconds,
    Milliseconds,
    Microseconds,
    Nanoseconds
};

class Timer final {
public:
    using Clock = std::chrono::high_resolution_clock;
    using Time_Point = std::chrono::time_point<Clock>;
    using Callback = std::function<void(const Timer&)>;

public:
    Timer();
    Timer(Callback callback);

    ~Timer();

    static Duration to_seconds(const Time_Point& time_point);
    static Duration to_milliseconds(const Time_Point& time_point);
    static Duration to_microseconds(const Time_Point& time_point);
    static Duration to_nanoseconds(const Time_Point& time_point);

    Time_Point get_start_point() const;
    Time_Point get_end_point() const;
    void set_callback(Callback callback);
    Duration get_duration(Measurement measurement = Measurement::Microseconds) const;
    bool is_running() const;
    bool is_finished() const;
    bool has_callback() const;
    void stop();
    void stop_without_callback();
    void reset();

private:
    Time_Point m_start_point {};
    Time_Point m_end_point {};
    Callback m_callback {};
    bool m_is_running { true };
};

inline Timer::Timer() :
    m_start_point { Clock::now() } {}

inline Timer::Timer(Callback callback) :
    m_start_point { Clock::now() },
    m_callback { callback } {}

inline Timer::~Timer() {
    stop();
}

inline Timer::Time_Point Timer::get_start_point() const {
    return m_start_point;
}

inline Timer::Time_Point Timer::get_end_point() const {
    return (m_is_running) ? Clock::now() : m_end_point;
}

inline void Timer::set_callback(Callback callback) {
    m_callback = callback;
}

inline Duration Timer::get_duration(Measurement measurement) const {
    if (m_is_running) {
        constexpr Duration error { -1 };
        return error;
    }

    Duration start {};
    Duration end {};

    // We are converting from microseconds to whatever our end measurement is.
    switch (measurement) {
    case Measurement::Seconds:
        start = to_seconds(get_start_point());
        end = to_seconds(get_end_point());
        break;

    case Measurement::Milliseconds:
        start = to_milliseconds(get_start_point());
        end = to_milliseconds(get_end_point());
        break;

    case Measurement::Microseconds:
        start = to_microseconds(get_start_point());
        end = to_microseconds(get_end_point());
        break;

    case Measurement::Nanoseconds:
        start = to_nanoseconds(get_start_point());
        end = to_nanoseconds(get_end_point());
        break;

    default:
        throw std::runtime_error("Unknown timers measurement used!");
    }

    return end - start;
}

inline bool Timer::is_running() const {
    return m_is_running;
}

inline bool Timer::is_finished() const {
    return m_is_running == false;
}

inline bool Timer::has_callback() const {
    return m_callback != nullptr;
}

inline void Timer::stop() {
    if (m_is_running) {
        m_end_point = Clock::now();
        m_is_running = false;

        if (m_callback) {
            m_callback(*this);
        }
    }
}

inline void Timer::stop_without_callback() {
    if (m_is_running) {
        m_end_point = Clock::now();
        m_is_running = false;
    }
}

inline void Timer::reset() {
    m_start_point = Clock::now();
    m_end_point = m_start_point;
    m_is_running = true;
}

inline Duration Timer::to_seconds(const Time_Point& time_point) {
    return std::chrono::time_point_cast<std::chrono::seconds>(time_point)
        .time_since_epoch()
        .count();
}


inline Duration Timer::to_milliseconds(const Time_Point& time_point) {
    return std::chrono::time_point_cast<std::chrono::milliseconds>(time_point)
        .time_since_epoch()
        .count();
}

inline Duration Timer::to_microseconds(const Time_Point& time_point) {
    return std::chrono::time_point_cast<std::chrono::microseconds>(time_point)
        .time_since_epoch()
        .count();
}

inline Duration Timer::to_nanoseconds(const Time_Point& time_point) {
    return std::chrono::time_point_cast<std::chrono::nanoseconds>(time_point)
        .time_since_epoch()
        .count();
}

}
