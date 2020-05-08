/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#include "Kitchen.hpp"
#include <mutex>
#include <string>

template <typename T_object>
std::unique_ptr<IFood> createFood(PizzaSize size)
{
    return std::make_unique<T_object>(size);
}

using food_ctor = std::unique_ptr<IFood> (*)(PizzaSize);

std::vector<std::pair<PizzaType, food_ctor>> const food_creators = {
    {PizzaType::Regina, createFood<ReginaPizza>},
    {PizzaType::Margarita, createFood<MargaritaPizza>},
    {PizzaType::Americana, createFood<AmericanaPizza>},
    {PizzaType::Fantasia, createFood<FantasiaPizza>}};

Kitchen::Kitchen(float multiplier,
                 int nbCooks,
                 int deliveryTime,
                 InterProcessCom &pipeCom)
    : _multiplier(multiplier),
      _nbCooks(nbCooks),
      _deliveryTime(deliveryTime),
      _pipeCom(pipeCom),
      _getPipeInf(true),
      _workingState(true),
      _threadPipe(nullptr)
{
    _refoundClock.reset();
    for (auto &ingredient : _stock)
        ingredient = 5;
    _threadPool.addNewThread(_nbCooks, multiplier);
    _threadPipe = std::make_unique<std::thread>(
        std::thread([this]() { this->pipeComunication(); }));
}

template <typename T>
T operator>>(T& left, T& packedOrder)
{
    left = InterProcessCom::pack(packedOrder);
    return(left);
}

template <typename T>
T operator<<(T& left, T& order)
{
    left = InterProcessCom::unpack(order);
    return(left);
}

void Kitchen::kitchenStatus()
{
    std::vector<Cook> const &cooks = _threadPool.getCooks();
    std::string state;

    for (size_t i = 0; i < cooks.size(); i++) {
        state = (cooks[i].isBusy() == 1) ? "busy" : "free";
        _pipeCom.printOutput("Cook " + std::to_string(i) + ":" + state);
    }
    printStock();
}

void Kitchen::pipeComunication()
{
    std::string buffer;
    while (_getPipeInf) {
        buffer = this->_pipeCom.readKitchenBuffer();
        if (buffer == "status") {
            kitchenStatus();
            this->_pipeCom.writeToReceptionBuffer("OK");
        } else if (buffer == "exit") {
            this->_workingState = false;
            return;
        } else {
            PizzaInf inf = _pipeCom.unpackPizzaInf(buffer);
            newPizza(inf.type, inf.size);
        }
    }
}

int Kitchen::haveIngredients(std::vector<Ingredients> ingredients)
{
    std::lock_guard<std::mutex> lock(_stockMutex);

    for (size_t i = 0; i < ingredients.size(); i++) {
        if (_stock[ingredients[i]] <= 0)
            return 1;
    }
    return 0;
}

void Kitchen::useIngredients(std::vector<Ingredients> ingredients)
{
    std::lock_guard<std::mutex> lock(_stockMutex);

    for (size_t i = 0; i < ingredients.size(); i++) {
        _stock[ingredients[i]] -= 1;
    }
}

void Kitchen::newPizza(PizzaType type, PizzaSize size)
{
    auto iter = std::find_if(
        food_creators.begin(),
        food_creators.end(),
        [&](auto const &obj_creator) { return obj_creator.first == type; });

    if (iter == food_creators.end()) {
    } else {
        std::unique_ptr<IFood> foodPtr = iter->second(size);
        std::vector<Ingredients> ingredients = foodPtr.get()->getIngredients();
        if (haveIngredients(ingredients) == 0 &&
            _threadPool.addOnQueue(std::move(foodPtr)) == 0) {
            _inactivityClock.reset();
            useIngredients(ingredients);
            this->_pipeCom.writeToReceptionBuffer("OK");
        } else {
            this->_pipeCom.writeToReceptionBuffer("KO");
        }
    }
}

int Kitchen::inactivityCheck()
{
    std::vector<Cook> const &cooks = _threadPool.getCooks();
    for (size_t i = 0; i < cooks.size(); i++) {
        if (cooks[i].isBusy() == true)
            return 0;
    }
    if (_inactivityClock.getElapsedTime() > 5000)
        return 1;
    return 0;
}

void Kitchen::update()
{
    while (_workingState) {
        if (inactivityCheck() == 1) {
            return;
        }
        if (_refoundClock.getElapsedTime() >= _deliveryTime) {
            _stockMutex.lock();
            for (auto &ingredient : _stock)
                ingredient += 1;
            _refoundClock.reset();
            _stockMutex.unlock();
        }
    }
}

void Kitchen::printStock()
{
    std::lock_guard<std::mutex> lock(_stockMutex);
    std::array<std::string, INGREDIENTS_COUNT> ingredientString =
    { {"DOE",
       "TOMATO",
       "GRUYERE",
       "MUSHROOMS",
       "HAM",
       "STEACK",
       "EGGPLANT",
       "GOAT_CHEESE",
       "CHIEF_LOVE"} };

    _pipeCom.printOutput("-------------------STOCK-----------------------");
    for (size_t i = 0; i < _stock.size(); i++) {
        _pipeCom.printOutput(std::to_string(_stock[i]) + " :" + ingredientString[i]);
    }
    _pipeCom.printOutput("------------------------------------------------");
}

Kitchen::~Kitchen()
{
    _getPipeInf = false;
    _threadPipe.get()->detach();
    this->_pipeCom.writeToReceptionBuffer("OK");
}
