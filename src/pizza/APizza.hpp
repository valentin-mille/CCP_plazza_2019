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
    [[nodiscard]] int getCookingTime() const override;
    [[nodiscard]] int getType() const override;
    [[nodiscard]] std::string getTypeString() const override;
    [[nodiscard]] int getSize() const override;
    [[nodiscard]] std::string getSizeString() const override;
    [[nodiscard]] std::vector<Ingredients> getIngredients() const override;
    [[nodiscard]] std::string getIngredientsString() const override;
    APizza(PizzaSize);
    ~APizza();
    APizza(APizza const &to_copy) = default;
    APizza(APizza &&to_move) = default;
};

