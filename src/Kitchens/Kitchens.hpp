/*
** EPITECH PROJECT, 2019
** kitchen.hpp
** File description:
** kitchens test
*/

#ifndef KITCHENS_HPP_
#define KITCHENS_HPP_

#include <algorithm>
#include <csignal>
#include <memory>
#include <unordered_map>
#include <vector>

#include "APizza.hpp"
#include "Cooks.hpp"
#include "Ingredients.hpp"
#include "InterProcessCom.hpp"
#include "clock.hpp"

class Kitchens
{

  public:
    enum Ingredients {
        tomatoe = 0,
        doe,
        gruyere,
        ham,
        mushroom,
        steak,
        egglant,
        goatCheese,
        chiefLove,
        MaxIngre,
        INGREDIENTS_COUNT,
    };

    Kitchens(float multiplier,
            int nbCooks,
            int deliveryTime,
            const InterProcessCom &pipeCom);
    ~Kitchens();

    void update();
    void printStock();

    void resetIngredients();
    void getKitchenStatus();
    void regenerateOneOfEachIngredients();
    bool isCookAvailable() const;
    bool cookPizza(const APizza &toPrepare, size_t &nbPizzas);
    void runCookingProcess(const std::string &pizza, size_t  &nbPizzas);

  private:
    // Add the clock
    const InterProcessCom &pipeCom_;
    float multiplier_;
    int nbCooks_;
    int deliveryTime_;
    std::vector<Cooks> cooks_;
    Clock refoundClock_;
    std::array<int, Ingredients::INGREDIENTS_COUNT> stock_;
    float timeToReplaceIngredients_;
    size_t availableCook_;
};

#endif
