/*
** EPITECH PROJECT, 2020
** Reception.cpp
** File description:
** Reception.cpp
*/

#include "Reception.hpp"
#include "InterProcessCom.hpp"
#include "Process.hpp"
#include <cstdlib>
#include <ostream>
#include <string>

// [TODO] delete this line before delivery
InterProcessCom debug;

Reception::Reception(float multiplier, int nbOfCooks, int deliveryTime)
    : multiplier_(multiplier),
      nbOfCooks_(nbOfCooks),
      deliveryTime_(deliveryTime),
      shellActive_(false)
{
}

Reception::~Reception()
{
    size_t nbProcess = streamCom_.size();

    std::cout << "Wait for kitchens..." << std::endl;
    for (size_t i = 0; i < nbProcess; ++i) {
        streamCom_[i].writeToKitchenBuffer("exit");
        Process::waitResponse(kitchensPid_[i]);
    }
}

template <typename T>
T operator>>(T &left, T &packedOrder)
{
    left = InterProcessCom::pack(packedOrder);
    return (left);
}

template <typename T>
T operator<<(T &left, T &order)
{
    left = InterProcessCom::unpack(order);
    return (left);
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
            isRunning = false;
            break;
        }
        if (input == "status") {
            displayKitchensStatus();
        } else {
            parseOrder(input);
        }
    }
    return (true);
}

bool Reception::getShellActivity()
{
    return (shellActive_);
}

void Reception::displayKitchensStatus()
{
    checkKitchensProcessus();
    for (size_t i = 0; i < streamCom_.size(); ++i) {
        streamCom_[i].writeToKitchenBuffer("status");
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
    std::string infos("OK");

    streamCom_.emplace_back();
    pid = Process::launchProcess();
    if (pid == 0) {
        std::unique_ptr<Kitchen> newKitchen = std::make_unique<Kitchen>(
            multiplier_, nbOfCooks_, deliveryTime_, streamCom_.back());
        newKitchen.get()->update();
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        kitchensPid_.push_back(pid);
        while (infos == "OK" && nbPizzas > 0) {
            streamCom_.back().writeToKitchenBuffer(currentPizza);
            infos = streamCom_.back().readReceptionBuffer();
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
    size_t i = 0;

    while (i < kitchensPid_.size()) {
        if (Process::isProcessRunning(kitchensPid_[i]) == false) {
            kitchensPid_.erase(kitchensPid_.begin() + i);
            streamCom_.erase(streamCom_.begin() + i);
            continue;
        }
        ++i;
    }
}

int Reception::sendPizzasToKitchens()
{
    std::string currentPizza = pizzas_.front();
    size_t nbPizzas = getNumberOfPizza(currentPizza);
    std::string pizzaTypeSize(getPizzaTypeSize(currentPizza));
    std::string infos("OK");
    std::string serializedOrder;

    checkKitchensProcessus();
    while (pizzas_.empty() == false) {
        serializedOrder >> currentPizza;
        while (nbPizzas > 0) {
            if (streamCom_.empty() == false) {
                for (size_t i = 0; i < streamCom_.size(); ++i) {
                    while (infos == "OK" && nbPizzas > 0) {
                        streamCom_[i].writeToKitchenBuffer(serializedOrder);
                        infos = streamCom_[i].readReceptionBuffer();
                        if (infos == "OK" && nbPizzas > 0) {
                            --nbPizzas;
                        }
                    }
                }
            }
            if (nbPizzas > 0) {
                if (createNewKitchenProcess(serializedOrder, nbPizzas)) {
                    return 1;
                }
            }
        }
        pizzas_.pop();
        currentPizza = pizzas_.front();
        nbPizzas = getNumberOfPizza(currentPizza);
        pizzaTypeSize = getPizzaTypeSize(currentPizza);
    }
    return 0;
}
