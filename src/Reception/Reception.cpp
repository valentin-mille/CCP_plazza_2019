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
#include <queue>
#include <unistd.h>

#include "InterProcessCom.hpp"
#include "APizza.hpp"
#include "Kitchens.hpp"
#include "Reception.hpp"

Reception::Reception(float multiplier, int nbOfCooks, int deliveryTime)
    : multiplier_(multiplier), nbOfCooks_(nbOfCooks), deliveryTime_(deliveryTime)
{
    this->shellActive_ = false;
}

void Reception::FillQueueOrder(std::vector<std::string> const &OrdersVect)
{
    int size = OrdersVect.size();
    int i = 0;

    if (size == 1) {
        this->pizzas_.push(OrdersVect.at(0));
    } else {
        while (i < size) {
            this->pizzas_.push(OrdersVect.at(i));
            i++;
        }
    }
    return;
}

void Reception::parseOrder(std::string const &order)
{
    std::vector<std::string> OrdersVect;
    std::queue<std::string> QueueOrder;

    OrdersVect = CleanOrder(order);
    if (OrdersVect.empty()) {
        std::cerr << "Error: Invalid Order" << std::endl;
        return;
    }
    FillQueueOrder(OrdersVect);
    return;
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

int Reception::createNewKitchenProcess(const APizza &toPrepare)
{
    InterProcessCom currentStream;
    pid_t pid;
    Kitchens newKitchen(this->multiplier_,
                        this->nbOfCooks_,
                        this->deliveryTime_,
                        currentStream);

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
    APizza currentPizza = this->pizzas_.front();
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
