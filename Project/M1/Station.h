/*****************************************************************************
                  Milestone1
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:Station.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace seneca {
    class Station {
        int id;
        std::string itemName;
        std::string description;
        size_t nextSerialNumber;
        size_t quantity;

        static size_t m_widthField;
        static int id_generator;

    public:
        Station(const std::string& record);

        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SENECA_STATION_H
