/*****************************************************************************
                  Workshop - #1 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: FoodOrder.h
 Date: May 17 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>
#include <fstream>
#include <string>

namespace seneca {
    class FoodOrder {
    private:
        char* customerName; // Dynamic C-style string
        char* orderDescription; // Dynamic C-style string
        double price;
        bool isSpecial;

        void freeMemory();  // Helper to deallocate memory

    public:
        FoodOrder(); // Default constructor
        FoodOrder(const FoodOrder& other); // Copy constructor
        // Copy assignment operator
        FoodOrder& operator=(const FoodOrder& other); 
        ~FoodOrder(); // Destructor
        void read(std::ifstream& in); // Function to read data from file
        void display() const; // Displays the order information
    };

    extern double g_taxrate;
    extern double g_dailydiscount;
}

#endif // SENECA_FOODORDER_H
