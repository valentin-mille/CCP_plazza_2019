/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include "Reception.hpp"
#include "InterProcessCom.hpp"
#include <cstdlib>
#include <string>

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

    for (int i = 0; i < size; i++)
        pizzas_.push(OrdersVect.at(i));
}

void Reception::parseOrder(std::string const &order)
{
    std::vector<std::string> OrdersVect;
    std::string tmp;
    InterProcessCom process;

    if (order.empty() || order == " ") {
        std::cerr << "Error: Invalid Order" << std::endl;
        return;
    }
    OrdersVect = CleanOrder(order);
    if (OrdersVect.empty()) {
        std::cerr << "Error: Invalid Order" << std::endl;
        return;
    }
    FillQueueOrder(OrdersVect);
    if (pizzas_.empty() == false) {
        sendPizzasToKitchens();
    }
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
    for (size_t i = 0; i < streamCom_.size(); ++i) {
        streamCom_[i].writeToKitchenBuffer("status");
        Process::waitResponse(kitchensPid_[i]);
        streamCom_[i].readReceptionBuffer();
    }
}

size_t Reception::getNumberOfPizza(std::string const &pizzaString)
{
    size_t xCharPos = pizzaString.find('x');
    std::string stringWithNb;

    if (xCharPos != std::string::npos) {
        stringWithNb = pizzaString.substr(xCharPos);
        return getCountPizza(stringWithNb);
    }
    return 0;
}

std::string Reception::getPizzaTypeSize(const std::string &currentPizza)
{
    size_t pos = currentPizza.find("x");

    return currentPizza.substr(0, pos - 1);
}

int Reception::createNewKitchenProcess(const std::string &currentPizza,
                                       size_t &nbPizzas)
{
    pid_t pid;
    InterProcessCom currentStream;
    std::string infos("OK\n");

    pid = Process::launchProcess();
    if (pid == 0) {
        std::unique_ptr<Kitchen> newKitchen = std::make_unique<Kitchen>(
            multiplier_, nbOfCooks_, deliveryTime_, currentStream);
        newKitchen.get()->update();
        newKitchen.reset();
        // Exit to close the child process and destroy the kitchen
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        streamCom_.emplace_back(currentStream);
        kitchensPid_.push_back(pid);
        while (infos == "OK" && nbPizzas > 0) {
            currentStream.writeToKitchenBuffer(currentPizza);
            infos = currentStream.readReceptionBuffer();
            if (infos == "OK") {
                --nbPizzas;
            }
        }
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
            streamCom_.erase(streamCom_.begin() + i);
        }
    }
}

int Reception::sendPizzasToKitchens()
{
    InterProcessCom debug;
    std::string currentPizza = pizzas_.front();
    debug.printOutput(currentPizza);
    size_t nbPizzas = getNumberOfPizza(currentPizza);
    std::string pizzaTypeSize(getPizzaTypeSize(currentPizza));
    std::string infos;
    std::string serializedOrder;

    debug.printOutput("Nb Pizzas #1:" + std::to_string(nbPizzas));
    checkKitchensProcessus();
    serializedOrder = InterProcessCom::pack(currentPizza);
    debug.printOutput("Serialized order " + serializedOrder);
    while (nbPizzas > 0) {
        debug.printOutput("Nb Pizzas #2: " + std::to_string(nbPizzas));
        for (auto &pipeToKitchen : streamCom_) {
            pipeToKitchen.writeToKitchenBuffer(serializedOrder);
            infos = pipeToKitchen.readReceptionBuffer();
            if (infos == "OK" && nbPizzas > 0) {
                --nbPizzas;
            }
        }
        if (nbPizzas > 0) {
            if (createNewKitchenProcess(serializedOrder, nbPizzas)) {
                return 1;
            }
        }
    }
    pizzas_.pop();
    return 0;
}
