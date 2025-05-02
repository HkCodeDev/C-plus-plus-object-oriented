/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: ConfirmationSender.h
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include <iostream>
#include "Reservation.h"

namespace seneca {

    class ConfirmationSender {
        const Reservation** m_pReservations;
        size_t m_cnt;

    public:
        // Default constructor to initialize member variables
        ConfirmationSender();
        // Destructor to deallocate the dynamically allocated array
        ~ConfirmationSender();
        // Copy constructor to create a deep copy of another 
        // ConfirmationSender object using the copy assignment operator
        ConfirmationSender(const ConfirmationSender& other);
        // Copy assignment operator to create a deep copy of another
        //  ConfirmationSender object
        ConfirmationSender& operator=(const ConfirmationSender& other);
        // Move constructor to transfer ownership of resources from 
        // another ConfirmationSender object using the move assignment operator
        ConfirmationSender(ConfirmationSender&& other) noexcept;
        // Move assignment operator to transfer 
        // ownership of resources from another ConfirmationSender object
        ConfirmationSender& operator=(ConfirmationSender&& other) noexcept;
        // Overload the += operator to add a Reservation to the array
        ConfirmationSender& operator+=(const Reservation& res);
        // Overload the -= operator to remove a Reservation from the array
        ConfirmationSender& operator-=(const Reservation& res);
        // Overload of the insertion operator to print the content of the
        //  ConfirmationSender object
        friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender);
    };

}

#endif // CONFIRMATIONSENDER_H
