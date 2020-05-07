/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** MargaritaPizza.hpp
*/

#include "Margarita.hpp"

MargaritaPizza::MargaritaPizza(PizzaSize pizzaSize): APizza(pizzaSize)
{
    _cookingTime = 1000;
    _type = PizzaType::Margarita;
    _ingredients.push_back(Ingredients::DOE);
    _ingredients.push_back(Ingredients::TOMATO);
    _ingredients.push_back(Ingredients::GRUYERE);
}

MargaritaPizza::~MargaritaPizza()
{
}
