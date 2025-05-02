/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Restaurant.cpp
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Restaurant.h"

namespace seneca {

    // Default constructor to initialize member variables
    Restaurant::Restaurant() : m_pReservations(nullptr), m_cnt(0) {}

    // Constructor that takes an array of pointers to Reservation objects and the count of reservations
    Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_cnt(cnt) {
        m_pReservations = new const Reservation * [cnt];
        for (size_t i = 0; i < cnt; ++i) {
            m_pReservations[i] = new Reservation(*reservations[i]);
        }
    }

    // Destructor to deallocate all dynamically allocated 
    // Reservation objects and the array itself
    Restaurant::~Restaurant() {
        for (size_t i = 0; i < m_cnt; ++i) {
            delete m_pReservations[i];
        }
        delete[] m_pReservations;
    }

    // Copy constructor to create a deep copy of another Restaurant
    //  object using the copy assignment operator
    Restaurant::Restaurant(const Restaurant& other) : Restaurant() {
        *this = other;
    }

    // Copy assignment operator to create a deep 
    // copy of another Restaurant object
    Restaurant& Restaurant::operator=(const Restaurant& other) {
        if (this != &other) {
            // Clean-up existing resources
            for (size_t i = 0; i < m_cnt; ++i) {
                delete m_pReservations[i];
            }
            delete[] m_pReservations;

            // Shallow copy
            m_cnt = other.m_cnt;

            // Deep copy
            if (m_cnt > 0) {
                m_pReservations = new const Reservation * [m_cnt];
                for (size_t i = 0; i < m_cnt; ++i) {
                    m_pReservations[i] = new Reservation(*other.m_pReservations[i]);
                }
            }
            else {
                m_pReservations = nullptr;
            }
        }
        return *this;
    }

    // Move constructor to transfer ownership of resources
    //  from another Restaurant object using the move assignment operator
    Restaurant::Restaurant(Restaurant&& other) noexcept : Restaurant() {
        *this = std::move(other);
    }

    // Move assignment operator to transfer ownership 
    // of resources from another Restaurant object
    Restaurant& Restaurant::operator=(Restaurant&& other) noexcept {
        if (this != &other) {
            // Clean-up existing resources
            for (size_t i = 0; i < m_cnt; ++i) {
                delete m_pReservations[i];
            }
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

    // Returns the number of reservations in the system
    size_t Restaurant::size() const {
        return m_cnt;
    }

    // Overload of the insertion operator to print the content of the
    //  Restaurant object
    std::ostream& operator<<(std::ostream& os, const Restaurant& res) {
        static int call_cnt = 0;
        ++call_cnt;

        os << "--------------------------" << std::endl;
        os << "Fancy Restaurant (" << call_cnt << ")" << std::endl;
        os << "--------------------------" << std::endl;
        if (res.m_cnt == 0) {
            os << "This restaurant is empty!" << std::endl;
        }
        else {
            for (size_t i = 0; i < res.m_cnt; ++i) {
                os << *res.m_pReservations[i];
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }

}
