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

static bool checkNbPizza(std::string &nbPizza)
{
    int convertedNumber = 0;

    if (nbPizza.front() == 'x') {
        nbPizza.erase(nbPizza.begin());
        convertedNumber = atoi(nbPizza.c_str());
        if (convertedNumber > 0) {
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

    std::for_each(order.at(0).begin(), order.at(0).end(), [](char & c) { c = ::tolower(c); });
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

std::string createStringOrder(std::vector<std::string> &input)
{
    size_t i = 0;
    size_t sizeInput = input.size();
    std::string tmp;

    while (i < sizeInput) {
        if (input.at(i) != " ") {
            tmp.append(input.at(i));
            tmp.append(" ");
        }
        i++;
    }
    return (tmp);
}

std::vector <std::string> handleMultipleCommands(std::string const &OrderInput, size_t nbOrder)
{
    std::vector<std::vector<std::string>> OrderTokens;
    std::string intermediate;
    std::stringstream check1(OrderInput);
    std::vector <std::string> tmp;
    std::vector <std::string> tmp2;
    std::vector<std::string> result;
    std::string strClean;
    size_t i = 0;

    while(getline(check1, intermediate, ';'))
    {
        if (intermediate.at(0) == ' ')
            intermediate.erase(0, 1);
        tmp2 = tokeniseString(intermediate, ' ');
        OrderTokens.push_back(tmp2);
    }
    while (i < nbOrder) {
        if (isOrderValid(OrderTokens.at(i))) {
            strClean = createStringOrder(OrderTokens.at(i));
            result.push_back(strClean);
        } else {
            std::cout << "One order is invalid" << std::endl;
        }
        i++;
    }
    return (result);
}

std::vector<std::string> CleanOrder(std::string const &OrderInput)
{
    size_t nbOrder = findNbOrder(OrderInput);
    std::vector <std::string> tmp;
    std::vector<std::string> result;
    std::string strOrder;

    if (nbOrder == 1) {
        tmp = tokeniseString(OrderInput, ' ');
        if (isOrderValid(tmp)) {
            strOrder = createStringOrder(tmp);
            result.push_back(strOrder);
        }
    } else {
        result = handleMultipleCommands(OrderInput, nbOrder);
    }
    return (result);
}
