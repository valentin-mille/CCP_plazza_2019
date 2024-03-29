/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

#include "Americana.hpp"
#include "Fantasia.hpp"
#include "IFood.hpp"
#include "Ingredients.hpp"
#include "InterProcessCom.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"
#include <Cook.hpp>
#include <ThreadPool.hpp>
#include <clock.hpp>

class Kitchen
{
  private:
    std::mutex _stockMutex;
    Clock _inactivityClock;
    Clock _refoundClock;
    float _multiplier;
    int _nbCooks;
    int _deliveryTime;
    ThreadPool _threadPool;
    std::array<int, Ingredients::INGREDIENTS_COUNT> _stock;
    InterProcessCom &_pipeCom;
    bool _getPipeInf;
    bool _workingState;
    std::unique_ptr<std::thread> _threadPipe;

  public:
    void kitchenStatus();
    int inactivityCheck();
    void update();
    void pipeComunication();
    void newPizza(PizzaType type, PizzaSize size);
    void printStock();
    int haveIngredients(std::vector<Ingredients>);
    void useIngredients(std::vector<Ingredients>);
    Kitchen(float multiplier,
            int nbCooks,
            int deliveryTime,
            InterProcessCom &pipeCom);
    ~Kitchen();
};

template <typename T>
T operator>>(T& left, T& right);

template <typename T>
T operator<<(T& left, T& right);
