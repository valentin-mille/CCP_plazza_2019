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

int ThreadPool::haveFreeCook()
{
    for (size_t i = 0; i < _Cooks.size(); i++)
        if (_Cooks[i].isBusy() == 0)
            return 0;
    return 1;
}

int ThreadPool::addOnQueue(std::unique_ptr<IFood> food)
{
    if ( haveFreeCook() == 0 || _foods.size() < _Cooks.size()) {
        std::lock_guard<std::mutex> lock(_foodMutex);
        _foods.push(std::move(food));
        _conditional.notify_one();
        std::cout<< "Log: Kitchen-accepted"<< _foods.size() << " on Queue;" << std::endl;
        return 0;
    } else {
        std::cout<< "Log: Kitchen-Full" << std::endl;
        return 1;
    }
}

std::vector<Cook> const& ThreadPool::getCooks() const
{
    return _Cooks;
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
