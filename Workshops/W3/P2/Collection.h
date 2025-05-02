/*****************************************************************************
                  Workshop - #3 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: Collection.h
 Date: May 29 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <iomanip>

namespace seneca {
    // The Collection class template represents a collection of items
    //  of type T with a fixed capacity C.
    template <typename T, unsigned C>
    class Collection {
    protected:
        T m_items[C] = {}; // Statically allocated array to hold the items.
        unsigned m_size{ 0 }; // Current number of items in the collection.

        static T m_smallestItem;// Static member to track the smallest item.
        static T m_largestItem;//// Static member to track the largest item 
        // Methods to update the smallest and largest items
        void setSmallestItem(const T& item);
        void setLargestItem(const T& item);
        // Operator to access an item by index
        T& operator[](unsigned index);
        // Method to increment the size of the collection
        void incrSize();
    public:
        // Default constructor
        Collection() = default;
        // Methods to get the current size and capacity of the collection
        unsigned size() const;
        unsigned capacity() const;
        // Static methods to get the smallest and largest items
        static T getSmallestItem();
        static T getLargestItem();
        // Method to add an item to the collection
        bool operator+=(const T& item);
        // Function to print the items in the collection
        void print(std::ostream& os) const;
    };

    // Static member initializations
    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = 9999;

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = -9999;

    // Specializations for the Book type with capacity 10
    template <>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    // Specializations for the Book type with capacity 72
    template <>
    Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

    // Definitions of member functions
    template <typename T, unsigned C>
    unsigned Collection<T, C>::size() const {
        return m_size;
    }

    template <typename T, unsigned C>
    unsigned Collection<T, C>::capacity() const {
        return C;
    }

    template <typename T, unsigned C>
    T Collection<T, C>::getSmallestItem() {
        return m_smallestItem;
    }

    template <typename T, unsigned C>
    T Collection<T, C>::getLargestItem() {
        return m_largestItem;
    }

    template <typename T, unsigned C>
    void Collection<T, C>::setSmallestItem(const T& item) {
        if (item < m_smallestItem) {
            m_smallestItem = item;
        }
    }

    template <typename T, unsigned C>
    void Collection<T, C>::setLargestItem(const T& item) {
        if (item > m_largestItem) {
            m_largestItem = item;
        }
    }

    template <typename T, unsigned C>
    T& Collection<T, C>::operator[](unsigned index) {
        return m_items[index];
    }

    template <typename T, unsigned C>
    void Collection<T, C>::incrSize() {
        if (m_size < C) {
            ++m_size;
        }
    }

    template <typename T, unsigned C>
    bool Collection<T, C>::operator+=(const T& item) {
        if (m_size < C) {
            m_items[m_size++] = item;
            setSmallestItem(item);
            setLargestItem(item);
            return true;
        }
        return false;
    }

    template <typename T, unsigned C>
    void Collection<T, C>::print(std::ostream& os) const {
        os << "[";
        for (unsigned i = 0; i < m_size; ++i) {
            if (i != 0) os << ",";
            os << m_items[i];
        }
        os << "]\n";
    }
    // Specialization of the print function for Book type with capacity 10
    template <>
    void Collection<Book, 10>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|\n";
        for (unsigned i = 0; i < m_size; ++i) {
            os << "| ";
            m_items[i].print(os) << " |\n";
        }
        os << "| ---------------------------------------------------------------------------|\n";
    }
    // Specialization of the print function for Book type with capacity 72
    template <>
    void Collection<Book, 72>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|\n";
        for (unsigned i = 0; i < m_size; ++i) {
            os << "| ";
            m_items[i].print(os) << " |\n";
        }
        os << "| ---------------------------------------------------------------------------|\n";
    }
}

#endif
