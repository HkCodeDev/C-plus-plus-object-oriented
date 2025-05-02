#define _CRT_SECURE_NO_WARNINGS
#include "Reservation.h"
#include <cstring>

namespace seneca {

    Reservation::Reservation() : reservation_id{ "" }, name{ "" }, email{ "" }, party_size{ 0 }, day{ 0 }, hour{ 0 } {}

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
        while (end > start && str[end - 1] == ' ') {
            --end;
        }
        return str.substr(start, end - start);
    }

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

    std::ostream& operator<<(std::ostream& os, const Reservation& res) {
        os << "Reservation " << std::setw(10) << std::right << res.reservation_id << ": "
            << std::setw(20) << std::right << res.name << "  "
            << std::setw(20) << std::left << ("<" + res.email + ">");

        if (res.hour >= 6 && res.hour <= 9) {
            os << " Breakfast on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else if (res.hour >= 11 && res.hour <= 15) {
            os << " Lunch on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else if (res.hour >= 17 && res.hour <= 21) {
            os << " Dinner on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }
        else {
            os << " Drinks on day " << res.day << " @ " << res.hour << ":00 for " << res.party_size << (res.party_size == 1 ? " person." : " people.");
        }

        os << std::endl;
        return os;
    }

}