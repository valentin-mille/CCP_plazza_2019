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

class Parser {
    public:
        Parser();
        ~Parser() = default;
        // get args
        bool getParams();
        size_t getMultiplier() const;
        size_t getNbCooks() const;
        size_t getTimeRefill() const;
        bool verifyCommand();
    private:
        size_t _multiplierCooking;
        size_t _nbCooks;
        size_t _timeRefill; // in milliseconds
};

#endif /* !PARSER_HPP */
