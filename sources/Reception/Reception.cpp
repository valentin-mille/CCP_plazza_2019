/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include <iostream>
#include <cstring>

#include "Reception.hpp"

Reception::Reception()
{
    this->_shellActive = false;
}

void Reception::parseOrder(std::string const &order)
{
    std::vector<std::vector<std::string>> Orders;

    Orders = CleanOrder(order);
    if (Orders.empty()) {
        std::cerr << "Error: Invalid Order" << std::endl;
        return;
    }
    std::cout << "NB ORDERS : " << Orders.size() << std::endl;
}

bool Reception::launchShell()
{
    bool isRunning = true;
    std::string input;

    this->_shellActive = true;
    while (isRunning) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (std::cin.eof() || input == "exit" || input == "quit") {
            std::cout << "--- quit pizzeria --- " << std::endl;
            isRunning = false;
            break;
        }
        parseOrder(input);
    }
    return (true);
}

bool Reception::getShellActivity()
{
    return (this->_shellActive);
}
