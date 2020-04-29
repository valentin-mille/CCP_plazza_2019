/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include "InterProcessCom.hpp"
#include "Kitchens.hpp"
#include "Pizza.hpp"
#include "Reception.hpp"

Reception::Reception(int nbOfCooks) : nbOfCooks_(nbOfCooks)
{
    this->shellActive_ = false;
}

void Reception::parseOrder(std::string const &order)
{
    std::vector<std::vector<std::string>> OrdersVect;

    OrdersVect = CleanOrder(order);
    if (OrdersVect.empty()) {
        std::cerr << "Error: Invalid Order" << std::endl;
        return;
    }
    std::cout << "NB ORDERS : " << OrdersVect.size() << std::endl;
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
        parseOrder(input);
    }
    return (true);
}

bool Reception::getShellActivity()
{
    return (this->shellActive_);
}

void Reception::displayKitchensStatus()
{
    // print the number the current occupancy of the cooks, as well as theirs
    // stocks of ingredients
    //
}

int Reception::createNewKitchenProcess(const Pizza &toPrepare)
{
    InterProcessCom currentStream;
    pid_t pid;
    Kitchens newKitchen(this->nbOfCooks_, currentStream);

    pid = fork();
    if (pid == 0) {
        newKitchen.runCookingProcess(toPrepare);
        // Exit to close the child process
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        this->streamCom_.emplace_back(currentStream);
    } else {
        std::cerr << "==> New Kitchen process failure: " << strerror(errno)
                  << std::endl;
        return 1;
    }
    return 0;
}

int Reception::sendPizzaToKitchens()
{
    Pizza currentPizza = this->pizzas_.front();
    bool taskDone = false;

    for (auto &kitchen : this->kitchensProcess_) {
        if (kitchen.isCookAvailable()) {
            kitchen.runCookingProcess(currentPizza);
            taskDone = true;
            break;
        }
    }
    if (taskDone == false) {
        if (this->createNewKitchenProcess(currentPizza)) {
            return 1;
        }
    }
    return 0;
}
