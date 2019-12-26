#include "hashTable.hpp"

int main(){
    hashTable<int> t(5);
    t.insert(7,"happy");
    t.insert(412,"sad");
    t.insert(511,"angry");
    t.insert(421,"bus");
    t.insert(41231,"nowhere");
    t.insert(593,"wallpaper");
    t.print();

    int angry = t["angry"];
    int null = t["null"];
    bool isNull = t.search("null");
    int sad = t.retrive("sad");
    bool isSad = t.search("sad");

}
