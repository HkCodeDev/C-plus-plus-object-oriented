/*****************************************************************************
                  Workshop - #1 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: FoodOrder.cpp
 Date: May 17 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "FoodOrder.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace seneca {
    // Global tax rate and daily discount
    double g_taxrate = 0.13;
    double g_dailydiscount = 1.15;
    // Default constructor initializing members to default values
    FoodOrder::FoodOrder() : customerName(nullptr), orderDescription(nullptr), 
        price(0.0), isSpecial(false) {}
    // Copy constructor for deep copying dynamic members
    FoodOrder::FoodOrder(const FoodOrder& other) : 
        customerName(nullptr), orderDescription(nullptr), price(other.price),
        isSpecial(other.isSpecial) {
        // Deep copy customerName if it exists
        if (other.customerName) {
            customerName = new char[strlen(other.customerName) + 1];
            strcpy(customerName, other.customerName);
        }
        // Deep copy orderDescription if it exists
        if (other.orderDescription) {
            orderDescription = new char[strlen(other.orderDescription) + 1];
            strcpy(orderDescription, other.orderDescription);
        }
    }
    // Assignment operator for deep copying dynamic
    //  members and releasing old memory
    FoodOrder& FoodOrder::operator=(const FoodOrder& other) {
        if (this != &other) {
            freeMemory();// Release existing memory
            price = other.price;
            isSpecial = other.isSpecial;
            // Deep copy customerName if it exists
            if (other.customerName) {
                customerName = new char[strlen(other.customerName) + 1];
                strcpy(customerName, other.customerName);
            }
            // Deep copy orderDescription if it exists
            if (other.orderDescription) {
                orderDescription = new char[strlen(other.orderDescription) + 1];
                strcpy(orderDescription, other.orderDescription);
            }
        }
        return *this;
    }
    // Destructor to release allocated memory
    FoodOrder::~FoodOrder() {
        freeMemory();
    }
    // Function to release dynamically allocated memory
    void FoodOrder::freeMemory() {
        delete[] customerName;
        delete[] orderDescription;
        customerName = nullptr;
        orderDescription = nullptr;
    }
    // Function to read FoodOrder data from an input stream
    void FoodOrder::read(std::ifstream& in) {
        if (in.good()) {
            std::string tempName, tempDesc;
            getline(in, tempName, ',');
            getline(in, tempDesc, ',');
            in >> price;
            char delim;
            in >> delim; // Read the comma separator
            // Read the special status (Y/N)
            char specialStatus;
            in >> specialStatus;
            in.ignore(); // Ignore the newline character
            // Allocate and copy new data
            freeMemory();
            customerName = new char[tempName.length() + 1];
            strcpy(customerName, tempName.c_str());
            orderDescription = new char[tempDesc.length() + 1];
            strcpy(orderDescription, tempDesc.c_str());

            isSpecial = (specialStatus == 'Y');
        }
    }
    // Function to display the FoodOrder details
    void FoodOrder::display() const {
        static int counter = 1;
        std::cout << std::left << std::setw(2) << counter++ << ". ";
        if (customerName == nullptr || customerName[0] == '\0') {
            std::cout << "No Order";
        }
        else {
            double taxedPrice = price * (1 + g_taxrate);
            // Display customer name, order description, and taxed price
            std::cout << std::setw(10) << customerName << "|"
                << std::setw(25) << orderDescription << "|"
                << std::setw(12) << std::fixed << 
                std::setprecision(2) << taxedPrice << "|";
            if (isSpecial) {
                // Calculate and display special price after discount
                double specialPrice = taxedPrice - g_dailydiscount;
                std::cout << std::right << std::setw(13) << specialPrice;
            }
        }
        std::cout << std::endl;
    }
}
