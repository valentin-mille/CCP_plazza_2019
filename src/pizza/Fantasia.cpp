/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** FantasiaPizza.hpp
*/

#include "Fantasia.hpp"

FantasiaPizza::FantasiaPizza(PizzaSize pizzaSize): APizza(pizzaSize)
{
    _cookingTime = 4000;
    _type = PizzaType::Fantasia;
    _ingredients.push_back(Ingredients::DOE);
    _ingredients.push_back(Ingredients::TOMATO);
    _ingredients.push_back(Ingredients::EGGPLANT);
    _ingredients.push_back(Ingredients::GOAT_CHEESE);
    _ingredients.push_back(Ingredients::CHIEF_LOVE);
}

FantasiaPizza::~FantasiaPizza()
{
}
