/*****************************************************************************
                  Milestone3 >
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Workstation.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace seneca {
    // Global deques
    extern std::deque<CustomerOrder> g_pending;// Orders waiting to be processed
    extern std::deque<CustomerOrder> g_completed;// Orders that are completed
    extern std::deque<CustomerOrder> g_incomplete;// Orders that are incomplete

    class Workstation : public Station {
        // Orders at this workstation
        std::deque<CustomerOrder> m_orders;
        // Pointer to the next workstation
        Workstation* m_pNextStation{ nullptr };

    public:
        // Constructor
        Workstation(const std::string& record);
        // Fills the current order
        void fill(std::ostream& os);
        // Attempts to move the order to the next station
        bool attemptToMoveOrder();
        // Sets the next station
        void setNextStation(Workstation* station);
        // Gets the next station
        Workstation* getNextStation() const;
        // Displays the workstation details
        void display(std::ostream& os) const;
        // Adds a new order to the workstation
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif // WORKSTATION_H
