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
        Reception();
        ~Reception() = default;
        bool launchShell();
        bool getShellActivity();
        bool isOrderValid();

        void displayKitchensStatus(); // [TODO] add the Kitchens
        void parseOrder(std::string const &order);
    private:
        bool shellActive_;
        std::vector<InterProcessCom> streamCom_;
        std::vector<Kitchens> kitchens_;
        std::vector<std::string> lastOrders_;
        float cookingTime_;
        std::queue<Pizza> pizzas_;
};

std::vector<std::vector<std::string>> CleanOrder(std::string const &OrderInput);

#endif /* !RECEPTION_HPP */
