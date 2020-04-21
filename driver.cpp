/*
** EPITECH PROJECT, 2020
** driver.cpp
** File description:
** driver.cppp
*/

#include "Launcher/Plazza.hpp"
#include "Parser/Parser.hpp"

int driver(int ac, char **av)
{
    bool parsingDone = false;
    // Launch Parsing
    Parser input;

    parsingDone = input.getParams(av);
    if (parsingDone) {
        std::cout << "Launch Shell" << std::endl;
        // Verify Command
    }
    return (0);
}
