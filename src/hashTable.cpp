#include "murmurFunction.hpp"
#include "hashTable.hpp"

#include <random>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

template <class itemT>
hashTable<itemT>::hashTable(int size){
    srand(time(NULL));
    seed = (const uint32_t)rand();
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
            delete * current;
            current = next;
        }
    }
    delete [] dataArray;
    delete [] indexStatus;
}

template <class itemT>
hashTable<itemT>::hashTable(const hashTable<itemT>& table){
    capacity = table.capacity;
    length = table.length;
    seed = table.seed;
    indexStatus = new int[capacity];
    dataArray = new entry<itemT>[capacity];
    for (int i = 0; i < capacity && table.indexStatus[i] == FULL; i++){
        this->dataArray[i] = table.dataArray[i];
        entry<itemT> * current = this->dataArray[i];
        entry<itemT> * currentTable = table.dataArray[i];
        while(currentTable->link != NULL){
            current->link = new entry<itemT>;
            current = current->link;
            currentTable = currentTable->link;
            current->key = currentTable->key;
            current->value = currentTable->value;
        }
        this->indexStatus[i] = table.indexStatus[i];
    }
}

template <class itemT>
int hashTable<itemT>::hashFunc(string key){
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
        cout << "Key " << key << " has already been inserted.\n"
            << "Not allowing duplicates." << endl;

    }
    else {
        entry<itemT> * temp = dataArray[hash];
        while(temp->link != NULL){
            temp = temp->link;
        }
        temp->link = new entry<itemT> {key, item, nullptr}; 
        length++;
    }
}

template <class itemT>
itemT& hashTable<itemT>::retrive(string key) const {
    int hash = hashFunc(key);
    if (indexStatus[hash] != FULL){
        throw invalid_argument("Key not found");
    }
    entry<itemT> & current = dataArray[hash];
    while (current.key != key){
        if (current.link != NULL) {
            current = *current->link;
        }
        else {
            cout << "The item with the key {" << key 
                << "} is not found" << endl;
            throw std::invalid_argument("Key not found");
        }
    }
    
    return current.value;
}


template <class itemT>
bool hashTable<itemT>::search(string key) const {
    entry<itemT> entry;
    try {
        entry = retrive(key);
    } 
    catch (invalid_argument& e) {
        return false;
    }
    return entry.key == key;
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
    return retrive(key);
}


template <class itemT>
hashTable<itemT>::iterator::iterator(){
    curPos = {0,0};
    int endLastIndex = 0;
    entry<itemT> * temp = this->dataArray[this->capacity];
    while (temp->link != nullptr){
        endLastIndex++;
        temp = temp->link;
    }
    endPos = {this->capacity,endLastIndex};
    while (this->indexStatus[curPos[0]] != FULL){
        curPos[0]++;
    }
    currentEntry = this->dataArray[curPos[0]];
}

template <class itemT>
hashTable<itemT>::iterator::~iterator(){ }

template <class itemT>
typename hashTable<itemT>::iterator& hashTable<itemT>::iterator::operator++(){
    entry<itemT> * temp = currentEntry;
    if (temp->link != NULL){
        currentEntry = temp->link;
        curPos[1]++;
        return *this;
    }
    else {
        while (this->indexStatus[++curPos[0]] != FULL){
            continue;
        }
        curPos[2] = 0;
        currentEntry = this->dataArray[curPos[0]];
        return *this;
    }
}

template <class itemT>
bool hashTable<itemT>::iterator::operator==(hashTable<itemT>::iterator &i){
    return (currentEntry->key == i.currentEntry->key);
}

template <class itemT>
bool hashTable<itemT>::iterator::operator!=(hashTable<itemT>::iterator &i){
    return (currentEntry->key != i.currentEntry->key);
}

template <class itemT>
itemT& hashTable<itemT>::iterator::operator*(){
    return *currentEntry;
}

template <class itemT>
typename hashTable<itemT>::iterator hashTable<itemT>::iterator::begin(){
    curPos = {0,0};
    while (this->indexStatus[curPos[0]] != FULL){
        curPos[0]++;
    }
    currentEntry = this->dataArray[curPos[0]];
}

template <class itemT>
typename hashTable<itemT>::iterator hashTable<itemT>::iterator::end(){
    curPos[0] = endPos[0];
    curPos[1] = 0;
    while (this->dataArray[curPos[0]] != FULL){
        curPos[0]--;
    }
    entry<itemT> * temp = this->dataArray[curPos[0]];
    while (temp->link != NULL){
        temp = temp->link;
        curPos[1]++;
    }
    currentEntry = temp;
}

