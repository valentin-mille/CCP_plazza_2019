/*
** EPITECH PROJECT, 2019
** Kitchens.cpp
** File description:
** kitchens class implementation
*/

#include "Kitchens.hpp"

Kitchens::Kitchens(const InterProcessCom &pipeCom): pipeCom_(pipeCom)
{
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
