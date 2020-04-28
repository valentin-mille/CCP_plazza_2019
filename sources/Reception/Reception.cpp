/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include <iostream>

#include "Reception.hpp"

Reception::Reception()
{
    this->shellActive_ = false;
}

bool Reception::launchShell()
{
    bool isRunning = true;
    std::string input;

    this->shellActive_ = true;
    while (isRunning) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (std::cin.eof() || input == "exit" || input == "quit") {
            std::cout << "--- quit pizzeria --- " << std::endl;
            isRunning = false;
            break;
        }
        std::cout << input << std::endl;
    }
    return (true);
}

bool Reception::getShellActivity()
{
    return (this->shellActive_);
}

void Reception::displayKitchensStatus()
{
   // print the number the current occupancy of the cooks, as well as theirs stocks of ingredients 
}
