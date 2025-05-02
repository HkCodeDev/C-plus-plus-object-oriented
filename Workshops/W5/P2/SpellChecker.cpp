/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: SpellChecker.cpp
 Date: June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "SpellChecker.h"
#include <iomanip>
#include <algorithm>
#include <iterator>

namespace seneca {
    // Helper function implementation
    std::string SpellChecker::trim(const std::string& str) const {
        size_t start = str.find_first_not_of(" ");
        size_t end = str.find_last_not_of(" ");
        return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Constructor implementation
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            throw "Bad file name!";
        }

        std::string line;
        size_t index = 0;
        while (std::getline(file, line) && index < 6) {
            size_t pos = line.find(' ');
            m_badWords[index] = line.substr(0, pos);
            m_goodWords[index] = line.substr(pos + 1);
            m_replacements[index] = 0;
            ++index;
        }
    }

    // Operator() implementation
    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < m_badWords.size(); ++i) {
            size_t pos = text.find(m_badWords[i]);
            while (pos != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos = text.find(m_badWords[i], pos + m_goodWords[i].length());
            }
        }

        // Remove extra spaces after replacements
        auto it = std::unique(text.begin(), text.end(), [](char a, char b) {
            return isspace(a) && isspace(b);
            });
        text.erase(it, text.end());

        // Trim spaces after replacements
        text = trim(text);
    }

    // showStatistics implementation
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < m_badWords.size(); ++i) {
            out << std::setw(15) << m_badWords[i] << ": " << m_replacements[i] << " replacements\n";
        }
    }
}
