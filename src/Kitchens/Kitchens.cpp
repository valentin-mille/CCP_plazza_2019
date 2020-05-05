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
      refoundClock_(),
      availableCook_(nbCooks)
{
    refoundClock_.reset();
    for (int i = 0; i < nbCooks_; i++)
        cooks_.push_back(Cooks{});
    for (auto &ingredient : stock_)
        ingredient = 5;
    resetIngredients();
}

Kitchens::~Kitchens()
{
}

void Kitchens::update()
{
    if (refoundClock_.getElapsedTime() >= deliveryTime_) {
        for (auto &ingredient : stock_)
            ingredient += 1;
        refoundClock_.reset();
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

void Kitchens::getKitchenStatus()
{

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

bool Kitchens::cookPizza(const APizza &toPrepare, size_t &nbPizzas)
{
    for (auto &cook : this->cooks_) {
        if (cook.isOccupied() == false) {
            availableCook_ -= 1;
            nbPizzas -= 1;
            cook.setCookStatus(true);
            // Give the pizza to the cook
            return true;
        }
    }
    return false;
}

void Kitchens::runCookingProcess(const std::string &pizza, size_t &nbPizzas)
{
    // Call the serialized operator to unpack the string into pizza
    // Add the clock inside the loop condition
    while (refoundClock_.getElapsedTime() < 5000) {
        //if (cookPizza(pizza, nbPizzas) == false) {
            // Increment clock here
        //} else {
            // reset the clock here
        //}
    }
}
