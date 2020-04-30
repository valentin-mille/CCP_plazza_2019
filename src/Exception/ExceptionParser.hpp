/*
** EPITECH PROJECT, 2020
** project
** File description:
** Exception Parser
*/

#pragma once

#include <string>
#include "Exception.hpp"

class ExceptionParser : public Exception {
    public:
        ExceptionParser(const std::string &message) throw();
        ~ExceptionParser() = default;
};
