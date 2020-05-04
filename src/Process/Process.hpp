/*
** EPITECH PROJECT, 2019
** Process.hpp
** File description:
** Process class excapsulation
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <wait.h>

class Process
{
  public:
    static int launchProcess();
    static bool isProcessRunning(pid_t pidProcess);
};

#endif
