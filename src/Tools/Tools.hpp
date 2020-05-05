/*
** EPITECH PROJECT, 2020
** Tools.hpp
** File description:
** Tools.hpp
*/

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <vector>
#include <queue>
#include <string>

void displayUsage(void);
bool isCommandLineError(int ac, char **av);
bool isOrderValid(std::vector<std::string> order);
std::vector<std::string> CleanOrder(std::string const &OrderInput);
int getCountPizza(std::string &nbPizza);
std::vector<std::string> tokeniseString(std::string const &order, char delim);

#endif /* !TOOLS_HPP */
