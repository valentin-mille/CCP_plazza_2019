/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Pizza.hpp
*/

#pragma once

enum PizzaType
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class IPizza
{
private:
    /* data */
public:
    IPizza(/* args */);
    ~IPizza();
};

IPizza::IPizza(/* args */)
{
}

IPizza::~IPizza()
{
}
