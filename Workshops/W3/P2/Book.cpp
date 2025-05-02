/*****************************************************************************
                  Workshop - #3 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Book.cpp
 Date: May 29 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Book.h"

namespace seneca {
    // Default constructor for Book, initializing title to an empty string,
    // number of chapters to 0, and number of pages to 0.
    Book::Book() : m_title(""), m_numChapters(0), m_numPages(0) {}
    // Parameterized constructor for Book, initializing title, number of chapters,
   // and number of pages to the provided values.
    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}
    // Getter for the title of the book.
    const std::string& Book::getTitle() const {
        return m_title;
    }
    // Getter for the number of chapters in the book.
    unsigned Book::getNumChapters() const {
        return m_numChapters;
    }
    // Getter for the number of pages in the book.
    unsigned Book::getNumPages() const {
        return m_numPages;
    }
    // Function to check if the book is valid.
    bool Book::isValid() const {
        return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
    }
    // Function to print the book details in the required format.
    std::ostream& Book::print(std::ostream& os) const {
        if (isValid()) {
            //If the book is valid, it prints the title, number of chapters,
            //  number of pages, and the average pages
            os << std::right << std::setw(56) << m_title + "," + std::to_string(m_numChapters) + "," + std::to_string(m_numPages)
                << " | " << std::left << std::setw(15) << "(" + std::to_string(static_cast<double>(m_numPages) / m_numChapters) + ")";
        }
        else {
            //If the book is invalid, it prints "Invalid book data".
            os << "| Invalid book data";
        }
        return os;
    }
    // Operator overload to compare two books based on the average number of pages
    bool Book::operator<(const Book& other) const {
        return static_cast<double>(m_numPages) / m_numChapters < static_cast<double>(other.m_numPages) / other.m_numChapters;
    }
    // Operator overload to compare two books based on the average number of pages
   // per chapter.
    bool Book::operator>(const Book& other) const {
        return static_cast<double>(m_numPages) / m_numChapters > static_cast<double>(other.m_numPages) / other.m_numChapters;
    }
    // Overloaded stream insertion operator to print the book details using the print
    // method
    std::ostream& operator<<(std::ostream& os, const Book& bk) {
        return bk.print(os);
    }
}
