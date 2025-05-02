/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Restaurant.h
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include <iostream>
#include "Reservation.h"

namespace seneca {

    class Restaurant {
        const Reservation** m_pReservations;
        size_t m_cnt;

    public:
        // Default constructor to initialize member variables
        Restaurant();
        // Constructor that takes an array of pointers to 
        // Reservation objects and the count of reservations
        Restaurant(const Reservation* reservations[], size_t cnt);
        // Destructor to deallocate all dynamically 
        // allocated Reservation objects and the array itself
        ~Restaurant();
        // Copy constructor to create a deep copy of 
        // another Restaurant object using the copy assignment operator
        Restaurant(const Restaurant& other);
        // Copy assignment operator to create a 
        // deep copy of another Restaurant object
        Restaurant& operator=(const Restaurant& other);
        // Move constructor to transfer ownership of 
        // resources from another Restaurant object using the move assignment operator
        Restaurant(Restaurant&& other) noexcept;
        // Move assignment operator to transfer 
        // ownership of resources from another Restaurant object
        Restaurant& operator=(Restaurant&& other) noexcept;
        // Returns the number of reservations in the system
        size_t size() const;
        // Overload of the insertion operator to print the content of the Restaurant object
        friend std::ostream& operator<<(std::ostream& os, const Restaurant& res);
    };

}

#endif // RESTAURANT_H
