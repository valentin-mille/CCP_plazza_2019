/*
** EPITECH PROJECT, 2019
** Process.cpp
** File description:
** Process class implementation
*/

#include <iostream>
#include <unistd.h>
#include <wait.h>

#include "Process.hpp"

int Process::launchProcess()
{
    return fork();
}

bool Process::isProcessRunning(pid_t pidProcess)
{
    pid_t ret;
    int status;

    ret = waitpid(pidProcess, &status, WNOHANG);
    std::cout << "-----> Waitpid return: " << ret << std::endl;
    if (ret == 0) {
        return true;
    } else if (WIFEXITED(status) == true) {
        std::cout << "Kitchen exit status: " << WEXITSTATUS(status) << std::endl;
        return false;
    }
    return false;
}

void Process::waitResponse(pid_t toWait)
{
    waitpid(toWait, NULL, 0);
}
