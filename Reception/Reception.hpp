/*
** EPITECH PROJECT, 2020
** Reception.hpp
** File description:
** Reception.hpp
*/

#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <string>
#include "Definitions.hpp"

class Reception {
    public:
        Reception();
        ~Reception() = default;
        bool isOrderValid();
        bool isShellActive();
    private:
        bool shellActive;
        std::string _lastOrder;
};

#endif /* !RECEPTION_HPP */