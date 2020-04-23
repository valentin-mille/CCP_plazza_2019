/*
** EPITECH PROJECT, 2020
** Reception.hpp
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <string>
#include <vector>
#include "Definitions.hpp"

class Reception {
    public:
        Reception();
        ~Reception() = default;
        bool launchShell();
        bool getShellActivity();
        bool isOrderValid();
    private:
        bool _shellActive;
        std::vector<std::string> _lastOrders;
        float cookingTime_;
};

#endif /* !RECEPTION_HPP */
