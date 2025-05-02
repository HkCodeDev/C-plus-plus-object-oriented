/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Reservation.h
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <iostream>
#include <string>
#include <iomanip>

namespace seneca {

    class Reservation {
        char reservation_id[11];
        std::string name;
        std::string email;
        int party_size;
        int day;
        int hour;

    public:
        // Default constructor to initialize member variables
        Reservation();
        // Modifier to update the reservation date and time
        void update(int new_day, int new_hour);
        // Constructor that initializes a Reservation object from a string
        Reservation(const std::string& res);
        // Overload of the insertion operator to print the contents of a Reservation object
        friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
    };

}

#endif // RESERVATION_H
