/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: ConfirmationSender.cpp
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "ConfirmationSender.h"

namespace seneca {

    // Default constructor to initialize member variables
    ConfirmationSender::ConfirmationSender() : m_pReservations(nullptr), m_cnt(0) {}

    // Destructor to deallocate the dynamically allocated array
    ConfirmationSender::~ConfirmationSender() {
        delete[] m_pReservations;
    }

    // Copy constructor to create a deep copy of another ConfirmationSender object using the copy assignment operator
    ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) : ConfirmationSender() {
        *this = other;
    }

    // Copy assignment operator to create a deep copy of another ConfirmationSender object
    ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
        if (this != &other) {
            // Clean-up existing resources
            delete[] m_pReservations;

            // Shallow copy
            m_cnt = other.m_cnt;

            // Deep copy
            if (m_cnt > 0) {
                m_pReservations = new const Reservation * [m_cnt];
                for (size_t i = 0; i < m_cnt; ++i) {
                    m_pReservations[i] = other.m_pReservations[i];
                }
            }
            else {
                m_pReservations = nullptr;
            }
        }
        return *this;
    }

    // Move constructor to transfer ownership of resources from another ConfirmationSender object using the move assignment operator
    ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept : ConfirmationSender() {
        *this = std::move(other);
    }

    // Move assignment operator to transfer ownership of resources from another ConfirmationSender object
    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept {
        if (this != &other) {
            // Clean-up existing resources
            delete[] m_pReservations;

            // Transfer ownership of resources
            m_pReservations = other.m_pReservations;
            m_cnt = other.m_cnt;

            // Nullify the other object's pointers to avoid double deletion
            other.m_pReservations = nullptr;
            other.m_cnt = 0;
        }
        return *this;
    }

    // Overload the += operator to add a Reservation to the array
    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        // Check if the reservation already exists
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_pReservations[i] == &res) {
                return *this;
            }
        }
        // Create a new array with one extra slot
        const Reservation** temp = new const Reservation * [m_cnt + 1];
        for (size_t i = 0; i < m_cnt; ++i) {
            temp[i] = m_pReservations[i];
        }
        temp[m_cnt] = &res; // Add the new reservation
        delete[] m_pReservations;
        m_pReservations = temp;
        ++m_cnt;
        return *this;
    }

    // Overload the -= operator to remove a Reservation from the array
    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
        bool found = false;
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_pReservations[i] == &res) {
                m_pReservations[i] = nullptr;
                found = true;
                break;
            }
        }
        if (!found) return *this;

        // Create a new array with one less slot
        const Reservation** temp = new const Reservation * [m_cnt - 1];
        size_t index = 0;
        for (size_t i = 0; i < m_cnt; ++i) {
            if (m_pReservations[i] != nullptr) {
                temp[index++] = m_pReservations[i];
            }
        }
        delete[] m_pReservations;
        m_pReservations = temp;
        --m_cnt;
        return *this;
    }

    // Overload of the insertion operator to print the content of the ConfirmationSender object
    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender) {
        os << "--------------------------" << std::endl;
        os << "Confirmations to Send" << std::endl;
        os << "--------------------------" << std::endl;
        if (sender.m_cnt == 0) {
            os << "There are no confirmations to send!" << std::endl;
        }
        else {
            for (size_t i = 0; i < sender.m_cnt; ++i) {
                os << *sender.m_pReservations[i];
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }

}
