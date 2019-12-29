#include "hashTable.hpp"
#include <fstream>
#include <iostream>
#include <cassert>

#define ALLPRODUCTS_SIZE 5000
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

// swapping elements
void swap(product* a, product* b)
{
	product temp = *a;
	*a = *b;
	*b = temp;
}

//take the last element as pivot, put it in its place in sorted array
//if element is smaller than pivot put it to left, if its larger than pivot put it to right
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



//printing func.
void printArray(product arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
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
    product temp;
    hashTable<product> table;
    string dummy;
    string quantityString;
    ifstream dataF("OnlineRetail.csv");
    product allProducts[ALLPRODUCTS_SIZE] {};

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

    quickSort(allProducts,0,ALLPRODUCTS_SIZE-1);
    for (int i = ALLPRODUCTS_SIZE - 1; i >= ALLPRODUCTS_SIZE - 10; i--){
        cout << allProducts[i];
    }
    /*table.print();*/

    return 0;
}
