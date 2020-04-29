/*
** EPITECH PROJECT, 2019
** Kitchens.cpp
** File description:
** kitchens class implementation
*/

#include "Kitchens.hpp"
#include "Cooks.hpp"
#include "Pizza.hpp"
#include <algorithm>
#include <cstdlib>

Kitchens::Kitchens(int nbOfCooks, const InterProcessCom &pipeCom)
    : pipeCom_(pipeCom)
{
    this->nbOfCooks_ = nbOfCooks;
    resetIngredients();
}

Kitchens::~Kitchens()
{
}

void Kitchens::resetIngredients()
{
    for (size_t i = 0; i < MaxIngre; ++i) {
        this->available_ingr_[i] = 5;
    }
}

void Kitchens::regenerateOneOfEachIngredients()
{
    for (size_t i = 0; i < MaxIngre; ++i) {
        this->available_ingr_[i] += 1;
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

bool Kitchens::cookPizza(const Pizza &toPrepare)
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

int Kitchens::runCookingProcess(const Pizza &pizza)
{
    // Add the clock inside the loop condition
    while (1) {
        if (cookPizza(pizza) == false) {
            // Increment clock here
        } else {
            // reset the clock here
        }
    }
}
