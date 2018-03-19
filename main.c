#include "stdafx.h"
#include "PriorityQueue.h"

int main()
{
	int arr[] = { 15, 9, 18, 4, 8, 12 };
	int n = sizeof(arr) / sizeof(arr[0]);

	HeapSort(arr, n);

    return 0;
}
