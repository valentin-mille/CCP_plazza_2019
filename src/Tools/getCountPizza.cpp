/*
** EPITECH PROJECT, 2020
** getCountPizza
** File description:
** getCountPizza
*/

#include <string>
#include <iostream>
#include "Tools.hpp"

int getCountPizza(std::string &nbPizza)
{
    int value = 0;

    if (nbPizza.front() == 'x') {
        nbPizza.erase(nbPizza.begin());
        value = atoi(nbPizza.c_str());
        if (value > 0) {
            return (value);
        }
        return (0);
    }
    return (0);
}