/*
** EPITECH PROJECT, 2019
** testsParseCommandLine.cpp
** File description:
** tests functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <vector>
#include <string>

#include "Tools.hpp"
#include "InterProcessCom.hpp"

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

Test(TestValidOrder1, returnTrue)
{
    std::vector<std::string> order = {"regina", "XL", "x2"};

    cr_assert_eq(isOrderValid(order), true);
}

Test(TestValidOrder2, returnFalse)
{
    std::vector<std::string> order = {"4fromages", "XL", "x2"};

    cr_assert_eq(isOrderValid(order), false);
}

Test(TestValidOrder3, returnFalse)
{
    std::vector<std::string> order = {"regina", "xxs", "x2"};

    cr_assert_eq(isOrderValid(order), false);
}

Test(TestValidOrder4, returnFalse)
{
    std::vector<std::string> order = {"regina", "S", "1"};

    cr_assert_eq(isOrderValid(order), false);
}

Test(TestSerialize1, returnTrue)
{
    InterProcessCom process;

    cr_assert_eq(process.pack("regina S x2"), "1-1");
}

Test(TestSerialize4, returnTrue)
{
    InterProcessCom process;

    cr_assert_eq(process.unpack("1-1"), "regina S");
}
