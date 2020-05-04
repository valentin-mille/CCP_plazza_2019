/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#pragma once

#include <vector>
#include <array>
#include <iostream>

#include <cook/Cook.hpp>
#include <ingredient/Ingredients.hpp>
#include <clock.hpp>

class Kitchen
{
private:
    Clock _refoundClock;
    int _multiplier;
    int _nbCooks;
    int _deliveryTime;
    std::vector<Cook> _Cooks;
    std::array<int, Ingredients::INGREDIENTS_COUNT> _stock;
public:
    void update();
    void printStock();
    Kitchen(int multiplier, int nbCooks, int deliveryTime);
    ~Kitchen();
};

Kitchen::Kitchen(int multiplier, int nbCooks, int deliveryTime): _multiplier(multiplier), _nbCooks(nbCooks), _deliveryTime(deliveryTime)
{
    _refoundClock.reset();
    for (int i = 0; i < _nbCooks; i++)
        _Cooks.push_back(Cook{});
    for (auto& ingredient:  _stock)
        ingredient = 5;
}

void Kitchen::update()
{
    if (_refoundClock.getElapsedTime() >= _deliveryTime) {
        for (auto& ingredient:  _stock)
            ingredient += 1;
        _refoundClock.reset();
        printStock();
    }

}

void Kitchen::printStock()
{
    std::cout << "-------------------STOCK-----------------------" << std::endl;
    for (auto& ingredient:  _stock)
        std::cout << ingredient << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

Kitchen::~Kitchen()
{
}
