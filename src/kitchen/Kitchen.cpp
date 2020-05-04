/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(float multiplier, int nbCooks, int deliveryTime)
    : _multiplier(multiplier), _nbCooks(nbCooks), _deliveryTime(deliveryTime)
{
    _threadPool.addNewThread(_nbCooks, multiplier);
    _refoundClock.reset();
    for (auto &ingredient: _stock)
        ingredient = 5;
}

void Kitchen::newPizza()
{
    _inactivityClock.reset();
    _threadPool.addOnQueue();
}

void Kitchen::update()
{
    while (1) {
        if (_inactivityClock.getElapsedTime() > 5000) {
            std::cout << "Log: kitchenClose" << std::endl;
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
