/*
** EPITECH PROJECT, 2019
** redirectAllStd.cpp
** File description:
** redirection function
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_std(void)
{
    cr_redirect_stderr();
    cr_redirect_stdout();
}
