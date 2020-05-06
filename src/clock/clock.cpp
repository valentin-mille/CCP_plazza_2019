/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** clock
*/

#include <clock.hpp>

Clock::Clock() : startTime{clocktype::now()}
{
}

long Clock::getElapsedTime()
{
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        clocktype::now() - this->startTime);

    return elapsed_time.count();
}

void Clock::reset()
{
    this->startTime = clocktype::now();
}
