/*
** EPITECH PROJECT, 2020
** Parser.hpp
** File description:
** Parser.hpp
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <iostream>

#include "../Exception/ExceptionParser.hpp"

class Parser {
    public:
        Parser();
        ~Parser() = default;
        bool getParams(char **input);
        size_t getMultiplier() const;
        size_t getNbCooks() const;
        size_t getTimeRefill() const;
        bool isCommandValid(std::string const &input);
    private:
        size_t _multiplierCooking;
        size_t _nbCooks;
        size_t _timeRefill; // in milliseconds
};

#endif /* !PARSER_HPP */
