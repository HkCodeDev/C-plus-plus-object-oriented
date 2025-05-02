/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: SpellChecker.h
 Date: June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>
#include <fstream>
#include <array>

namespace seneca {
    class SpellChecker {
        std::array<std::string, 6> m_badWords;
        std::array<std::string, 6> m_goodWords;
        std::array<int, 6> m_replacements{};

        // Helper function to trim spaces from both ends of a string
        std::string trim(const std::string& str) const;

    public:
        // Constructor 
        SpellChecker(const char* filename);
        // Operator() implementation
        void operator()(std::string& text);
        // showStatistics implementation
        void showStatistics(std::ostream& out) const;
    };
}

#endif
