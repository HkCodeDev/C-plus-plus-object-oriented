/*****************************************************************************
                  Workshop - #7 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Bakery.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_BAKERY_H
#define SENECA_BAKERY_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

namespace seneca {

    enum class BakedType {
        BREAD, PASTERY
    };
    // Struct to represent a baked good item with default initialization
    struct BakedGood {
        BakedType type;
        std::string description = "";
        int shelfLife = 0;
        int stock = 0;
        double price = 0.0;
    };

    class Bakery {
    private:
        std::vector<BakedGood> bakedGoods;// Collection of baked goods

    public:
        // Constructor that initializes the Bakery object by reading data from a file
        Bakery(const std::string& filename);
        // Function to display the list of baked goods, total stock, and total price
        void showGoods(std::ostream& os) const;
        // Function to sort the baked goods based on a specified field
        void sortBakery(const std::string& field);
        // Function to combine the baked goods from two bakeries and return a sorted collection by price
        std::vector<BakedGood> combine(const Bakery& other) const;
        // Function to check if a specific baked good is in stock
        bool inStock(const std::string& description, BakedType type) const;
        // Function to get a list of out of stock items of a specific type
        std::list<BakedGood> outOfStock(BakedType type) const;

        // Helper function to trim whitespace from both ends of a string
        static std::string trim(const std::string& str);
    };
    // Sorting the out of stock items manually by description
    std::ostream& operator<<(std::ostream& out, const BakedGood& b);

}

#endif // BAKERY_H
