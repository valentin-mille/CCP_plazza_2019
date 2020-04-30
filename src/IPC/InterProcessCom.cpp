/*
** EPITECH PROJECT, 2019
** InterProcessCom
** File description:
** interProcessCom implementation
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "InterProcessCom.hpp"

std::mutex mutex;

InterProcessCom::InterProcessCom()
{
}

InterProcessCom::~InterProcessCom()
{
}

int InterProcessCom::createPipe()
{
    int pfds[2];

    if (pipe(pfds) == -1) {
        std::cerr << "==> Pipe fatal error" << std::endl;
        return 1;
    }
    this->fdRead_ = pfds[0];
    this->fdWrite_ = pfds[1];
    return 0;
}

std::string InterProcessCom::readBuffer()
{
    // The reception has to send a "[1...9][0...9]*[-]" string to work
    bool process = true;
    char buf[BUFFER_SIZE + 1];
    char *end = NULL;
    std::string finalStrSize;
    char *finder = 0;
    size_t i = 0;

    while (process) {
        read(this->fdRead_, buf, BUFFER_SIZE);
        buf[BUFFER_SIZE] = '\0';
        end = buf + sizeof(buf) / sizeof(buf[0]);
        finder = std::find(buf, end, '\n');
        if (finder != std::end(buf)) {
            while (buf[i] != '\n') {
                finalStrSize += buf[i];
                ++i;
            }
            return finalStrSize;
        }
        finalStrSize += buf;
    }
    return "";
}

void InterProcessCom::writeInformations(const std::string &infos)
{
    // Lock the program if a mutex is already blocked
    std::lock_guard<std::mutex> lock(mutex);
    std::string finalStr;

    finalStr += infos + "\n";
    std::cout << "Final str before sending: \"" << finalStr << "\""
              << std::endl;
    // Send the size of the data and data
    write(this->fdWrite_, finalStr.c_str(), finalStr.size());
    // release the locked mutex automatically at the end of the scope
}

void InterProcessCom::readInformations()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string buffer = this->readBuffer();

    std::cout << "result: \"" << buffer << "\"" << std::endl;
}
