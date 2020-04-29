/*
** EPITECH PROJECT, 2019
** Kitchens.hpp
** File description:
** kitchens test
*/

#ifndef KITCHENS_HPP_
#define KITCHENS_HPP_

#include <algorithm>
#include <csignal>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Cooks.hpp"
#include "Pizza.hpp"
#include "InterProcessCom.hpp"

class Kitchens
{

    enum Ingredients {
        tomatoe=0,
        doe,
        gruyere,
        ham,
        mushroom,
        steak,
        egglant,
        goatCheese,
        chiefLove,
        MaxIngre,
    };

  public:
    Kitchens(int nbOfCooks, const InterProcessCom &pipeCom);
    ~Kitchens();

    void resetIngredients();
    void regenerateOneOfEachIngredients();
    bool isCookAvailable() const;
    bool cookPizza(const Pizza &toPrepare);
    int runCookingProcess(const Pizza &pizza);

  private:
    // Add the clock
    size_t nbOfCooks_;
    const InterProcessCom &pipeCom_;
    std::vector<Cooks> cooks_;
    std::unordered_map<std::size_t, int> available_ingr_;
    float timeToReplaceIngredients_;
};

#endif
