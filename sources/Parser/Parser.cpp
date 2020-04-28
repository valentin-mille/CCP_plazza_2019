/*
** EPITECH PROJECT, 2020
** Parser.cpp
** File description:
** Parser.cpp
*/

#include <cstring>
#include <iostream>
#include "Parser.hpp"

Parser::Parser()
{
    this->_multiplierCooking = 0;
    this->_nbCooks = 0;
    this->_timeRefill = 0;
}

bool Parser::getParams(char **input)
{
    if (input) {
        this->_multiplierCooking = atoi(input[1]);
        this->_nbCooks = atoi(input[2]);
        this->_timeRefill = atoi(input[3]);
        return (true);
    }
    throw ExceptionParser("Parser error: input");
}

size_t Parser::getNbCooks() const
{
    return (this->_nbCooks);
}

size_t Parser::getMultiplier() const
{
    return (this->_multiplierCooking);
}

size_t Parser::getTimeRefill() const
{
    return (this->_timeRefill);
}