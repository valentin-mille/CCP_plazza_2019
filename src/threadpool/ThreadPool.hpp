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
    int addOnQueue(std::unique_ptr<IFood> food);

    ThreadPool();
    ~ThreadPool();
};
