/*****************************************************************************
                  Milestone2
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:Station.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Station.h"

namespace seneca {
    // Static member variable to store the width of the field.
    size_t Station::m_widthField = 0;
    // Static member variable to generate
    int Station::id_generator = 0;
    // Constructor that initializes a Station 
    // object from a record string.
    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        itemName = util.extractToken(record, next_pos, more);
        nextSerialNumber = std::stoul(util.extractToken(record, next_pos, more));
        quantity = std::stoul(util.extractToken(record, next_pos, more));
        description = util.extractToken(record, next_pos, more);

        id = ++id_generator;

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }
    // Returns the item name of the station.
    const std::string& Station::getItemName() const {
        return itemName;
    }
    // Returns the next serial number and increments it.
    size_t Station::getNextSerialNumber() {
        return nextSerialNumber++;
    }
    // Returns the quantity of items in the station.
    size_t Station::getQuantity() const {
        return quantity;
    }
    // Decrements the quantity of 
    // items by one, if it is greater than zero.
    void Station::updateQuantity() {
        if (quantity > 0) {
            --quantity;
        }
    }
    // Displays the station information to the given output stream.
    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << id << " | "
            << std::setw(14) << std::left << std::setfill(' ') << itemName << " | "
            << std::setw(6) << std::setfill('0') << std::right << nextSerialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << std::right << quantity << " | "
                << description;
        }

        os << std::endl;
    }
}
