/*****************************************************************************
                  Workshop - #1 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: FoodOrder.h
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>
#include <fstream>

namespace seneca {
    class FoodOrder {
    private:
        // C-style string with space for null terminator
        char customerName[11]; 
        // C-style string with space for null terminator
        char orderDescription[26]; 
        double price;
        bool isSpecial;

    public:
        FoodOrder(); // Default constructor
        void read(std::ifstream& in); // Function to read data from file
        void display() const; // Displays the order information
    };

    extern double g_taxrate;
    extern double g_dailydiscount;
}

#endif // SENECA_FOODORDER_H
