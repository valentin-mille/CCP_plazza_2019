/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#include "Kitchen.hpp"

template <typename T_object> std::unique_ptr<IFood> createFood(PizzaSize size)
{
    return std::make_unique<T_object>(size);
}

using food_ctor = std::unique_ptr<IFood> (*)(PizzaSize);

std::vector<std::pair<PizzaType, food_ctor>> const food_creators = {
    {PizzaType::Regina, createFood<ReginaPizza>}};

Kitchen::Kitchen(float multiplier, int nbCooks, int deliveryTime, const InterProcessCom &pipeCom)
    : _multiplier(multiplier), _nbCooks(nbCooks), _deliveryTime(deliveryTime), _pipeCom(pipeCom)
{
    _threadPool.addNewThread(_nbCooks, multiplier);
    _refoundClock.reset();
    for (auto &ingredient: _stock)
        ingredient = 5;
}

int Kitchen::haveIngredients(std::vector<Ingredients> ingredients)
{
    for (size_t i = 0; i < ingredients.size(); i++) {
        if (_stock[ingredients[i]] <= 0)
            return 1;
    }
    return 0;
}

void Kitchen::useIngredients(std::vector<Ingredients> ingredients)
{
    for (size_t i = 0; i < ingredients.size(); i++)
        _stock[ingredients[i]] -= 1;
}

void Kitchen::newPizza(PizzaType type, PizzaSize size)
{
    auto iter = std::find_if(food_creators.begin(), food_creators.end(),
        [&](auto const &obj_creator) { return obj_creator.first == type; });

    if (iter == food_creators.end()) {
    } else {
        std::unique_ptr<IFood> foodPtr = iter->second(size);
        std::vector<Ingredients> ingredients = foodPtr.get()->getIngredients();
        if (haveIngredients(ingredients) == 0 &&
            _threadPool.addOnQueue(std::move(foodPtr)) == 0) {
            _inactivityClock.reset();
            useIngredients(ingredients);
        }
    }
}

void Kitchen::update()
{
    while (1) {
        if (_inactivityClock.getElapsedTime() > 5000) {
            std::cout << "Log: kitchenClose" << std::endl;
            return;
        }
        if (_refoundClock.getElapsedTime() >= _deliveryTime) {
            _stockMutex.lock();
            for (auto &ingredient: _stock)
                ingredient += 1;
            _refoundClock.reset();
            _stockMutex.unlock();
            printStock();
        }
    }
}

void Kitchen::printStock()
{
    std::cout << "-------------------STOCK-----------------------" << std::endl;
    for (auto &ingredient: _stock)
        std::cout << ingredient << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

Kitchen::~Kitchen()
{
}
