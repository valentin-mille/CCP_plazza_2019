/*
** EPITECH PROJECT, 2019
** testsParseCommandLine.cpp
** File description:
** tests functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>

#include "Tools.hpp"

Test(TestIsCommandLineError0, returnTrue)
{
    int ac = 4;
    const char *av[] = {"program", "2", "5", "2000"};

    cr_assert_eq(isCommandLineError(ac, (char **)av), false);
}

Test(TestIsCommandLineError1, returnFalse)
{
    int ac = 4;
    char *av[] = {"program", "2", "0", "2000"};

    cr_assert_eq(isCommandLineError(ac, (char **)av), true);
}
