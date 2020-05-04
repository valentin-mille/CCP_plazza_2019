/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** ThreadPool.hpp
*/

#include "ThreadPool.hpp"

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
        std::cout << "Log: Kitchen-accepted"<< _foods.size() << " on Queue;" << std::endl;
    } else {
        std::cout << "Log: Kitchen-Full" << std::endl;
    }
}

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
    for (size_t i = 0; i < _Cooks.size(); i++) {
        _Cooks[i].setWorkingState(false);
    }

    for (size_t i = 0; i < _Cooks.size(); i++) {
        _conditional.notify_all();
    }
    for (size_t i = 0; i < _Cooks.size(); i++)
        _Cooks[i].getThread().detach();
}
