/*****************************************************************************
                  Workshop - #1 (Part - 1)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: FoodOrder.cpp
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "FoodOrder.h"
#include <iostream>
#include <iomanip>

namespace seneca {

    double g_taxrate = 0.13; // Initial global tax rate
    double g_dailydiscount = 1.15; // Initial global daily discount

    FoodOrder::FoodOrder() : price(0.0), isSpecial(false) {
        customerName[0] = '\0';
        orderDescription[0] = '\0';
    }
    // Function to read FoodOrder data from an input stream
    void FoodOrder::read(std::ifstream& in) {
        if (in.good()) {
      in.getline(customerName, 11, ',');
            in.getline(orderDescription, 26, ',');
            in >> price;
            char delim;
            in >> delim; // Read the comma separator
            char specialStatus;
            in >> specialStatus;
            in.ignore(); // Ignore the newline character

            isSpecial = (specialStatus == 'Y');
        }
    }
    // Function to display the FoodOrder details
    void FoodOrder::display() const {
        // Static variable to keep track of calls to this function
        static int counter = 1; 

        std::cout << std::left << std::setw(2) << counter++ << ". ";
        if (customerName[0] == '\0') {
            std::cout << "No Order";
        }
        else {
            double taxedPrice = price * (1 + g_taxrate);
            std::cout << std::setw(10) << customerName << "|"
                << std::setw(25) << orderDescription << "|"
                << std::setw(12) << std::fixed <<
                std::setprecision(2) << taxedPrice << "|";
            if (isSpecial) {
                double specialPrice = taxedPrice - g_dailydiscount;
                std::cout << std::right << std::setw(13) << specialPrice;
            }
        }
        std::cout << std::endl;
    }

}
