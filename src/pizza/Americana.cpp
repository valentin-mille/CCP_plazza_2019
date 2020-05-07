/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** AmericanaPizza.hpp
*/

#include "Americana.hpp"

AmericanaPizza::AmericanaPizza(PizzaSize pizzaSize): APizza(pizzaSize)
{
    _cookingTime = 2000;
    _type = PizzaType::Americana;
    _ingredients.push_back(Ingredients::DOE);
    _ingredients.push_back(Ingredients::TOMATO);
    _ingredients.push_back(Ingredients::GRUYERE);
    _ingredients.push_back(Ingredients::STEACK);
}

AmericanaPizza::~AmericanaPizza()
{
}
