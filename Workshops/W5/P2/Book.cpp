/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Book.h
 Date: June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Book.h"
#include <iomanip>

namespace seneca {
    // Default constructor that initializes member variables to default values
    Book::Book() : m_year(0), m_price(0.0) {}
    // Parameterized constructor that initializes a Book object from a comma-separated string
    Book::Book(const std::string& strBook) {
        size_t start = 0;
        size_t end = strBook.find(',');
        // Extract the author from the string
        m_author = strBook.substr(start, end - start);
        start = end + 1;
        end = strBook.find(',', start);
        // Extract the title from the string
        m_title = strBook.substr(start, end - start);
        start = end + 1;
        end = strBook.find(',', start);
        // Extract the country from the string
        m_country = strBook.substr(start, end - start);
        start = end + 1;
        end = strBook.find(',', start);
        // Extract the price from the string and convert it to a double
        m_price = std::stod(strBook.substr(start, end - start));
        start = end + 1;
        end = strBook.find(',', start);
        // Extract the year from the string and convert it to a size_t
        m_year = std::stoi(strBook.substr(start, end - start));
        start = end + 1;
        // Extract the description from the string
        m_description = strBook.substr(start);

        // Trim spaces
        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" "));
            str.erase(str.find_last_not_of(" ") + 1);
            };

        trim(m_author);
        trim(m_title);
        trim(m_country);
        trim(m_description);
    }
    // Returns the title of the book
    const std::string& Book::title() const {
        return m_title;
    }
    // Returns the country of the book
    const std::string& Book::country() const {
        return m_country;
    }
    // Returns the year of the book
    const size_t& Book::year() const {
        return m_year;
    }
    // Returns a reference to the price of the book, allowing modification
    double& Book::price() {
        return m_price;
    }
    // Overloaded operator<< to output the book details to an output stream
    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << book.m_author << " | "
            << std::setw(22) << book.m_title << " | "
            << std::setw(5) << book.m_country << " | "
            << std::setw(4) << book.m_year << " | "
            << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
            << book.m_description << std::endl;
        return os;
    }
}
