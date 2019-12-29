#include <iostream>	

using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int arr[], int first, int last, int n)

{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int partition(int arr[], int l, int r, int x)
{
	int pivot = arr[x]; // pivot 
	int i = (r - 1); // küçüðün indeksi

	for (int j = r; j <= x - 1; j++)
	{
		// þimdiki element pivottan küçükse
		if (arr[j] < pivot)
		{
			i++; // küçük elementin indeksii arttýr
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[r]);
	return (i + 1);
}

int findMedian(int arr[], int n)
{
	sort(arr, 0, n -1,n);
		return arr[n / 2];
}

// Returns k'th smallest element in arr[l..r] in worst case 
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT 
int kthSmallest(int arr[], int l, int r, int k)
{
	// If k is smaller than number of elements in array 
	if (k > 0 && k <= r - l + 1)
	{
		int n = r - l + 1; // Number of elements in arr[l..r] 

		// Divide arr[] in groups of size 5, calculate median 
		// of every group and store it in median[] array. 
		int i; // There will be floor((n+4)/5) groups; 
		int* median = new int[(n + 4) / 5] ;
		for (i = 0; i < n / 5; i++)
			median[i] = findMedian(arr + l + i * 5, 5);
		if (i * 5 < n) //For last group with less than 5 elements 
		{
			median[i] = findMedian(arr + l + i * 5, n % 5);
			i++;
		}

		// Find median of all medians using recursive call. 
		// If median[] has only one element, then no need 
		// of recursive call 
		int medOfMed = (i == 1) ? median[i - 1] :
			kthSmallest(median, 0, i - 1, i / 2);

		// Partition the array around a random element and 
		// get position of pivot element in sorted array 
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k 
		if (pos - l == k - 1)
			return arr[pos];
		if (pos - l > k - 1)  // If position is more, recur for left 
			return kthSmallest(arr, l, pos - 1, k);

		// Else recur for right subarray 
		return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
	}

	// If k is more than number of elements in array 
	return INT_MAX;
}
int kthlargest(int arr[],int n, int k) {
	return kthSmallest(arr, 0, n - 1, n - k + 1);




}

int main()
{
	int arr[] = { 12, 3, 5, 7, 4, 19, 26 };
	int n = sizeof(arr) / sizeof(arr[0]), k = 3;
	cout << "K'th largest element is "
		<< kthlargest(arr, n, k);

	return 0;
	
}

//
//int main()
//{
//	int arr[] = { 11,12,13,14,15,16 };
//	int n = sizeof(arr) / sizeof(arr[0]);
//	sort(arr, 0, n - 1);
//	cout << "kth largest: \n"<<kthlargest(arr,0,n-1,k);
//	
//	return 0;
//
//	system("PAUSE");
//}