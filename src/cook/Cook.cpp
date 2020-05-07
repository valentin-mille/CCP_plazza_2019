/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#include "Cook.hpp"

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
    _working = true;

    while (_working) {
        lock.lock();
        _conditionalRef.wait(lock,
            [this] { return (!this->_queueRef.empty()) || (!_working); });
        if (!_working) {
            lock.unlock();
            break;
        }
        std::cout<< "Log: Cook-LockQueue" << std::endl;
        foodRef = _queueRef.front().release();
        _queueRef.pop();
        lock.unlock();
        _conditionalRef.notify_one();
        _busy = true;
        std::cout<< "Log: Cook-unLockQueue" << std::endl;
        std::cout<< "Log: Pizza-start-cooking " << foodRef->getTypeString() << " " << foodRef->getSizeString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(
            (int)(foodRef->getCookingTime() * _multiplier)));
        _busy = false;
        std::cout<< "Log: Pizza-Finish" << std::endl;
    }
    std::cout<< "Log: Cook-leave" << std::endl;
}

bool Cook::isBusy() const
{
    return _busy;
}

void Cook::initThread()
{
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
