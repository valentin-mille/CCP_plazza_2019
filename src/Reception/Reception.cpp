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

    for (size_t i = 0; i < nbProcess; ++i) {
        streamCom_[i].writeToKitchenBuffer("exit");
    }
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
        std::cout<< "> ";
        std::getline(std::cin, input);
        if (std::cin.eof() || input == "exit" || input == "quit") {
            std::cout<< "--- quit pizzeria --- " << std::endl;
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
    // print the number the current occupancy of the cooks, as well as theirs
    // stocks of ingredients
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
    InterProcessCom currentStream;
    std::string infos("OK");

    pid = Process::launchProcess();
    if (pid == 0) {
        std::unique_ptr<Kitchen> newKitchen = std::make_unique<Kitchen>(
            multiplier_, nbOfCooks_, deliveryTime_, currentStream);
        newKitchen.get()->update();
        newKitchen.reset();
        std::cout<< "====> END OF KITCHEN" << std::endl;
        // Exit to close the child process and destroy the kitchen
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        debug.printOutput("======> Create New kitchen !");
        streamCom_.emplace_back(currentStream);
        kitchensPid_.push_back(pid);
        while (infos == "OK" && nbPizzas > 0) {
            currentStream.writeToKitchenBuffer(currentPizza);
            infos = currentStream.readReceptionBuffer();
            if (infos == "OK") {
                --nbPizzas;
            }
        }
        debug.printOutput("==> End of kitchens created: " +
                          std::to_string(nbPizzas));
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

    debug.printOutput("===> Nb kitchen processes " +
                      std::to_string(kitchensPid_.size()));
    while (i < kitchensPid_.size()) {
        debug.printOutput("==> Kitchen processes " + std::to_string(i));
        if (Process::isProcessRunning(kitchensPid_[i]) == false) {
            debug.printOutput("Erase pid: " + std::to_string(kitchensPid_[i]));
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
    debug.printOutput(currentPizza);
    size_t nbPizzas = getNumberOfPizza(currentPizza);
    std::string pizzaTypeSize(getPizzaTypeSize(currentPizza));
    std::string infos("OK");
    std::string serializedOrder;

    debug.printOutput("Number of Cook: " + std::to_string(nbOfCooks_));
    checkKitchensProcessus();
    debug.printOutput("=======> There is " + std::to_string(streamCom_.size()) +
                      " Kitchens");
    serializedOrder = InterProcessCom::pack(currentPizza);
    debug.printOutput("Serialized order " + serializedOrder);
    debug.printOutput("Nb Pizzas #1: " + std::to_string(nbPizzas));
    while (nbPizzas > 0) {
        debug.printOutput("Nb Pizzas #2: " + std::to_string(nbPizzas));
        if (streamCom_.empty() == false) {
            for (size_t i = 0; i < streamCom_.size(); ++i) {
                while (infos == "OK" && nbPizzas > 0) {
                    debug.printOutput("======> Kitchen already created ! " +
                                      std::to_string(kitchensPid_[i]));
                    streamCom_[i].writeToKitchenBuffer(serializedOrder);
                    infos = streamCom_[i].readReceptionBuffer();
                    if (infos == "OK" && nbPizzas > 0) {
                        --nbPizzas;
                    }
                }
            }
        }
        debug.printOutput("Nb Pizzas #3: " + std::to_string(nbPizzas));
        if (nbPizzas > 0) {
            if (createNewKitchenProcess(serializedOrder, nbPizzas)) {
                return 1;
            }
        }
    }
    debug.printOutput("=======> #2 There is " +
                      std::to_string(streamCom_.size()) + " Kitchens");
    pizzas_.pop();
    return 0;
}
