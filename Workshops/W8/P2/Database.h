#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <iomanip>
#include <algorithm>

namespace seneca {

    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory
    };

    class Database {
        static std::shared_ptr<Database> instance;
        static const int max_entries = 20;

        std::string keys[max_entries];
        std::string values[max_entries];
        int num_entries;
        std::string filename;

        Database(const std::string& filename) : num_entries(0), filename(filename) {
            std::cout << "[" << this << "] Database(const std::string&)\n";

            std::ifstream file(filename);
            if (file) {
                std::string key, value;
                while (file >> key >> value && num_entries < max_entries) {
                    std::replace(key.begin(), key.end(), '_', ' ');
                    keys[num_entries] = key;
                    values[num_entries] = value;
                    ++num_entries;
                }
            }
        }

    public:
        ~Database() {
            std::cout << "[" << this << "] ~Database()\n";

            std::ofstream backup_file(filename + ".bkp.txt");
            if (backup_file) {
                for (int i = 0; i < num_entries; ++i) {
                    backup_file << std::left << std::setw(25) << keys[i] << " -> " << values[i] << "\n";
                }
            }
        }

        static std::shared_ptr<Database> getInstance(const std::string& filename) {
            if (!instance) {
                instance = std::shared_ptr<Database>(new Database(filename));
            }
            return instance;
        }

        Err_Status GetValue(const std::string& key, std::string& value) {
            for (int i = 0; i < num_entries; ++i) {
                if (keys[i] == key) {
                    value = values[i];
                    return Err_Status::Err_Success;
                }
            }
            return Err_Status::Err_NotFound;
        }

        Err_Status SetValue(const std::string& key, const std::string& value) {
            if (num_entries >= max_entries) {
                return Err_Status::Err_OutOfMemory;
            }

            for (int i = 0; i < num_entries; ++i) {
                if (keys[i] == key) {
                    values[i] = value;
                    return Err_Status::Err_Success;
                }
            }

            keys[num_entries] = key;
            values[num_entries] = value;
            ++num_entries;
            return Err_Status::Err_Success;
        }
    };

    std::shared_ptr<Database> Database::instance = nullptr;

} // namespace seneca

#endif // DATABASE_H
