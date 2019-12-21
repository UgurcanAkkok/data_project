#pragma once
#include <string>

#define HASH_TABLE_SIZE 5000

enum e_indexStatus {EMPTY, FULL, DELETED};

using namespace std;
template <class itemT>
struct entry {
            string key;
            itemT value;
            entry * link;
};

// TODO: Iterator for this class
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

        class iterator {
            public:
                iterator();
                ~iterator();
                iterator& operator++(); // Prefix increment
                bool operator==(iterator& i);
                bool operator!=(iterator& i);
                itemT& operator*();

                iterator begin();
                iterator end();
            private:
                int curPos[2];
                int endPos[2];
                entry<itemT> * currentEntry;

        };

    private:
        entry<itemT> * dataArray;
        int capacity;
        int length;
        const uint32_t seed;
        int * indexStatus;

        int hashFunc(string key); // Uses Murmur3 Hash Function
};
