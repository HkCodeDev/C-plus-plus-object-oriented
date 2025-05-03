/*****************************************************************************
                  Milestone2
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:CustomerOrder.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Station.h"
#include "Utilities.h"

namespace seneca {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;

        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& record);

        // Copy operations are not allowed
        CustomerOrder(const CustomerOrder& other);
        CustomerOrder& operator=(const CustomerOrder& other) = delete;

        // Move constructor
        CustomerOrder(CustomerOrder&& other) noexcept;

        // Move assignment operator
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;

        // Destructor
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif // CUSTOMER_ORDER_H
