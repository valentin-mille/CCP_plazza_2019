/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** ReginaPizza.hpp
*/

#pragma once

#include<APizza.hpp>

class ReginaPizza : public APizza
{
private:
public:
    ReginaPizza(PizzaSize);
    ~ReginaPizza();
};

ReginaPizza::ReginaPizza(PizzaSize pizzaSize): APizza(pizzaSize)
{
    _type = PizzaType::Regina;
    _ingredients.push_back(Ingredients::DOE);
    _ingredients.push_back(Ingredients::GRUYERE);
}

ReginaPizza::~ReginaPizza()
{
}
