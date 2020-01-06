#include "hashTable.hpp"
#include <fstream>
#include <iostream>
#include <cassert>

#define ALLPRODUCTS_SIZE 5000 // Number of distinct products
using namespace std;

class product {
    // We will insert this class to the table
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

// swapping elements
void swap(product* a, product* b)
{
	product temp = *a;
	*a = *b;
	*b = temp;
}

//take the last element as pivot, put it in its place in sorted array
//if element is smaller than pivot put it to left, if its larger than 
//pivot put it to right
int partition(product arr[], int first, int last)
{
	product pivot = arr[last]; // pivot 
	int i = (first - 1); // index of the small one

	for (int j = first; j <= last - 1; j++)
	{
		
		if ( (arr[j]).quantity <= pivot.quantity)
		{
			i++;
            swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[last]);
	return (i + 1);
}

//quicksorting func.
void quickSort(product arr[], int first, int last)
{
	if (first < last)
	{
		int pi = partition(arr, first, last);
		quickSort(arr, first, pi - 1);
		quickSort(arr, pi + 1, last);
	}
}

int main(){
    clock_t begin_time = clock();
    product temp; // Read into this and insert a copy of this
    hashTable<product> table;
    string dummy; // Read unneccessary info to this var
    string quantityString; //First read the quantity as string, then convert
    ifstream dataF("OnlineRetail.csv");
    product allProducts[ALLPRODUCTS_SIZE] {}; // Array to apply the sort

    // Getting the header out of the way
    getline(dataF,dummy);
    while(dataF.good()){
        getline(dataF, dummy, ';'); //Invoice No
        getline(dataF, temp.stockCode, ';'); //Stock Code
        getline(dataF, temp.desc, ';'); //Description
        getline(dataF, quantityString, ';'); //Quantity
        getline(dataF, dummy); // the rest
        temp.quantity = std::stoi(quantityString);
        /*if (table.search(temp.stockCode))
            (table[temp.stockCode]).quantity += temp.quantity;
        else
            table.insert(temp,temp.stockCode);*/
        try {
            (table[temp.stockCode]).quantity += temp.quantity;
        }
        catch (invalid_argument& e){
            table.insert(temp,temp.stockCode);
        }

    }

    table.toArray(allProducts);

    quickSort(allProducts,0,ALLPRODUCTS_SIZE-1);
    for (int i = ALLPRODUCTS_SIZE - 1; i >= ALLPRODUCTS_SIZE - 10; i--){
        cout << allProducts[i];
    }
    
    dataF.close();
    cout << (clock() - begin_time) / (float)CLOCKS_PER_SEC << " second";
    return 0;
}
