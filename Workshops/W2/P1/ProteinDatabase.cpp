#include "ProteinDatabase.h"
#include <fstream>
#include <iostream>

namespace seneca {

    ProteinDatabase::ProteinDatabase() : sequences(nullptr), numSequences(0) {}

    ProteinDatabase::ProteinDatabase(const std::string& filename) : sequences(nullptr), numSequences(0) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // First pass: Count the number of sequences
        std::string line;
        size_t count = 0;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') {
                ++count;
            }
        }

        // Allocate memory based on the number of sequences
        sequences = new std::string[count];
        numSequences = count;

        // Close and reopen the file for the second pass
        file.close();
        file.open(filename);
        if (!file) {
            std::cerr << "Error reopening file: " << filename << std::endl;
            delete[] sequences;
            sequences = nullptr;
            numSequences = 0;
            return;
        }

        // Second pass: Load the sequences
        size_t currentIndex = 0;
        std::string sequence;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] == '>') {
                if (!sequence.empty() && currentIndex < numSequences) {
                    sequences[currentIndex++] = sequence;
                    sequence = "";
                }
            }
            else {
                sequence += line;
            }
        }

        // Save the last read sequence
        if (!sequence.empty() && currentIndex < numSequences) {
            sequences[currentIndex] = sequence;
        }
    }

    ProteinDatabase::~ProteinDatabase() {
        delete[] sequences;
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {
        *this = other; // Delegate to the copy assignment operator
    }

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& other) {
        if (this != &other) {
            std::string* newSequences = new std::string[other.numSequences];
            for (size_t i = 0; i < other.numSequences; ++i) {
                newSequences[i] = other.sequences[i];  // Copy each string
            }
            delete[] sequences;
            sequences = newSequences;
            numSequences = other.numSequences;
        }
        return *this;
    }

    size_t ProteinDatabase::size() const {
        return numSequences;
    }

    std::string ProteinDatabase::operator[](size_t index) const {
        if (index >= numSequences) {
            return "";
        }
        return sequences[index];
    }

}
