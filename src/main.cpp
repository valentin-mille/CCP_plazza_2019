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
    Kitchen kitchen(1, 5, 2000);
    ReginaPizza myRegina(PizzaSize::M);

    std::cout << myRegina.getTypeString() << std::endl;
    std::cout << myRegina.getSizeString() << std::endl;

    kitchen.update();
    return 0;
}
