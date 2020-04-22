/*
** EPITECH PROJECT, 2019
** CPP_plazza_2019
** File description:
** main.cpp
*/

#include "Kitchen.hpp"

int main()
{
    Kitchen kitchen(1, 5, 2000);

    while (1)
    {
        kitchen.update();
    }
    return 0;
}
