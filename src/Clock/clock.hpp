/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** clock
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <chrono>

#include <iclock.hpp>

class Clock : public IClock
{
    using clocktype = std::chrono::high_resolution_clock;

public:
    Clock();
    //Clock(Clock& toCopy) = delete;
    //Clock(Clock&& toMove) = delete;

    ~Clock() override = default;

    long getElapsedTime() override;
    void reset() override;

private:
    std::chrono::time_point<clocktype> startTime;
};

#endif
