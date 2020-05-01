/*
** EPITECH PROJECT, 2020
** tokeniseString.cpp
** File description:
** tokeniseString
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Tools.hpp"

std::vector<std::string> tokeniseString(std::string const &order, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream check1(order);
    std::string intermediate;

    while(getline(check1, intermediate, delim))
    {
        tokens.push_back(intermediate);
    }
    return (tokens);
}