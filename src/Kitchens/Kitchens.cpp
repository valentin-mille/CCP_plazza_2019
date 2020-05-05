/*
** EPITECH PROJECT, 2019
** Kitchens.cpp
** File description:
** kitchens class implementation
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "Cooks.hpp"
#include "kitchen.hpp"

Kitchens::Kitchens(float multiplier,
                   int nbCooks,
                   int deliveryTime,
                   const InterProcessCom &pipeCom)
    : pipeCom_(pipeCom),
      multiplier_(multiplier),
      nbCooks_(nbCooks),
      deliveryTime_(deliveryTime),
      _refoundClock()
{
    _refoundClock.reset();
    for (int i = 0; i < nbCooks_; i++)
        cooks_.push_back(Cooks{});
    for (auto &ingredient : stock_)
        ingredient = 5;
    this->nbCooks_ = nbCooks;
    resetIngredients();
}

Kitchens::~Kitchens()
{
}

void Kitchens::update()
{
    if (_refoundClock.getElapsedTime() >= deliveryTime_) {
        for (auto &ingredient : stock_)
            ingredient += 1;
        _refoundClock.reset();
        printStock();
    }
}

void Kitchens::printStock()
{
    std::cout << "-------------------STOCK-----------------------" << std::endl;
    for (auto &ingredient : stock_)
        std::cout << ingredient << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

void Kitchens::resetIngredients()
{
    for (size_t i = 0; i < MaxIngre; ++i) {
        this->stock_[i] = 5;
    }
}

void Kitchens::regenerateOneOfEachIngredients()
{
    for (size_t i = 0; i < MaxIngre; ++i) {
        this->stock_[i] += 1;
    }
}

bool Kitchens::isCookAvailable() const
{
    for (auto const &cook : this->cooks_) {
        if (cook.isOccupied() == false) {
            return true;
        }
    }
    return false;
}

bool Kitchens::cookPizza(const APizza &toPrepare)
{
    for (auto &cook : this->cooks_) {
        if (cook.isOccupied() == false) {
            cook.setCookStatus(true);
            // Give the pizza to the cook
            return true;
        }
    }
    return false;
}

int Kitchens::runCookingProcess(const std::string &pizza)
{
    // Call the serialized operator to unpack the string into pizza
    // Add the clock inside the loop condition
    while (1) {
        //if (cookPizza(pizza) == false) {
            // Increment clock here
        //} else {
            // reset the clock here
        //}
    }
}
