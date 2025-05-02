#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <iomanip>

namespace seneca {
    template <typename T, unsigned C>
    class Collection {
        T m_items[C] = {};
        unsigned m_size{ 0 };

        static T m_smallestItem;
        static T m_largestItem;

        void setSmallestItem(const T& item);
        void setLargestItem(const T& item);
    public:
        Collection() = default;

        int size() const;
        int capacity() const;

        static T getSmallestItem();
        static T getLargestItem();

        bool operator+=(const T& item);
        void print(std::ostream& os) const;
    };

    // Static member initializations
    template <typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = 9999;

    template <typename T, unsigned C>
    T Collection<T, C>::m_largestItem = -9999;

    template <>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    // Definitions
    template <typename T, unsigned C>
    int Collection<T, C>::size() const {
        return m_size;
    }

    template <typename T, unsigned C>
    int Collection<T, C>::capacity() const {
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
}
#endif
