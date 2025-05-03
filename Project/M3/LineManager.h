/*****************************************************************************
                  Milestone3 >
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: LineManager.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Workstation.h"

namespace seneca {
    class LineManager {
        // Active line of workstations
        std::vector<Workstation*> m_activeLine;
        // Counter for the number of customer orders
        size_t m_cntCustomerOrder{ 0 };
        // Pointer to the first workstation in the line
        Workstation* m_firstStation{ nullptr };

    public:
        // Constructor
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        // Reorders the stations
        void reorderStations();
        // Runs the assembly line
        bool run(std::ostream& os);
        // Displays the current state of the line
        void display(std::ostream& os) const;
    };
}

#endif // LINE_MANAGER_H
