/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** APizza.hpp
*/

#pragma once
#include <algorithm>
#include <array>
#include <utility>

#include <IFood.hpp>

enum PizzaType
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class APizza : public IFood {
  protected:
    double _cookingTime;
    double _modifer;
    PizzaSize _size;
    PizzaType _type;
    std::vector<Ingredients> _ingredients;

  public:
    [[nodiscard]] double getCookingTime() const override;
    [[nodiscard]] int getType() const override;
    [[nodiscard]] std::string getTypeString() const override;
    [[nodiscard]] int getSize() const override;
    [[nodiscard]] std::string getSizeString() const override;
    [[nodiscard]] std::vector<Ingredients> getIngredients() const override;
    [[nodiscard]] std::string getIngredientsString() const override;
    APizza(PizzaSize);
    ~APizza();
};

double APizza::getCookingTime() const
{
    return _cookingTime;
}

std::string APizza::getIngredientsString() const
{
    std::array<std::pair<Ingredients, std::string>,
        Ingredients::INGREDIENTS_COUNT> const enumString = {{{Ingredients::DOE,
                                                                 "DOE"},
        {Ingredients::TOMATO, "TOMATO"}, {Ingredients::GRUYERE, "GRUYERE"},
        {Ingredients::MUSHROOMS, "MUSHROOMS"}, {Ingredients::HAM, "HAM"},
        {Ingredients::STEACK, "STEACK"}, {Ingredients::EGGPLANT, "EGGPLANT"},
        {Ingredients::GOAT_CHEESE, "GOAT_CHEESE"},
        {Ingredients::CHIEF_LOVE, "CHIEF_LOVE"}}};

    auto iter = std::find_if(enumString.begin(), enumString.end(),
        [&](auto const &entry) { return this->_ingredients[0] == entry.first; });
    if (!iter)
        return "NONE";
    else
        return iter->second;
}

std::vector<Ingredients> APizza::getIngredients() const
{
    return _ingredients;
}

std::string APizza::getSizeString() const
{
    std::array<std::pair<PizzaSize, std::string>, 5> const enumString = {
        {{PizzaSize::S, "S"}, {PizzaSize::M, "M"}, {PizzaSize::L, "L"},
            {PizzaSize::XL, "XL"}, {PizzaSize::XXL, "XXL"}}};

    auto iter = std::find_if(enumString.begin(), enumString.end(),
        [&](auto const &entry) { return this->_size == entry.first; });
    if (!iter)
        return "NONE";
    else
        return iter->second;
}

int APizza::getSize() const
{
    return _size;
}

std::string APizza::getTypeString() const
{
    std::array<std::pair<PizzaType, std::string>, 4> const enumString = {
        {{PizzaType::Regina, "Regina"}, {PizzaType::Margarita, "Margarita"},
            {PizzaType::Americana, "Americana"},
            {PizzaType::Fantasia, "Fantasia"}}};

    auto iter = std::find_if(enumString.begin(), enumString.end(),
        [&](auto const &entry) { return this->_type == entry.first; });
    if (!iter)
        return "NONE";
    else
        return iter->second;
}

int APizza::getType() const
{
    return _type;
}

APizza::APizza(PizzaSize size) : _size(size)
{
}

APizza::~APizza()
{
}
