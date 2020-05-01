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
#include <vector>

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
        std::string operator<<(std::vector<std::string> const &order);
        std::string operator>>(std::vector<std::string> const &order);

    private:
        int fdWrite_;
        int fdRead_;
};

#endif
