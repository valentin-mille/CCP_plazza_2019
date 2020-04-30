/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** Cook.cpp
*/

#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

enum Status
{
    FREE = 0,
    BUSY
};

class Cook {
  private:
    Status _status;
    std::thread _thread;

  public:
    Status getStatus() const;
    void update();
    void initThread();

    Cook(Cook &&) = default;
    Cook();
    ~Cook();
};

void Cook::update()
{
  std::cout << "Pizza cooking" << std::endl;
    // std::conditional_cariable
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Pizza Finish" << std::endl;
}

Status Cook::getStatus() const
{
    return _status;
}

void Cook::initThread()
{
}

Cook::Cook() : _status(FREE), _thread(std::thread([this]() { update(); }))
{
}

Cook::~Cook()
{
}
