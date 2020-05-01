/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** ThreadPool.hpp
*/

#pragma once

#include <condition_variable>
#include <cook/Cook.hpp>
#include <memory>
#include <mutex>
#include <pizza/IFood.hpp>
#include <pizza/Regina.hpp>
#include <queue>
#include <vector>

class ThreadPool {
  private:
    std::condition_variable _conditional;
    std::vector<Cook> _Cooks;
    std::queue<std::unique_ptr<IFood>> _foods;
    std::mutex _foodMutex;

  public:
    void addNewThread(size_t nbNew, float multiplier);
    void addOnQueue();

    ThreadPool();
    ~ThreadPool();
};

void ThreadPool::addNewThread(size_t nbNew, float multiplier)
{
    for (size_t i = 0; i < nbNew; i++)
        _Cooks.push_back(Cook{_foods, multiplier, _foodMutex, _conditional});
    for (size_t i = 0; i < _Cooks.size(); i++)
        _Cooks[i].initThread();
}

void ThreadPool::addOnQueue()
{
    if (_foods.size() < _Cooks.size()) {
        std::lock_guard<std::mutex> lock(_foodMutex);
        _foods.push(std::make_unique<ReginaPizza>(PizzaSize::XL));
        _conditional.notify_one();
        std::cout << "Kitchen accepted Pizza, "<< _foods.size() << " on Queue;" << std::endl;
    } else {
        std::cout << "Kitchen Full" << std::endl;
    }
}

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
    std::cout << "Close ThreadPool" << std::endl;
    for (size_t i = 0; i < _Cooks.size(); i++) {
        _Cooks[i].setWorkingState(false);
    }

    for (size_t i = 0; i < _Cooks.size(); i++) {
        _conditional.notify_all();
    }
    for (size_t i = 0; i < _Cooks.size(); i++)
        _Cooks[i].getThread().detach();
}
