
#include <iostream>
using namespace std;

// swapping elements
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//take the last element as pivot, put it in its place in sorted array
//if element is smaller than pivot put it to left, if its larger than pivot put it to right
int partition(int arr[], int first, int last)
{
	int pivot = arr[last]; // pivot 
	int i = (first - 1); // index of the small one

	for (int j = first; j <= last - 1; j++)
	{
		
		if (arr[j] < pivot)
		{
			i++;
            swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[last]);
	return (i + 1);
}



//printing func.
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}


//quicksorting func.
void quickSort(int arr[], int first, int last)
{
	if (first < last)
	{
		int pi = partition(arr, first, last);

		quickSort(arr, first, pi - 1);
		quickSort(arr, pi + 1, last);
	}
}



int main()
{
	int arr[] = { 11,12,13,14,15,16 };
	int n = sizeof(arr) / sizeof(arr[0]);
	quickSort(arr, 0, n - 1);
	cout << "duzenlenmis array: \n";
	printArray(arr, n);
	return 0;

	system("PAUSE");
}

