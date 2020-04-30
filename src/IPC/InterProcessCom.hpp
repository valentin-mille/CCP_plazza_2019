/*
** EPITECH PROJECT, 2019
** InterProcessCom.hpp
** File description:
** Encapsulation class for IPC
*/

#ifndef INTERPROCESSCOM_HPP_
#define INTERPROCESSCOM_HPP_

#include <string>
#include <mutex>

class InterProcessCom {

    enum CommunicationSettings {
        BUFFER_SIZE=1042,
    };

    public:
        InterProcessCom();
        ~InterProcessCom();

        int createPipe();
        std::string readBuffer();
        void readInformations();
        void writeInformations(const std::string &infos);

    private:
        int fdWrite_;
        int fdRead_;
};

#endif
