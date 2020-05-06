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
#include "IFood.hpp"

class InterProcessCom {

    enum CommunicationSettings {
        BUFFER_SIZE=1042,
    };

    public:
        InterProcessCom();
        ~InterProcessCom();

        int createPipe();
        std::string readInformations(int fd);
        std::string readReceptionBuffer();
        std::string readKitchenBuffer();
        void writeInformations(const std::string &infos, int fd);
        void writeToKitchenBuffer(const std::string &infos);
        void writeToReceptionBuffer(const std::string &infos);
        static std::string pack(std::string const &order);
        static std::string unpack(std::string const &order);
        // std::string operator<<(std::string const &order);
        // std::string operator>>(std::string const &order);

    private:
        int kitchenFdWrite_;
        int kitchenFdRead_;
        int receptionFdRead_;
        int receptionFdWrite_;
};

#endif
