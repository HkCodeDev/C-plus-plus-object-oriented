#ifndef BAKERY_H
#define BAKERY_H

#include <iostream>
#include <vector>
#include <string>

namespace seneca {

    enum class BakedType {
        BREAD, PASTRY
    };

    struct BakedGood {
        BakedType type;
        std::string description;
        int shelfLife;
        int stock;
        double price;
    };

    class Bakery {
    private:
        std::vector<BakedGood> bakedGoods;

    public:
        Bakery(const std::string& filename);
        void showGoods(std::ostream& os) const;

        // Helper function to trim whitespace from both ends of a string
        static std::string trim(const std::string& str);
    };

    std::ostream& operator<<(std::ostream& out, const BakedGood& b);

}

#endif // BAKERY_H
