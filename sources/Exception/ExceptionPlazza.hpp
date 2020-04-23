/*
** EPITECH PROJECT, 2020
** ExceptionPlazza.hpp
** File description:
** ExceptionPlazza
*/

#pragma once

#include <string>
#include "Exception.hpp"

class ExceptionPlazza : public Exception {
    public:
        ExceptionPlazza(const std::string &message) throw();
        ~ExceptionPlazza() = default;
};