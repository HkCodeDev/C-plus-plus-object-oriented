#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace seneca {

    class Station {
        int m_id; // the id of the station
        std::string m_itemName; // the name of the item handled by the station
        std::string m_description; // the description of the station
        size_t m_serialNumber; // the next serial number to be assigned to an item at this station
        size_t m_quantity; // the number of items currently in stock

        static size_t m_widthField; // the maximum number of characters required to print to the screen the item name for any object of type Station
        static int id_generator; // a variable used to generate IDs for new instances of type Station

    public:
        // custom 1-argument constructor
        Station(const std::string& record) : m_id(++id_generator) {
            Utilities util;
            size_t next_pos = 0;
            bool more = true;

            m_itemName = util.extractToken(record, next_pos, more);
            m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
            m_quantity = std::stoul(util.extractToken(record, next_pos, more));
            m_description = util.extractToken(record, next_pos, more);

            if (m_widthField < util.getFieldWidth()) {
                m_widthField = util.getFieldWidth();
            }
        }

        // returns the name of the current Station object
        const std::string& getItemName() const {
            return m_itemName;
        }

        // returns the next serial number to be used on the assembly line and increments m_serialNumber
        size_t getNextSerialNumber() {
            return m_serialNumber++;
        }

        // returns the remaining quantity of items in the Station object
        size_t getQuantity() const {
            return m_quantity;
        }

        // subtracts 1 from the available quantity; should not drop below 0.
        void updateQuantity() {
            if (m_quantity > 0) {
                m_quantity--;
            }
        }

        // inserts information about the current object into stream os.
        void display(std::ostream& os, bool full) const {
            os << std::setw(3) << std::setfill('0') << m_id << " | ";
            os << std::setw(15) << std::left << std::setfill(' ') << m_itemName << "| ";
            os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

            if (full) {
                os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " |";
                os << std::left << " " << Utilities::trim(m_description);
            }
            os << std::endl;
        }

    };

}

#endif // STATION_H
