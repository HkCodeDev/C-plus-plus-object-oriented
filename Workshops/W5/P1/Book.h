#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {
    class Book {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

    public:
        Book() : m_year(0), m_price(0.0) {}

        Book(const std::string& strBook) {
            size_t start = 0;
            size_t end = strBook.find(',');

            m_author = strBook.substr(start, end - start);
            start = end + 1;
            end = strBook.find(',', start);

            m_title = strBook.substr(start, end - start);
            start = end + 1;
            end = strBook.find(',', start);

            m_country = strBook.substr(start, end - start);
            start = end + 1;
            end = strBook.find(',', start);

            m_price = std::stod(strBook.substr(start, end - start));
            start = end + 1;
            end = strBook.find(',', start);

            m_year = std::stoi(strBook.substr(start, end - start));
            start = end + 1;

            m_description = strBook.substr(start);

            // Trim spaces
            auto trim = [](std::string& str) {
                str.erase(0, str.find_first_not_of(" \t"));
                str.erase(str.find_last_not_of(" \t") + 1);
                };

            trim(m_author);
            trim(m_title);
            trim(m_country);
            trim(m_description);
        }

        const std::string& title() const { return m_title; }
        const std::string& country() const { return m_country; }
        const size_t& year() const { return m_year; }
        double& price() { return m_price; }

        friend std::ostream& operator<<(std::ostream& os, const Book& book) {
            os << std::setw(20) << book.m_author << " | "
                << std::setw(22) << book.m_title << " | "
                << std::setw(5) << book.m_country << " | "
                << std::setw(4) << book.m_year << " | "
                << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
                << book.m_description;
            return os;
        }
    };
}

#endif
