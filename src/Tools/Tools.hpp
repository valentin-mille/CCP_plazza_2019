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

void displayUsage(void);
bool isCommandLineError(int ac, char **av);
bool isOrderValid(std::vector<std::string> order);
std::queue<std::string> FillQueueOrder(std::vector<std::string> const &OrdersVect);
std::vector<std::string> CleanOrder(std::string const &OrderInput);

#endif /* !TOOLS_HPP */
