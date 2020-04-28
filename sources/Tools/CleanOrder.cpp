/*
** EPITECH PROJECT, 2020
** CleanOrder.cpp
** File description:
** CleanOrder.cpp
*/

#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "../Reception/Reception.hpp"
#include "../Exception/ExceptionParser.hpp"

size_t findNbOrder(std::string const &input)
{
    size_t result = 0;

    result = std::count(input.begin(), input.end(), ';') + 1;
    return (result);
}

bool checkNbPizza(std::string &nbPizza)
{
    if (nbPizza.front() == 'x') {
        nbPizza.erase(nbPizza.begin());
        if (atoi(nbPizza.c_str()) > 0) {
            return (true);
        }
        return (false);
    }
    return (false);
}

bool isOrderValid(std::vector<std::string> order)
{
    size_t checker = 0;
    std::vector<std::string> recipes = {"regina", "fantasia", "margarita", "americana"};
    std::vector<std::string> sizes = {"S", "M", "L", "XL", "XXL"};

    if (order.size() != 3)
        return (false);
    auto it = std::find(recipes.begin(), recipes.end(), order.at(0));
    if (it != recipes.end()) {
        checker++;
    }
    it = std::find(sizes.begin(), sizes.end(), order.at(1));
    if (it != sizes.end()) {
        checker++;
    }
    if (checkNbPizza(order.at(2)))
        checker++;
    if (checker == 3)
        return (true);
    return (false);
}

std::vector<std::string> tokeniseString(std::string const &order)
{
    std::vector<std::string> tokens;
    std::stringstream check1(order);
    std::string intermediate;

    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return (tokens);
}

std::vector<std::vector<std::string>> CleanOrder(std::string const &OrderInput)
{
    size_t nbOrder = findNbOrder(OrderInput);
    std::vector <std::string> tmp;
    std::vector<std::vector<std::string>> result;

    if (nbOrder == 1) {
        tmp = tokeniseString(OrderInput);
        if (isOrderValid(tmp))
            result.push_back(tmp);
        return (result);
    }
    while (nbOrder > 0) {
        tmp = tokeniseString(OrderInput);
        nbOrder--;
    }
    return (result);
}
