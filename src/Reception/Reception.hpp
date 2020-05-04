/*
** EPITECH PROJECT, 2020
** Reception.hpp
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <queue>
#include <sched.h>
#include <string>
#include <utility>
#include <vector>

#include "APizza.hpp"
#include "InterProcessCom.hpp"
#include "Kitchens.hpp"
#include "Tools.hpp"

class Reception
{
  public:
    Reception(float multiplier, int nbOfCooks, int deliveryTime_);
    ~Reception() = default;
    bool launchShell();
    bool getShellActivity();
    // bool isOrderValid();

    void displayKitchensStatus(); // [TODO] add the Kitchens
    std::queue<std::string> parseOrder(std::string const &order);
    int createNewKitchenProcess(const std::string &toPrepare, size_t &nbPizzas);
    void FillQueueOrder(std::vector<std::string> const &OrdersVect);
    int sendPizzasToKitchens();
    std::string getPizzaTypeSize(const std::string &currentPizza);
    size_t getNumberOfPizza(std::string const &pizzaString);
    void checkKitchensProcessus();

<<<<<<< HEAD
        void displayKitchensStatus(); // [TODO] add the Kitchens
        void parseOrder(std::string const &order);
        int createNewKitchenProcess(const std::string &toPrepare);
        void FillQueueOrder(std::vector<std::string> const &OrdersVect);
        int sendPizzaToKitchens();
    private:
        std::vector<InterProcessCom> streamCom_; // Mutex is not copiable
        std::vector<Kitchens> kitchensProcess_;
        std::vector<std::string> lastOrders_;
        float multiplier_;
        int nbOfCooks_;
        int deliveryTime_;
        std::queue<std::string> pizzas_;
        bool shellActive_;
=======
  private:
    std::vector<InterProcessCom> streamCom_; // Mutex is not copiable
    std::vector<pid_t> kitchensPid_;
    std::vector<std::string> lastOrders_;
    float multiplier_;
    int nbOfCooks_;
    int deliveryTime_;
    std::queue<std::string> pizzas_;
    bool shellActive_;
>>>>>>> reception
};

#endif /* !RECEPTION_HPP */
