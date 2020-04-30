/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** ThreadPool.hpp
*/

#pragma once

#include <vector>
#include <queue>
#include <cook/Cook.hpp>
#include <pizza/IFood.hpp>

class ThreadPool
{
private:
    std::vector<Cook> _Cooks;
    std::queue<IFood> _foods;
public:
    ThreadPool();
    ~ThreadPool();
};

ThreadPool::ThreadPool()
{
    _Cooks.push_back(Cook{});
}

ThreadPool::~ThreadPool()
{
}
