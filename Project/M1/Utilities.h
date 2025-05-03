/*****************************************************************************
                  Milestone1 
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:Utilities.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
#include <stdexcept>

namespace seneca {
    class Utilities {
        // Member variable to store the width of the field.
        size_t m_widthField = 1;
        // Static member variable to store
        //  the delimiter used for token extraction.
        static char m_delimiter;

    public:
        // Sets the field width to the specified value.
        void setFieldWidth(size_t newWidth);
        // Returns the current field width.
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        // Sets the delimiter to the specified character.
        static void setDelimiter(char newDelimiter);
        // Returns the current delimiter.
        static char getDelimiter();
    };
}

#endif // SENECA_UTILITIES_H
