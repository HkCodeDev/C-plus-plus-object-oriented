/*****************************************************************************
                  Workshop - #3 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Book.h
 Date: May 29 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {
    class Book {
        std::string m_title{};// Title of the book
        unsigned m_numChapters{};// Number of chapters in the book
        unsigned m_numPages{};// Number of pages in the book
    public:
        // Default constructor
        Book();
        // Constructor that initializes the book with the provided
       // title, number of chapters, and number of pages.
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        // Getter methods for:
        const std::string& getTitle() const;//title of the book.
        unsigned getNumChapters() const;//number of chapters in the book.
        unsigned getNumPages() const;//number of pages in the book.

        // Display method
        std::ostream& print(std::ostream& os) const;

        // Operator overloads
        bool operator<(const Book& other) const;
        bool operator>(const Book& other) const;

        // Validation
        bool isValid() const;//To check if the code is valid.
    };
    // Overloaded stream insertion operator to print the book details using the print
    // method defined in the Book class.
    std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif
