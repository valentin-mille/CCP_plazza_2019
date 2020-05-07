/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#pragma once

#include "IFood.hpp"
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class Cook {
  private:
    bool _busy;
    bool _working;
    float _multiplier;
    std::queue<std::unique_ptr<IFood>> &_queueRef;
    std::mutex &_queueMutex;
    std::condition_variable &_conditionalRef;
    std::unique_ptr<std::thread> _thread;

  public:
    bool isBusy() const;
    void initThread();
    std::thread &getThread();
    void setWorkingState(bool workingState);
    bool getWorkingState() const;
    void update();

    Cook(Cook &&to_move) = default;
    Cook(std::queue<std::unique_ptr<IFood>> &queueRef, float multiplier,
        std::mutex &, std::condition_variable &);
    ~Cook();
};