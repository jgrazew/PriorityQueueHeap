#pragma once

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdlib.h>
#include <stdio.h>

typedef enum heapType {Min, Max} heapType;

//Declaration of Heap using a Opaque pointer
typedef struct Heap Heap;

Heap* CreateNewHeap(int, heapType);
int GetLeftChild(Heap*, int);
int GetRightChild(Heap*, int);
int GetMaximumElementInHeap(Heap*);
void Insert(Heap*, int);
static void ResizeHeap(Heap*);
void DestroyHeap(Heap*);
void PercolateDown(Heap*, int);
void BuildHeap(Heap*, int[], int);
void HeapSort(int[], int);
void PrintHeap(Heap*, int);

#endif // !PRIORITYQUEUE_H

