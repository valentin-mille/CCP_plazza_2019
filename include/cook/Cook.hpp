/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#pragma once

#include "pizza/IFood.hpp"
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
    bool _working;
    float _multiplier;
    std::queue<std::unique_ptr<IFood>> &_queueRef;
    std::mutex &_queueMutex;
    std::condition_variable &_conditionalRef;
    std::unique_ptr<std::thread> _thread;

  public:
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

std::thread &Cook::getThread()
{
    return *(_thread.get());
}

bool Cook::getWorkingState() const
{
    return _working;
}

void Cook::setWorkingState(bool working)
{
    _working = working;
}

void Cook::update()
{
    std::unique_lock<std::mutex> lock(_queueMutex, std::defer_lock);
    IFood *foodRef;

    while (_working) {
        lock.lock();
        _conditionalRef.wait(lock,
            [this] { return (!this->_queueRef.empty()) || (!_working); });
        if (!_working) {
            lock.unlock();
            break;
        }
        std::cout << "LockQueue" << std::endl;
        foodRef = _queueRef.front().release();
        _queueRef.pop();
        lock.unlock();
        _conditionalRef.notify_one();
        std::cout << "unLockQueue" << std::endl;

        std::cout << "Pizza " << foodRef->getTypeString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(foodRef->getCookingTime() * _multiplier)));
        std::cout << "Pizza Finish" << std::endl;
    }
    std::cout << "Cook leave" << std::endl;
}

void Cook::initThread()
{
    _working = true;
    _thread = std::make_unique<std::thread>(
        std::thread([this]() { this->update(); }));
}

Cook::Cook(std::queue<std::unique_ptr<IFood>> &queueRef, float multiplier,
    std::mutex &foodMutexRef, std::condition_variable &conditionalRef)
    : _multiplier(multiplier), _queueRef(queueRef), _queueMutex(foodMutexRef),
      _conditionalRef(conditionalRef), _thread(nullptr)
{
}

Cook::~Cook()
{
}
