/*****************************************************************************
                  Workshop - #2 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:ProteinDatabase.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_PROTEINDATABASE_H 
#define SENECA_PROTEINDATABASE_H 

#include <string>

namespace seneca {
    class ProteinDatabase {
        std::string* sequences;// Pointer to an array of protein sequences
        size_t numSequences; // Number of sequences stored in the database

    public:
        // Constructors 
        ProteinDatabase();// Default constructor
        ProteinDatabase(const std::string& filename);// Construct from file
        ProteinDatabase(const ProteinDatabase& other);// Copy constructor
        ProteinDatabase(ProteinDatabase&& other) noexcept;// Move constructor
        // Assignment Operators
        // Copy assignment
        ProteinDatabase& operator=(const ProteinDatabase& other);
        // Move assignment
        ProteinDatabase& operator=(ProteinDatabase&& other) noexcept;
        // Destructor
        ~ProteinDatabase();
        // Accessors
        size_t size() const;// Return the number of sequences
        // Access a sequence by index
        std::string operator[](size_t index) const;
    };
}
#endif // PROTEINDATABASE_H
