/*
** EPITECH PROJECT, 2020
** Operators.cpp
** File description:
** Operators.cpp
*/


#include <unordered_map>
#include <vector>
#include <iostream>
#include "InterProcessCom.hpp"
#include "../Tools/Tools.hpp"
#include "APizza.hpp"

// PACK / SERIALIZE
std::string InterProcessCom::pack(std::string const &packedOrder)
{
    size_t control = 0;
    std::vector <std::string> VectOrder = tokeniseString(packedOrder, ' ');
    std::string result;
    std::string tmp;
    std::unordered_map<std::string, char>::iterator it;
    std::unordered_map<std::string, char> typeMap(
        {
            {"regina", PizzaType::Regina},
            {"margarita", Margarita},
            {"americana", Americana},
            {"fantasia", Fantasia}
        }
    );
    std::unordered_map<std::string, char>  sizeMap(
        {
            {"S", S},
            {"M", M},
            {"L", L},
            {"XL", XL},
            {"XXL", XXL}
        }
    );
    // Find Pizza Type
    it = typeMap.find(VectOrder.at(0));
    if (it != typeMap.end()) {
        tmp = std::to_string(it->second);
        result.append(tmp);
        result.append("-");
        control++;
    }
    // Find Pizza Size
    it = sizeMap.find(VectOrder.at(1));
    if (it != typeMap.end()) {
        tmp = std::to_string(it->second);
        result.append(tmp);
        control++;
    }
    if (control == 2)
        return (result);
    return (nullptr);
}

// UNPACK / DESERIALIZE
std::string InterProcessCom::unpack(std::string const &packedOrder)
{
    size_t control = 0;
    std::vector <std::string> VectOrder = tokeniseString(packedOrder, '-');
    std::string result;
    int tmp;
    std::unordered_map<char, std::string>::iterator it;
    std::unordered_map<char, std::string> typeMap(
        {
            {Regina, "regina"},
            {Margarita, "margarita"},
            {Americana, "americana"},
            {Fantasia, "fantasia"}
        }
    );
    std::unordered_map<char, std::string>  sizeMap(
        {
            {S, "S"},
            {M, "M"},
            {L, "L"},
            {XL, "XL"},
            {XXL, "XXL"}
        }
    );

    // Find Pizza Type
    tmp = std::atoi(VectOrder.at(0).c_str());
    for (auto it : typeMap) {
        if (it.first == tmp) {
            result.append(it.second);
            result.append(" ");
            control++;
        }
    }
    // Find Pizza Type
    tmp = std::atoi(VectOrder.at(1).c_str());
    for (auto it : sizeMap) {
        if (it.first == tmp) {
            result.append(it.second);
            control++;
        }
    }
    if (control == 2)
        return (result);
    return (nullptr);
}
