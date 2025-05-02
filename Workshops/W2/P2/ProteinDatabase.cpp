/*****************************************************************************
                  Workshop - #2 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File:ProteinDatabase.cpp
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#include "ProteinDatabase.h"
#include <fstream>
#include <iostream>

namespace seneca {
    // Default constructor initializes the database as empty
    ProteinDatabase::ProteinDatabase() : sequences(nullptr), numSequences(0) {}
    // Constructor to load protein sequences from a file
    ProteinDatabase::ProteinDatabase(const std::string& filename) : sequences(nullptr), numSequences(0) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // Initialize storage for sequences dynamically
        std::string line;
        std::string* tempSequences = new std::string[10];  // Initial size
        size_t allocatedSize = 10;
        size_t currentIndex = 0;
        std::string sequence;

        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') {
                if (!sequence.empty()) {  // Save the previous sequence
                    if (currentIndex >= allocatedSize) {
                        // Resize the array when limit is reached
                        size_t newSize = allocatedSize * 2;  // Double the array size
                        std::string* newSequences = new std::string[newSize];
                        for (size_t i = 0; i < allocatedSize; ++i) {
                            newSequences[i] = std::move(tempSequences[i]);
                        }
                        delete[] tempSequences;
                        tempSequences = newSequences;
                        allocatedSize = newSize;
                    }
                    tempSequences[currentIndex++] = std::move(sequence);
                    sequence.clear();
                }
            }
            else {
                sequence += line;// Accumulate sequence lines
            }
        }

        // Add the last sequence if it exists
        if (!sequence.empty()) {
            if (currentIndex >= allocatedSize) {
                // Increment to fit the last sequence
                size_t newSize = allocatedSize + 1;
                std::string* newSequences = new std::string[newSize];
                for (size_t i = 0; i < allocatedSize; ++i) {
                    newSequences[i] = std::move(tempSequences[i]);
                }
                delete[] tempSequences;
                tempSequences = newSequences;
                allocatedSize = newSize;
            }
            tempSequences[currentIndex++] = std::move(sequence);
        }

        // Finalize the structure
        sequences = tempSequences;
        numSequences = currentIndex;
    }

    // Destructor to free allocated memory
    ProteinDatabase::~ProteinDatabase() {
        delete[] sequences;
    }
    //copy constructor
    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other)
        : sequences(nullptr), numSequences(0) {
        *this = other;  // Use the copy assignment operator
    }

    // Copy assignment operator
    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
        // 1. Check for self-assignment
        if (this != &other) {
            // 2. Clean-up existing resources
            delete[] sequences;
            // Clear the pointer after deleting to avoid dangling references
            sequences = nullptr;

            // 3. Shallow copy of non-resource data
            numSequences = other.numSequences;

            // 4. Deep copy of the resource
            if (numSequences > 0) {
                // Allocate new memory for sequences
                sequences = new std::string[numSequences];
                for (size_t i = 0; i < numSequences; ++i) {
                    sequences[i] = other.sequences[i];  // Copy each sequence
                }
            }
            else {
                sequences = nullptr;  // No sequences to copy
            }
        }
        return *this;
    }


    // Move constructor 
    ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) noexcept
        : sequences(nullptr), numSequences(0) {
        *this = std::move(other);  // Use the move assignment operator
    }


    // Move assignment operator
    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) noexcept {
        if (this != &other) {
            delete[] sequences;
            sequences = other.sequences;
            numSequences = other.numSequences;
            other.sequences = nullptr;
            other.numSequences = 0;
        }
        return *this;
    }

    // Return the number of sequences in the database
    size_t ProteinDatabase::size() const {
        return numSequences;
    }
    // Access a sequence by index, return empty 
    // string if index is out of bounds
    std::string ProteinDatabase::operator[](size_t index) const {
        if (index >= numSequences) {
            return "";
        }
        return sequences[index];
    }

}
