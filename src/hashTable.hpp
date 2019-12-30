#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <random>
#include <string>
#include "murmurFunction.hpp"
using namespace std;

#define HASH_TABLE_SIZE 5000

enum e_indexStatus {EMPTY, FULL, DELETED};

template <class itemT>
struct entry {
    string key;
    itemT value;
    entry * link;
};

template<class itemT>
class hashTable {
    // Hash Table implementation
    // Uses chaining for resolving conflicts
    // and Murmur3 function for the hash function
    // which is very efficent, fast and has good
    // distrubition.
    public:
        hashTable<itemT>(int size = HASH_TABLE_SIZE);
        ~hashTable<itemT>();
        hashTable<itemT>(const hashTable<itemT>& table);
        void insert(itemT item, string key);
        itemT& retrive(string key) const ;
        bool search(string key) const;
        void remove(string key);
        void print() const;
        // Return the item using key
        itemT& operator[](string key) const;
        void toArray(itemT output[]);

    private:
        entry<itemT> * dataArray;
        int capacity;
        int length;
        uint32_t seed;
        int * indexStatus;
        int hashFunc(string key) const ; // Uses Murmur3 Hash Function
};
#endif

template <class itemT>
hashTable<itemT>::hashTable(int size){
    srand(time(NULL));
    seed = rand();
    dataArray = new entry<itemT>[size];
    capacity = size;
    length = 0;
    indexStatus = new int[capacity]{EMPTY};
}

template <class itemT>
hashTable<itemT>::~hashTable<itemT>(){
    for (int i = 0; i < capacity && indexStatus[i] == FULL; i++){
        entry<itemT> * current = (dataArray[i]).link;
        entry<itemT> * next;
        while(current != NULL){
            next = current->link;
            delete current;
            current = next;
        }
    }
    delete [] dataArray;
    delete [] indexStatus;
}

template <class itemT>
int hashTable<itemT>::hashFunc(string key) const{
    // Hash Function, uses Murmur3_x64_128
    const char * keyCharArray = key.c_str();
    int keyLength = key.length();
    uint64_t * hashes = new uint64_t[2];
    int hash = 0;
    murmur(keyCharArray, keyLength, seed, hashes);
    hash += hashes[0] % capacity;
    hash += hashes[1] % capacity;
    hash = hash % capacity;
    return hash;
}

template <class itemT>
void hashTable<itemT>::insert(itemT item, string key){
    int hash = hashFunc(key);
    if (indexStatus[hash] != FULL){
        indexStatus[hash] = FULL;
        dataArray[hash] = entry<itemT> {key, item, nullptr};
        length++;
    }
    else if (dataArray[hash].key == key){
        cout << "Key " << key << " has already been inserted."
            << "Not allowing duplicates." << endl;
    }
    else {
        entry<itemT> * temp = &dataArray[hash];
        while(temp->link != NULL){
            temp = temp->link;
        }
        temp->link = new entry<itemT> {key, item, nullptr}; 
        length++;
    }
}

template <class itemT>
itemT& hashTable<itemT>::retrive(string key) const {
    // Returns the item for given key
    int hash = hashFunc(key);
    if (indexStatus[hash] != FULL){
        throw invalid_argument("Key not found");
    }
    entry<itemT>* current = &dataArray[hash];
    while (current->key != key){
        if (current->link != NULL) {
            current = current->link;
        }
        else {
            throw std::invalid_argument("Key not found");
        }
    }
    
    return current->value;
}


template <class itemT>
bool hashTable<itemT>::search(string key) const {
    // Returns true if entry with given key is present
    try {
        retrive(key);
    } 
    catch (invalid_argument& e) {
        return false;
    }
    return true;
}

template <class itemT>
void hashTable<itemT>::remove(string key){
    int hash = hashFunc(key);
    if (indexStatus[hash] != FULL){
        return; // Item is not present in table
    }
    else if (indexStatus[hash] == FULL && (dataArray[hash]).key == key){
        indexStatus[hash] = EMPTY;
    }
    else {
        // Item is in one of the links
        entry<itemT> *current = &dataArray[hash];
        entry<itemT> *next;
        while (current->link != NULL){
            next = current->link;
            if (next->key == key){
                current->link = next->link;
                delete next;
            }
            else {
                current = current->link;
            }
        }
    }
}

template <class itemT>
itemT& hashTable<itemT>::operator[](string key) const {
    //retrive with the syntax : table["key"] 
    return retrive(key);
}

template <class itemT>
void hashTable<itemT>::print() const {
    // Print all the items, accessing each of them
    for (int i = 0; i < capacity; i++){
        if (indexStatus[i] == FULL){
            entry<itemT> *m = &dataArray[i];
            cout << m->value;
            while(m->link != NULL){
                m = m->link;
                cout << m->value;
            }
        }
        else {
            continue;
        }
    }
    cout << endl;
}

template <class itemT>
void hashTable<itemT>::toArray(itemT *output){
    // Copy all the items to given array
    int j = 0;
    for (int i = 0; i < capacity; i++){
        if (indexStatus[i] == FULL){
            entry<itemT> *m = &dataArray[i];
            output[j++] = m->value;
            while (m->link != NULL){
                m = m->link;
                output[j++] = m->value;
            }
        }
    }
}
