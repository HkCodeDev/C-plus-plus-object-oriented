/*****************************************************************************
                  Workshop - #5 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Collection.h
 Date: June 14 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <iostream>
#include <algorithm>

namespace seneca {
    template <typename T>
    class Collection {
        std::string m_name;// Name of the collection
        T* m_items{};// Dynamic array of items in the collection
        size_t m_size{};// Number of items in the collection
        void (*m_observer)(const Collection<T>&, const T&) {};// Observer function pointer

        // Helper function to convert string to lowercase
        std::string toLower(const std::string& str) const {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

    public:
        // Constructor that initializes the collection with a name
        Collection(const std::string& name) : m_name(name), m_items(nullptr), m_size(0), m_observer(nullptr) {}
        // Destructor that deallocates the dynamic array of items
        ~Collection() { delete[] m_items; }
        // Returns the name of the collection
        const std::string& name() const { return m_name; }
        // Returns the number of items in the collection
        size_t size() const { return m_size; }
        // Sets the observer function
        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            m_observer = observer;
        }
        // Adds an item to the collection if it doesn't already exist
        Collection<T>& operator+=(const T& item) {
            bool exists = false;
            for (size_t i = 0; i < m_size; ++i) {
                if (m_items[i].title() == item.title()) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                T* temp = new T[m_size + 1];
                for (size_t i = 0; i < m_size; ++i) {
                    temp[i] = m_items[i];
                }
                temp[m_size] = item;
                delete[] m_items;
                m_items = temp;
                ++m_size;
                // Notify observer if it exists
                if (m_observer != nullptr) {
                    m_observer(*this, item);
                }
            }
            return *this;
        }
        // Returns the item at the given index, throws out_of_range exception if index is invalid
        T& operator[](size_t idx) const {
            if (idx >= m_size) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
            }
            return m_items[idx];
        }
        // Returns a pointer to the item with the given title, or nullptr if not found
        T* operator[](const std::string& title) const {
            std::string lowerTitle = toLower(title);
            for (size_t i = 0; i < m_size; ++i) {
                if (toLower(m_items[i].title()) == lowerTitle) {
                    return &m_items[i];
                }
            }
            return nullptr;
        }
        // Overloaded operator<< to output the collection details to an output stream
        friend std::ostream& operator<<(std::ostream& os, const Collection& collection) {
            for (size_t i = 0; i < collection.m_size; ++i) {
                os << collection.m_items[i];
            }
           
            return os;
        }
    };
}

#endif
