/*
** EPITECH PROJECT, 2020
** driver.cpp
** File description:
** driver.cppp
*/

#include "Plazza.hpp"
#include "Reception.hpp"
#include "Parser.hpp"

int driver(char **av)
{
    bool parsingDone = false;
    Parser input;

    parsingDone = input.getParams(av);
    if (parsingDone) {
        Reception reception(input.getMultiplier(), input.getNbCooks(), input.getTimeRefill());
        reception.launchShell();
    }
    return (0);
}
