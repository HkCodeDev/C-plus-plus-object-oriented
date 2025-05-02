#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <iostream>
#include <string>
#include <iomanip>

namespace seneca {

    class Reservation {
        char reservation_id[11];
        std::string name;
        std::string email;
        int party_size;
        int day;
        int hour;

    public:
        Reservation();
        void update(int new_day, int new_hour);
        Reservation(const std::string& res);

        friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
    };

}

#endif // RESERVATION_H
