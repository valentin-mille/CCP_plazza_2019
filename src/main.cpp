/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "Kitchen.hpp"
#include "Regina.hpp"
#include "ThreadPool.hpp"

int main()
{
    Kitchen kitchen(6, 5, 500);


    kitchen.update();
    return 0;
}
