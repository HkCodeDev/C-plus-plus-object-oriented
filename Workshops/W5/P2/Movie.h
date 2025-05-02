/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Movie.h
 Date: June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>

namespace seneca {

    class Movie {
        std::string m_title;
        int m_year;
        std::string m_description;

    public:
        // Default constructor
        Movie();
        // Parameterized constructor 
        Movie(const std::string& strMovie);
        // Returns the title of the movie
        const std::string& title() const;
        // Returns the year of the movie
        int year() const;
        // Returns the description of the movie
        const std::string& description() const;
        // Fix the spelling
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_title);
            spellChecker(m_description);
        }
        // Overloaded operator<<
        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };

}

#endif
