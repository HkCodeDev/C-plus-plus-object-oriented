/*****************************************************************************
                  Milestone3 >
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: LineManager.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "LineManager.h"

namespace seneca {
    // Constructor
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream infile(file);
        if (!infile) {
            throw std::string("Unable to open [") + file + "] file.";
        }

        std::string record;
        while (std::getline(infile, record)) {
            size_t pos = record.find('|');
            std::string firstStationName = record.substr(0, pos);
            std::string nextStationName = (pos == std::string::npos) ? "" : record.substr(pos + 1);

            Workstation* firstStation = nullptr;
            Workstation* nextStation = nullptr;

            for (auto& station : stations) {
                if (station->getItemName() == firstStationName) {
                    firstStation = station;
                }
                if (station->getItemName() == nextStationName) {
                    nextStation = station;
                }
            }

            if (firstStation) {
                firstStation->setNextStation(nextStation);
                if (std::find(m_activeLine.begin(), m_activeLine.end(), firstStation) == m_activeLine.end()) {
                    m_activeLine.push_back(firstStation);
                }
            }
        }

        // Identify the first station
        for (const auto& station : stations) {
            bool isFirst = true;
            for (const auto& ws : m_activeLine) {
                if (ws->getNextStation() == station) {
                    isFirst = false;
                    break;
                }
            }
            if (isFirst) {
                m_firstStation = station;
                break;
            }
        }

        m_cntCustomerOrder = g_pending.size();
    }
    // Reorders the stations
    void LineManager::reorderStations() {
        std::vector<Workstation*> reorderedLine;
        Workstation* currentStation = m_firstStation;
        while (currentStation) {
            reorderedLine.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }
        m_activeLine = std::move(reorderedLine);
    }
    // Runs the assembly line
    bool LineManager::run(std::ostream& os) {
        static size_t count = 0;
        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        for (auto& station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }
    // Displays the current state of the line
    void LineManager::display(std::ostream& os) const {
        for (const auto& station : m_activeLine) {
            station->display(os);
        }
    }
}
