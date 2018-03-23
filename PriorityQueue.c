#include "stdafx.h"
#include "PriorityQueue.h"

struct Heap {
	int *array;
	int countOfElements;
	int capacityOfHeap;
	heapType theHeapType;
};

Heap* CreateNewHeap(int capacity, heapType theHeapType)
{
	Heap* theHeap = (Heap*)malloc(sizeof(Heap));
	if (theHeap == NULL) 
	{
		printf("Memory Error");
		return 0;
	}
		
	theHeap->theHeapType = theHeapType;
	theHeap->countOfElements = 0;
	theHeap->capacityOfHeap = capacity;
	theHeap->array = (int*)malloc(sizeof(int)*theHeap->capacityOfHeap);
	if (theHeap->array == NULL)
	{
		printf("Memory Error");
		return 0;
	}
	return theHeap;
}

int GetLeftChild(Heap* theHeap, int nodeLocation)
{
	int leftNode = 2 * nodeLocation + 1;
	if (leftNode >= theHeap->countOfElements)
		return -1;
	return leftNode;
}

int GetRightChild(Heap* theHeap, int nodeLocation)
{
	int rightNode = 2 * nodeLocation + 2;
	if (rightNode >= theHeap->countOfElements)
		return -1;
	return rightNode;
}

void Insert(Heap* theHeap, int data)
{
	//use this vatriable to traverse the tree locations
	int i;
	if (theHeap->countOfElements == theHeap->capacityOfHeap)
	{
		//double the heap size if we are at capactity
		ResizeHeap(theHeap);
	}

	theHeap->countOfElements++;
	//get the max location pg.197
	i = theHeap->countOfElements - 1;
  
	while (i >= 0 && data > theHeap->array[(i - 1) / 2])
	{
		theHeap->array[i] = theHeap->array[(i - 1) / 2];
		//get the next parent location
		i = i - (1 / 2);
	}

	theHeap->array[i] = data;
}

void ResizeHeap(Heap* theHeap)
{
	int* theOldArray = theHeap->array;
	theHeap->array = (int*)malloc(sizeof(int)*theHeap->capacityOfHeap * 2);

	if (theHeap->array == NULL)
	{
		printf("Memory Error");
		return;
	}

	for (int i = 0; i != theHeap->capacityOfHeap; i++)
	{
		theHeap->array[i] = theOldArray[i];
	}
	theHeap->capacityOfHeap *= 2;
	free(theOldArray);
}

void PercolateDown(Heap* theHeap, int i)
{
	int max, temp;

	int leftChild = GetLeftChild(theHeap, i);
	int rightChild = GetRightChild(theHeap, i);

	if (leftChild != -1 && theHeap->array[leftChild] > theHeap->array[i])
		max = leftChild;
	else
		max = i;

	if (rightChild != -1 && theHeap->array[rightChild] > theHeap->array[max])
		max = rightChild;

	//if largest is not root- you will have to swap and make a recursive call
	if (max != i)
	{
		//swap to make the root the max
		temp = theHeap->array[i];
		theHeap->array[i] = theHeap->array[max];
		theHeap->array[max] = temp;

		PercolateDown(theHeap, max);
	}
}

void BuildHeap(Heap* theHeap, int arr[], int lengthOfArray)
{
	if (theHeap == NULL)
		return;

	while (lengthOfArray > theHeap->capacityOfHeap)
		ResizeHeap(theHeap);
	for (int i = 0; i < lengthOfArray; i++)
		theHeap->array[i] = arr[i];
	theHeap->countOfElements = lengthOfArray;
	//(h->count-1)/2 is the location of the first non-leaf node (i.e. the first node with children)
	int firstNonLeafNode = (lengthOfArray - 1) / 2;
	for (int i = firstNonLeafNode; i >= 0; i--)
		PercolateDown(theHeap, i);
}

void HeapSort(int arr[], int lengthOfArray)
{
	Heap* theHeap = CreateNewHeap(lengthOfArray, Max);
	int oldSize, temp;
	BuildHeap(theHeap, arr, lengthOfArray);
	oldSize = theHeap->countOfElements;
	for (int i = lengthOfArray - 1; i > 0; i--)
	{
		//index 0 is the largest element
		//swap -move current root to the end
		temp = theHeap->array[0];
		theHeap->array[0] = theHeap->array[theHeap->countOfElements-1]; 
		theHeap->array[theHeap->countOfElements-1] = temp;
		theHeap->countOfElements--;
		PercolateDown(theHeap, 0);
	}
	theHeap->countOfElements = oldSize;
	PrintHeap(theHeap, lengthOfArray);
}

void PrintHeap(Heap* theHeap, int lengthOfArray)
{
	for (int i = 0; i<lengthOfArray; ++i)
		printf("%d ", theHeap->array[i]);
	printf("\n");
}

