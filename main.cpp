/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main.cpp
*/

#include "ExceptionPlazza.hpp"
#include "Plazza.hpp"
#include "Tools.hpp"

int main(int ac, char **av)
{
    int control = 0;

    try {
        if (isCommandLineError(ac, av)) {
            displayUsage();
            return (84);
        }
        control = driver(ac, av);
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (control);
}
