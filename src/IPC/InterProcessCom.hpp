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

#include "../Tools/Tools.hpp"
#include "IPizza.hpp"

class InterProcessCom {

    enum CommunicationSettings {
        BUFFER_SIZE=1042,
    };

    public:
        InterProcessCom();
        ~InterProcessCom();

        int createPipe();
        std::string readBuffer();
        std::string readInformations();
        void writeInformations(const std::string &infos);
        std::string pack(std::string const &order);
        std::string unpack(std::string const &order);
        // std::string operator<<(std::string const &order);
        // std::string operator>>(std::string const &order);

    private:
        int fdWrite_;
        int fdRead_;
};

#endif
