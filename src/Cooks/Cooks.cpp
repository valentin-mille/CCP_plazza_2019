/*
** EPITECH PROJECT, 2019
** Cooks.cpp
** File description:
** Cooks implementation
*/

#include "Cooks.hpp"

Cooks::Cooks()
{
    this->occupied_ = false;
}

Cooks::~Cooks()
{
}

bool Cooks::isOccupied() const
{
    return this->occupied_;
}

void Cooks::setCookStatus(bool status)
{
    this->occupied_ = status;
}
