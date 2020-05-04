/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Kitchen.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include <clock.hpp>
#include <cook/Cook.hpp>
#include <ThreadPool.hpp>
#include <ingredient/Ingredients.hpp>

class Kitchen {
  private:
    std::mutex _stockMutex;
    Clock _inactivityClock;
    Clock _refoundClock;
    float _multiplier;
    int _nbCooks;
    int _deliveryTime;
    ThreadPool _threadPool;
    std::array<int, Ingredients::INGREDIENTS_COUNT> _stock;

  public:
    void update();
    void newPizza();
    void printStock();
    Kitchen(float multiplier, int nbCooks, int deliveryTime);
    ~Kitchen();
};
