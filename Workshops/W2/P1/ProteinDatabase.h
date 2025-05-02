#ifndef PROTEINDATABASE_H
#define PROTEINDATABASE_H

#include <string>

namespace seneca {
    class ProteinDatabase {
        std::string* sequences;
        size_t numSequences;

    public:
        ProteinDatabase();
        ProteinDatabase(const std::string& filename);
        ProteinDatabase(const ProteinDatabase& other);
        ProteinDatabase& operator=(const ProteinDatabase& other);
        ~ProteinDatabase();
        size_t size() const;
        std::string operator[](size_t index) const;
    };
}
#endif // PROTEINDATABASE_H
