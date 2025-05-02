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
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>

namespace seneca {
    class Book {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

    public:
        // Default constructor that initializes member variables to default values
        Book();
        // Parameterized constructor that initializes a Book object from a comma-separated string
        Book(const std::string& strBook);
        // Returns the title of the book
        const std::string& title() const;
        // Returns the country of the book
        const std::string& country() const;
        // Returns the year of the book
        const size_t& year() const;
        // Returns a reference to the price of the book, allowing modification
        double& price();

        // Templated function to fix spelling
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_description);
        }
        // Overloaded operator<< to output the book details to an output stream
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };
}

#endif
