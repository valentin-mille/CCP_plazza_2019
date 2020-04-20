/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main.cpp
*/

#include "Exception/ExceptionPlazza.hpp"
#include "Tools/Tools.hpp"
#include "Launcher/Plazza.hpp"

int main(int ac, char **av)
{
    int control = 0;

    try {
        if (ac < 4 || ac > 4) {
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
