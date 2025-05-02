/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Movie.cpp
 Date:June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Movie.h"
#include <iomanip>

namespace seneca {
    // Default constructor that initializes the year to 0
    Movie::Movie() : m_year(0) {}
    // Parameterized constructor that initializes a Movie object from a comma-separated string
    Movie::Movie(const std::string& strMovie) {
        size_t start = 0;
        size_t end = strMovie.find(',');
        
        // Extract the title from the string
        m_title = strMovie.substr(start, end - start);
        start = end + 1;
        end = strMovie.find(',', start);
        // Extract the year from the string and convert it to an int
        m_year = std::stoi(strMovie.substr(start, end - start));
        start = end + 1;
        // Extract the description from the string
        m_description = strMovie.substr(start);

        // Lambda function to trim leading and trailing spaces from a string
        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" "));
            str.erase(str.find_last_not_of(" ") + 1);
            };

        trim(m_title);
        trim(m_description);
    }
    // Returns the title of the movie
    const std::string& Movie::title() const {
        return m_title;
    }
    // Returns the year of the movie
    int Movie::year() const {
        return m_year;
    }
    // Returns the description of the movie
    const std::string& Movie::description() const {
        return m_description;
    }
    // Overloaded operator<< to output the movie details to an output stream
    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::setw(40) << movie.m_title << " | "
            << std::setw(4) << movie.m_year << " | "
            << movie.m_description << std::endl;
        return os;
    }
}
