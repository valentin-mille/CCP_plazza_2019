/*
** EPITECH PROJECT, 2019
** Cooks.hpp
** File description:
** Cooks class test
*/

#ifndef COOKS_HPP_
#define COOKS_HPP_

class Cooks {
    public:
        Cooks();
        ~Cooks();

        bool isOccupied() const;

    private:
        bool occupied_;

};

#endif
