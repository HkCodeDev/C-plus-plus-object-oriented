/*****************************************************************************
                  Workshop - #4 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Reservation.cpp
 Date: June 6 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Reservation.h"
#include <cstring>  

namespace seneca {
    // Default constructor to initialize member variables
    Reservation::Reservation() : reservation_id{ "" }, name{ "" }, email{ "" }, party_size{ 0 }, day{ 0 }, hour{ 0 } {}
    // Modifier to update the reservation date and time
    void Reservation::update(int new_day, int new_hour) {
        day = new_day;
        hour = new_hour;
    }

    // Utility function to trim leading and trailing spaces
    std::string trim(const std::string& str) {
        size_t start = 0;
        while (start < str.length() && str[start] == ' ') {
            ++start;
        }
        size_t end = str.length();
        // Find the last non-space character
        while (end > start && str[end - 1] == ' ') {
            --end;
        }
        // Return the substring without leading and trailing spaces
        return str.substr(start, end - start);
    }
    // Constructor that initializes a Reservation object from a string
    Reservation::Reservation(const std::string& res) {
        std::string temp = res;
        size_t pos = 0;

        // Extract reservation id
        pos = temp.find(':');
        std::string id = temp.substr(0, pos);
        id = trim(id); // Trim spaces around the token
        std::strncpy(reservation_id, id.c_str(), 10);
        reservation_id[10] = '\0'; // Ensure null-termination
        temp.erase(0, pos + 1);

        // Extract name
        pos = temp.find(',');
        name = temp.substr(0, pos);
        name = trim(name); // Trim spaces around the token
        temp.erase(0, pos + 1);

        // Extract email
        pos = temp.find(',');
        email = temp.substr(0, pos);
        email = trim(email); // Trim spaces around the token
        temp.erase(0, pos + 1);

        // Extract party size
        pos = temp.find(',');
        std::string party_size_str = temp.substr(0, pos);
        party_size_str = trim(party_size_str); // Trim spaces around the token
        party_size = std::stoi(party_size_str);
        temp.erase(0, pos + 1);

        // Extract day
        pos = temp.find(',');
        std::string day_str = temp.substr(0, pos);
        day_str = trim(day_str); // Trim spaces around the token
        day = std::stoi(day_str);
        temp.erase(0, pos + 1);

        // Extract hour
        std::string hour_str = temp;
        hour_str = trim(hour_str); // Trim spaces around the token
        hour = std::stoi(hour_str);

    }
    // Overload of the insertion operator to print the contents of a Reservation object
    std::ostream& operator<<(std::ostream& os, const Reservation& res) {
        os << "Reservation " << std::setw(10) << std::right << res.reservation_id << ": "
            << std::setw(20) << std::right << res.name << "  "
            << std::setw(20) << std::left << ("<" + res.email + ">");

        if (res.hour >= 6 && res.hour <= 9) {
            os << "    Breakfast on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else if (res.hour >= 11 && res.hour <= 15) {
            os << "    Lunch on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else if (res.hour >= 17 && res.hour <= 21) {
            os << "    Dinner on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else {
            os << "    Drinks on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }

        os << std::endl;
        return os;
    }

}