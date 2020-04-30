/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include <clock.hpp>
#include <cook/Cook.hpp>
#include <ThreadPool.hpp>
#include <ingredient/Ingredients.hpp>

class Kitchen {
  private:
    std::mutex _stockMutex;
    Clock _inactivityClock;
    Clock _refoundClock;
    int _multiplier;
    int _nbCooks;
    int _deliveryTime;
    ThreadPool _threadPool;
    std::array<int, Ingredients::INGREDIENTS_COUNT> _stock;

  public:
    void update();
    void printStock();
    Kitchen(int multiplier, int nbCooks, int deliveryTime);
    ~Kitchen();
};

Kitchen::Kitchen(int multiplier, int nbCooks, int deliveryTime)
    : _multiplier(multiplier), _nbCooks(nbCooks), _deliveryTime(deliveryTime)
{
    _refoundClock.reset();
    for (auto &ingredient: _stock)
        ingredient = 5;
}

void Kitchen::update()
{
    while (1) {
        if (_inactivityClock.getElapsedTime() > 5000) {
            std::cout << "kitchenClose" << std::endl;
            return;
        }
        if (_refoundClock.getElapsedTime() >= _deliveryTime) {
            _stockMutex.lock();
            for (auto &ingredient: _stock)
                ingredient += 1;
            _refoundClock.reset();
            _stockMutex.unlock();
            printStock();
        }
    }
}

void Kitchen::printStock()
{
    std::cout << "-------------------STOCK-----------------------" << std::endl;
    for (auto &ingredient: _stock)
        std::cout << ingredient << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

Kitchen::~Kitchen()
{
}
