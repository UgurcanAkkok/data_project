#include "hashTable.hpp"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

class product {
    public:
    string stockCode;
    string desc;
    int quantity;
    friend ostream& operator<<(ostream& out,const product& p){
        out << p.stockCode << ":    " << p.desc
            << " => " << p.quantity << endl;
        return out;
    }
};



int main(){
    product temp;
    hashTable<product> table;
    string dummy;
    string quantityString;
    ifstream dataF("OnlineRetail.csv");
    product allProducts[50000];

    // Getting the header out of the way
    getline(dataF,dummy);
    while(dataF.good()){
        getline(dataF, dummy, ';'); //Invoice No
        getline(dataF, temp.stockCode, ';'); //Stock Code
        getline(dataF, temp.desc, ';'); //Description
        getline(dataF, quantityString, ';'); //Quantity
        getline(dataF, dummy, ';'); //Invoice Date
        getline(dataF, dummy, ';'); //Unit Price
        getline(dataF, dummy, ';'); //CustomerId
        getline(dataF, dummy); //Country
        temp.quantity = std::stoi(quantityString);
        if (table.search(temp.stockCode))
            (table[temp.stockCode]).quantity += temp.quantity;
        else
            table.insert(temp,temp.stockCode);
    }

    table.toArray(allProducts);
    cout << allProducts[0];
    cout << allProducts[4];
    cout << allProducts[19];
    /*table.print();*/

    return 0;
}
