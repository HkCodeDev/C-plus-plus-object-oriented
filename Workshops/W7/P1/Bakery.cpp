#include "Bakery.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

namespace seneca {

    std::string Bakery::trim(const std::string& str) {
        auto start = str.find_first_not_of(' ');
        auto end = str.find_last_not_of(' ');
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }


    Bakery::Bakery(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("File not found");
        }

        std::string line;
        while (std::getline(file, line)) {
            BakedGood bg;

            bg.type = (trim(line.substr(0, 8)) == "Bread") ? BakedType::BREAD : BakedType::PASTRY;
            bg.description = trim(line.substr(8, 20));
            bg.shelfLife = std::stoi(trim(line.substr(28, 14)));
            bg.stock = std::stoi(trim(line.substr(42, 8)));
            bg.price = std::stod(trim(line.substr(50, 6)));

            bakedGoods.push_back(bg);
        }
    }

    void Bakery::showGoods(std::ostream& os) const {
    std::for_each(bakedGoods.begin(), bakedGoods.end(), [&os](const BakedGood& bg) {
        os << bg << std::endl;
    });
}


    std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
        out<< "* " << std::left << std::setw(10)  
            << ((b.type == BakedType::BREAD) ? "Bread" : "Pastry")
           << " * " << std::left << std::setw(20) << Bakery::trim(b.description)
           << " * " << std::setw(5) << b.shelfLife
             << " * " << std::setw(5) << b.stock
            << " * " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price
            << " *"; 
        return out;
    }



}
