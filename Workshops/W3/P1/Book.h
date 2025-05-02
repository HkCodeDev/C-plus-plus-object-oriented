#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {
    class Book {
        std::string m_title{};
        unsigned m_numChapters{};
        unsigned m_numPages{};
    public:
        Book();
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        // Getter methods
        const std::string& getTitle() const;
        unsigned getNumChapters() const;
        unsigned getNumPages() const;

        // Display method
        std::ostream& print(std::ostream& os) const;

        // Operator overloads
        bool operator<(const Book& other) const;
        bool operator>(const Book& other) const;

        // Validation
        bool isValid() const;
    };

    std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif
