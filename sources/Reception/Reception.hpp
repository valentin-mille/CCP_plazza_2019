/*
** EPITECH PROJECT, 2020
** Reception.hpp
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <string>
#include <utility>
#include <vector>
#include <queue>

#include "Definitions.hpp"
#include "Pizza.hpp"
#include "Kitchens.hpp"
#include "InterProcessCom.hpp"

class Reception {
    public:
        Reception(int nbOfCooks);
        ~Reception() = default;
        bool launchShell();
        bool getShellActivity();
        bool isOrderValid();

        void displayKitchensStatus(); // [TODO] add the Kitchens
        void parseOrder(std::string const &order);
        int createNewKitchenProcess(const Pizza &toPrepare);
        int sendPizzaToKitchens();
    private:
        bool shellActive_;
        std::vector<InterProcessCom> streamCom_; // Mutex is not copiable
        std::vector<Kitchens> kitchensProcess_;
        std::vector<std::string> lastOrders_;
        float cookingTime_;
        size_t nbOfCooks_;
        std::queue<Pizza> pizzas_;
};

std::vector<std::vector<std::string>> CleanOrder(std::string const &OrderInput);

#endif /* !RECEPTION_HPP */
