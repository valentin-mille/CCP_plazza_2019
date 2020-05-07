/*
** EPITECH PROJECT, 2020
** Usage.cpp
** File description:
** Usage.cpp
*/

#include <iostream>
#include "../Exception/Exception.hpp"

void displayUsage(void)
{
    std::cout<< "USAGE:" << std::endl;
    std::cout<< "\t./plazza multiplier cooks time\n" << std::endl;
    std::cout<< "DESCRIPTION" << std::endl;
    std::cout<< "\t multiplier : multiplier for cooking time"
     << std::endl;
    std::cout<< "\t cooks : number of cooks per kitchen" << std::endl;
    std::cout<< "\t time : time in milliseconds, "
    "used by the kitchen to replace ingredients in stock" << std::endl;
}