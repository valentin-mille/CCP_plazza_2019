/*
** EPITECH PROJECT, 2020
** FillQueueOrder.cpp
** File description:
** FillQueueOrder.cpp
*/

#include <string>
#include <iostream>
#include "Tools.hpp"

std::queue<std::string> FillQueueOrder(std::vector<std::string> const &OrdersVect)
{
    std::queue <std::string> QueueOrder;
    int size = OrdersVect.size();
    int i = 0;

    if (size == 1) {
        QueueOrder.push(OrdersVect.at(0));
    } else {
        while (i < size) {
            QueueOrder.push(OrdersVect.at(i));
            i++;
        }
    }
    return (QueueOrder);
}