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
    createPipe();
}

InterProcessCom::~InterProcessCom()
{
}

int InterProcessCom::createPipe()
{
    int pfdsReception[2];
    int pfdsKitchen[2];

    if (pipe(pfdsReception) == -1) {
        std::cerr << "==> Reception pipe fatal error" << std::endl;
        return 1;
    }
    if (pipe(pfdsKitchen) == -1) {
        std::cerr << "==> Kitchen pipe fatal error" << std::endl;
        return 1;
    }
    this->receptionFdRead_ = pfdsReception[0];
    this->receptionFdWrite_ = pfdsReception[1];
    this->kitchenFdRead_ = pfdsKitchen[0];
    this->kitchenFdWrite_ = pfdsKitchen[1];
    return 0;
}

std::string InterProcessCom::readInformations(int fd)
{
    // The reception has to send a "[1...9][0...9]*[-]" string to work
    bool process = true;
    char buf[BUFFER_SIZE + 1];
    char *end = NULL;
    std::string finalStrSize;
    char *finder = 0;
    size_t i = 0;

    while (process) {
        read(fd, buf, BUFFER_SIZE);
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

std::string InterProcessCom::readReceptionBuffer()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string buffer = this->readInformations(this->receptionFdRead_);

    std::cout << "Read result: \"" << buffer << "\"" << std::endl;
    return buffer;
}

std::string InterProcessCom::readKitchenBuffer()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string buffer = this->readInformations(this->kitchenFdRead_);

    std::cout << "Read result: \"" << buffer << "\"" << std::endl;
    return buffer;
}

void InterProcessCom::writeInformations(const std::string &infos, int fd)
{
    // Lock the program if a mutex is already blocked
    std::lock_guard<std::mutex> lock(mutex);
    std::string finalStr;

    finalStr += infos + "\n";
    std::cout << "Final str before sending: \"" << finalStr << "\""
        << std::endl;
    // Send the size of the data and data
    write(fd, finalStr.c_str(), finalStr.size());
    // release the locked mutex automatically at the end of the scope
}

void InterProcessCom::writeToKitchenBuffer(const std::string &infos)
{
    this->writeInformations(infos, this->kitchenFdWrite_);
}

void InterProcessCom::writeToReceptionBuffer(const std::string &infos)
{
    this->writeInformations(infos, this->receptionFdWrite_);
}

