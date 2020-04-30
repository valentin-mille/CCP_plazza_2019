/*
** EPITECH PROJECT, 2019
** ParseCommandLine.cpp
** File description:
** functions to parse command line
*/

#include <cstdlib>

bool isCommandLineError(int ac, char **av)
{
    bool error = true;
    float cookingTime = 0;
    int numberOfCook = 0;
    int timeToReplaceIngr = 0;

    if (ac == 4) {
        cookingTime = std::atof(av[1]);
        numberOfCook = std::atoi(av[2]);
        timeToReplaceIngr = std::atoi(av[3]);
        if (cookingTime >= 0 && numberOfCook > 0 && timeToReplaceIngr >= 0) {
           error = false;
        }
    }
    return error;
}
