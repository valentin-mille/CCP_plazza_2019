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

#include "IPizza.hpp"
#include "APizza.hpp"
#include "Kitchens.hpp"
#include "InterProcessCom.hpp"
#include "Tools.hpp"

class Reception {
    public:
        Reception(float multiplier, int nbOfCooks, int deliveryTime_);
        ~Reception() = default;
        bool launchShell();
        bool getShellActivity();
        bool isOrderValid();

        void displayKitchensStatus(); // [TODO] add the Kitchens
        std::queue<std::string> parseOrder(std::string const &order);
        int createNewKitchenProcess(const APizza &toPrepare);
        int sendPizzaToKitchens();
    private:
        bool shellActive_;
        std::vector<InterProcessCom> streamCom_; // Mutex is not copiable
        std::vector<Kitchens> kitchensProcess_;
        std::vector<std::string> lastOrders_;
        float multiplier_;
        int nbOfCooks_;
        int deliveryTime_;
        std::queue<APizza> pizzas_;
};

#endif /* !RECEPTION_HPP */
