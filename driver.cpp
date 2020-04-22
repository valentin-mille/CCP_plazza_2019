/*
** EPITECH PROJECT, 2020
** driver.cpp
** File description:
** driver.cppp
*/

#include "Launcher/Plazza.hpp"
#include "Parser/Parser.hpp"
#include "Reception/Reception.hpp"

int driver(int ac, char **av)
{
    bool parsingDone = false;
    // Launch Parsing
    Parser input;
    Reception reception;

    parsingDone = input.getParams(av);
    if (parsingDone) {
        reception.launchShell();
        // Verify Command
    }
    return (0);
}
