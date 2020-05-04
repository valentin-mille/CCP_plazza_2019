/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <iterator>
#include <queue>
#include <unistd.h>

#include "APizza.hpp"
#include "InterProcessCom.hpp"
#include "Kitchens.hpp"
#include "Process.hpp"
#include "Reception.hpp"
#include "Tools.hpp"

Reception::Reception(float multiplier, int nbOfCooks, int deliveryTime)
    : multiplier_(multiplier),
      nbOfCooks_(nbOfCooks),
      deliveryTime_(deliveryTime),
      shellActive_(false)
{
}

void Reception::FillQueueOrder(std::vector<std::string> const &OrdersVect)
{
    int size = OrdersVect.size();
    int i = 0;

    if (size == 1) {
        pizzas_.push(OrdersVect.at(0));
    } else {
        while (i < size) {
            pizzas_.push(OrdersVect.at(i));
            i++;
        }
    }
    return;
}

void Reception::parseOrder(std::string const &order)
{
    std::vector<std::string> OrdersVect;
    std::queue<std::string> QueueOrder;
    std::string tmp;
    InterProcessCom process;

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

    shellActive_ = true;
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
    return (shellActive_);
}

void Reception::displayKitchensStatus()
{
    // print the number the current occupancy of the cooks, as well as theirs
    // stocks of ingredients
    for (size_t i = 0; i < streamCom_.size(), ++i) {
        streamCom_[i].writeInformations("status");
        Process::waitResponse(kitchensPid_[i]);
        std::cout << streamCom_[i].readInformations() << std::endl;
    }
}

size_t Reception::getNumberOfPizza(std::string const &pizzaString)
{
    size_t xCharPos = pizzaString.find('x');

    if (xCharPos != std::string::npos) {
        return getCountPizza(pizzaString);
    }
    return 0;
}

std::string Reception::getPizzaTypeSize(const std::string &currentPizza)
{
    size_t pos = currentPizza.find("x");

    return currentPizza.substr(0, pos - 1);
}

int Reception::createNewKitchenProcess(const std::string &toPrepare,
                                       size_t &nbPizzas)
{
    pid_t pid;
    InterProcessCom currentStream;
    Kitchens newKitchen(multiplier_, nbOfCooks_, deliveryTime_, currentStream);

    pid = fork();
    if (pid == 0) {
        // Call pack function with the new nbPizzas
        newKitchen.runCookingProcess(toPrepare, nbPizzas);
        // Exit to close the child process and destroy the kitchen
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        streamCom_.emplace_back(currentStream);
    } else {
        std::cerr << "==> New Kitchen process failure: " << strerror(errno)
                  << std::endl;
        return 1;
    }
    return 0;
}

void Reception::checkKitchensProcessus()
{
    for (size_t i = 0; i < kitchensPid_.size(); ++i) {
        if (Process::isProcessRunning(kitchensPid_[i])) {
            kitchensPid_.erase(kitchensPid_.begin() + i);
        }
    }
}

int Reception::sendPizzasToKitchens()
{
    std::string currentPizza = pizzas_.front();
    size_t nbPizzas = getNumberOfPizza(currentPizza);
    std::string pizzaTypeSize(getPizzaTypeSize(currentPizza));

    checkKitchensProcessus();
    while (pizzas_.empty() == false) {
        while (nbPizzas > 0) {
            for (auto &pipeToKitchen : streamCom_) {
                // Call pack function with the new nbPizzas
                pipeToKitchen.writeInformations(currentPizza);
            }
            if (nbPizzas > 0) {
                if (createNewKitchenProcess(currentPizza, nbPizzas)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
