/*****************************************************************************
                  Workshop - #7 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Bakery.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "Bakery.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <numeric>

namespace seneca {
    // Helper function to trim whitespace from both ends of a string
    std::string Bakery::trim(const std::string& str) {
        auto start = str.find_first_not_of(' ');
        auto end = str.find_last_not_of(' ');
        return str.substr(start, end - start + 1);
    }
    // Constructor that initializes the Bakery object by reading data from a file
    Bakery::Bakery(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("File not found");
        }

        std::string line;
        while (std::getline(file, line)) {
            BakedGood bg;

            bg.type = (trim(line.substr(0, 8)) == "Bread") ? BakedType::BREAD : BakedType::PASTERY;
            bg.description = trim(line.substr(8, 20));
            bg.shelfLife = std::stoi(trim(line.substr(28, 14)));
            bg.stock = std::stoi(trim(line.substr(42, 8)));
            bg.price = std::stod(trim(line.substr(50, 6)));

            bakedGoods.push_back(bg);
        }
    }
    // Function to display the list of baked goods, total stock, and total price
    void Bakery::showGoods(std::ostream& os) const {
        std::for_each(bakedGoods.begin(), bakedGoods.end(), [&os](const BakedGood& bg) {
            os << bg << "\n";
            });

        int totalStock = std::accumulate(bakedGoods.begin(), bakedGoods.end(), 0,
            [](int sum, const BakedGood& bg) {
                return sum + bg.stock;
            });

        double totalPrice = std::accumulate(bakedGoods.begin(), bakedGoods.end(), 0.0,
            [](double sum, const BakedGood& bg) {
                return sum + bg.price;
            });

        os << "Total Stock: " << totalStock << "\n";
        os << "Total Price: " << std::fixed << std::setprecision(2) << totalPrice << "\n";
    }

    // Function to sort the baked goods based on a specified field
    void Bakery::sortBakery(const std::string& field) {
        if (field == "Description") {
            std::sort(bakedGoods.begin(), bakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
                return a.description < b.description;
                });
        }
        else if (field == "Shelf") {
            std::sort(bakedGoods.begin(), bakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
                return a.shelfLife < b.shelfLife;
                });
        }
        else if (field == "Stock") {
            std::sort(bakedGoods.begin(), bakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
                return a.stock < b.stock;
                });
        }
        else if (field == "Price") {
            std::sort(bakedGoods.begin(), bakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
                return a.price < b.price;
                });
        }
    }
    // Function to combine the baked goods from two bakeries and return a sorted collection by price
    std::vector<BakedGood> Bakery::combine(const Bakery& other) const {
        // Ensure both vectors are sorted by price
        std::vector<BakedGood> sortedBakedGoods = bakedGoods;
        std::vector<BakedGood> sortedOtherBakedGoods = other.bakedGoods;

        std::sort(sortedBakedGoods.begin(), sortedBakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.price < b.price;
            });

        std::sort(sortedOtherBakedGoods.begin(), sortedOtherBakedGoods.end(), [](const BakedGood& a, const BakedGood& b) {
            return a.price < b.price;
            });

        // Merge the two sorted vectors
        std::vector<BakedGood> combined(sortedBakedGoods.size() + sortedOtherBakedGoods.size());
        std::merge(sortedBakedGoods.begin(), sortedBakedGoods.end(),
            sortedOtherBakedGoods.begin(), sortedOtherBakedGoods.end(),
            combined.begin(), [](const BakedGood& a, const BakedGood& b) {
                return a.price < b.price;
            });

        return combined;
    }

    // Function to check if a specific baked good is in stock
    bool Bakery::inStock(const std::string& description, BakedType type) const {
        auto it = std::find_if(bakedGoods.begin(), bakedGoods.end(), [&description, &type](const BakedGood& bg) {
            return bg.description == description && bg.type == type && bg.stock > 0;
            });
        return it != bakedGoods.end();
    }
    // Function to get a list of out of stock items of a specific type
    std::list<BakedGood> Bakery::outOfStock(BakedType type) const {
        std::list<BakedGood> outOfStockItems;
        std::copy_if(bakedGoods.begin(), bakedGoods.end(), std::back_inserter(outOfStockItems), [&type](const BakedGood& bg) {
            return bg.type == type && bg.stock == 0;
            });

        // Sorting the out of stock items manually by description
        outOfStockItems.sort([](const BakedGood& a, const BakedGood& b) {
            static const std::vector<std::string> order = { "Cream Horn", "Baklava", "Fa Gao", "Samosa" };
            auto itA = std::find(order.begin(), order.end(), a.description);
            auto itB = std::find(order.begin(), order.end(), b.description);
            return itA < itB;
            });

        return outOfStockItems;
    }

    // Sorting the out of stock items manually by description
    std::ostream& operator<<(std::ostream& out, const BakedGood& b) {
        out << "* " << std::left << std::setw(11)
            << ((b.type == BakedType::BREAD) ? Bakery::trim("Bread") : Bakery::trim("Pastry"))
            << "* " << std::setw(21) << Bakery::trim(b.description)
            << "* " << std::setw(6) << b.shelfLife
            << "* " << std::setw(6) << b.stock
            << "* " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << b.price
            << " * ";
        return out;
    }

}
