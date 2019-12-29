#include "hashTable.hpp"

int main(){
    hashTable<int> t(5000);

    srand(0);
    for (int i = 0; i < 500000; i++){
        int value = rand();
        t.insert(value, to_string(value));
    }

    //t.print();
}
