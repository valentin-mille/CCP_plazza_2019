/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** ReginaPizza.hpp
*/

#include "Regina.hpp"

ReginaPizza::ReginaPizza(PizzaSize pizzaSize): APizza(pizzaSize)
{
    _cookingTime = 2000;
    _type = PizzaType::Regina;
    _ingredients.push_back(Ingredients::DOE);
    _ingredients.push_back(Ingredients::TOMATO);
    _ingredients.push_back(Ingredients::GRUYERE);
    _ingredients.push_back(Ingredients::HAM);
    _ingredients.push_back(Ingredients::MUSHROOMS);
}

ReginaPizza::~ReginaPizza()
{
}
