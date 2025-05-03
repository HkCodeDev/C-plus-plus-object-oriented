/*****************************************************************************
                  Milestone3 >
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Workstation.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Workstation.h"

namespace seneca {
    // Define the global deques
    std::deque<CustomerOrder> g_pending;// Orders waiting to be processed
    std::deque<CustomerOrder> g_completed;// Orders that are completed
    std::deque<CustomerOrder> g_incomplete;// Orders that are incomplete
    // Constructor
    Workstation::Workstation(const std::string& record) : Station(record) {}
    // Fills the current order
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }
    // Attempts to move the order to the next station
    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation) {
                    m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
                }
                else {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }
    // Sets the next station
    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }
    // Gets the next station
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }
    // Displays the workstation details
    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        }
        else {
            os << "End of Line";
        }
        os << std::endl;
    }
    // Adds a new order to the workstation
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
