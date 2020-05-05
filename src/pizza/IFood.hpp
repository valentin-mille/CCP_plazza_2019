/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Pizza.hpp
*/

#pragma once
#include <string>
#include <vector>

#include "Ingredients.hpp"

class IFood {
  protected:
    IFood() = default;
  public:
    IFood(IFood const &to_copy) = default;
    IFood(IFood &&to_move) = default;
    virtual ~IFood() = default;
    [[nodiscard]] int virtual getCookingTime() const = 0;
    [[nodiscard]] std::string virtual getTypeString() const = 0;
    [[nodiscard]] int virtual getType() const = 0;
    [[nodiscard]] int virtual getSize() const = 0;
    [[nodiscard]] std::string virtual getSizeString() const = 0;
    [[nodiscard]] std::vector<Ingredients> virtual getIngredients() const = 0;
    [[nodiscard]] std::string virtual getIngredientsString() const = 0;
};
