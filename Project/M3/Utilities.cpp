/*****************************************************************************
                  Milestone3 >
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Utilities.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Utilities.h"

namespace seneca {
    // Static member variable to store the delimiter used for token extraction.
    char Utilities::m_delimiter = ',';
    // Sets the field width to the specified value.
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    // Returns the current field width.
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }
    // Extracts the next token from the given string 
    // starting from the specified position.
    // Updates the position to the next character 
    // after the delimiter.
    // Sets the 'more' flag to indicate if there 
    // are more tokens to extract.
    // Throws a runtime error if a token is not found.
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        size_t pos = str.find(m_delimiter, next_pos);
        std::string token = str.substr(next_pos, pos - next_pos);

        if (token.empty()) {
            more = false;
            throw std::runtime_error("No token found");
        }

        next_pos = (pos == std::string::npos) ? str.length() : pos + 1;
        more = (next_pos < str.length());

        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }
    // Sets the delimiter to the specified character.
    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }
    // Returns the current delimiter.
    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
