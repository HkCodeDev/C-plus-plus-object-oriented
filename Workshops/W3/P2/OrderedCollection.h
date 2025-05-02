/*****************************************************************************
                  Workshop - #3 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: OrderCollection.h
 Date: May 29 2024
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace seneca {
    // The OrderedCollection class template is derived from the
    //  Collection class template and represents a collection 
    // that maintains its items in ascending order.
    // It always has a fixed capacity of 72 items.
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        // Overloaded operator+= to add an item to the 
        // collection in ascending order.
        bool operator+=(const T& item);
    };
    // Definition of the operator+= function
    template <typename T>
    bool OrderedCollection<T>::operator+=(const T& item) {
        // Check if there is room in the collection to add the item
        if (this->size() < this->capacity()) {
            unsigned i = this->size();
            // Find the correct position to insert
            //  the new item to maintain ascending order
            while (i > 0 && item < this->m_items[i - 1]) {
                this->m_items[i] = this->m_items[i - 1];
                --i;
            }
            this->m_items[i] = item;// Insert the new item
            this->incrSize();// Increment the size of the collection
            this->setSmallestItem(item);// Update the smallest item if necessary
            this->setLargestItem(item);// Update the largest item if necessary
            return true;
        }

        return false;// Return false if the collection is full
    }
}

#endif
