#include "hashTable.hpp"

#include <iostream>
struct item {
    const char * key;
    int value;
};

int main(){
   hashTable<int> t(100); 
   item a {"aile", 123};
   item b {"baba", 4246};
   item c {"cocuk", 82};
   item d {"yuksel", 41354};
   t.insert(a.value, a.key);
   t.insert(b.value, b.key);
   t.insert(c.value, c.key);
   t.insert(d.value, d.key);

   t.print();


}
