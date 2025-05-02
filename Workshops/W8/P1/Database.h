/*****************************************************************************
                  Workshop - #8 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Database.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

namespace seneca {

    enum class Err_Status {
        Err_Success,// Operation successful
        Err_NotFound,// Key not found in database
        Err_OutOfMemory,// Database has reached its capacity
    };
    // Templated singleton class to manage a key-value store
    template<typename T>
    class Database {
    private:
        // Singleton instance
        static std::shared_ptr<Database<T>> instance;
        // Maximum number of entries in the database
        static const int MAX_ENTRIES = 20;
        // Current number of entries
        int numEntries;
        // Array to store keys
        std::string keys[MAX_ENTRIES];
        // Array to store values
        T values[MAX_ENTRIES];
        // Filename for persistent storage
        std::string filename;
        // Custom deleter for the shared_ptr managing the singleton instance
        struct Deleter {
            void operator()(Database* ptr) {
                delete ptr;
            }
        };
        // Private constructor for singleton implementation
        Database(const std::string& filename) : numEntries(0), filename(filename) {
            std::cout << "[" << this << "] Database(const std::string&)\n";

            std::ifstream file(filename);
            if (file.is_open()) {
                std::string key;
                T value;
                while (file >> key >> value && numEntries < MAX_ENTRIES) {
                    std::replace(key.begin(), key.end(), '_', ' ');
                    encryptDecrypt(value);
                    keys[numEntries] = key;
                    values[numEntries] = value;
                    numEntries++;
                }
            }
        }
        // Destructor to write encrypted data back to a backup file
        ~Database() {
            std::cout << "[" << this << "] ~Database()\n";

            std::ofstream file(filename + ".bkp.txt");
            for (int i = 0; i < numEntries; ++i) {
                T encryptedValue = values[i];
                encryptDecrypt(encryptedValue);
                file << std::left << std::setw(25) << keys[i] << " -> " << encryptedValue << std::endl;
            }
           
        }

        // Template method for generic types
        void encryptDecrypt(T& value) {
            // Empty implementation for generic type
        }

    public:
        // Method to get the singleton instance, creating it if necessary
        static std::shared_ptr<Database<T>> getInstance(const std::string& filename) {
            if (!instance) {
                instance = std::shared_ptr<Database<T>>(new Database<T>(filename), Deleter());
            }
            return instance;
        }
        // Retrieve a value by key
        Err_Status GetValue(const std::string& key, T& value) const {
            for (int i = 0; i < numEntries; ++i) {
                if (keys[i] == key) {
                    value = values[i];
                    return Err_Status::Err_Success;
                }
            }
            return Err_Status::Err_NotFound;
        }
        // Set a new key-value pair in the database
        Err_Status SetValue(const std::string& key, const T& value) {
            if (numEntries < MAX_ENTRIES) {
                keys[numEntries] = key;
                values[numEntries] = value;
                numEntries++;
                return Err_Status::Err_Success;
            }
            return Err_Status::Err_OutOfMemory;
        }
    };

    // Define the static member variable
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::instance = nullptr;

    // Specialization for std::string
    template<>
    void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[]{ "secret encryption key" };
        for (char& c : value) {
            for (const char k : secret) {
                c ^= k;
            }
        }
    }

    // Specialization for long long
    template<>
    void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[]{ "super secret encryption key" };
        char* bytes = reinterpret_cast<char*>(&value);
        for (size_t i = 0; i < sizeof(value); ++i) {
            for (const char k : secret) {
                bytes[i] ^= k;
            }
        }
    }

} // namespace seneca

#endif // DATABASE_H
