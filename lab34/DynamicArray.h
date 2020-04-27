#pragma once
#include "Substance.h"
#include<stdlib.h>

typedef void* TElem;
typedef void(*destroySomething)(TElem);
typedef TElem(*copySomething)(TElem);

typedef struct
{
	TElem* elems;
	int size, capacity;
	destroySomething destroy;
	copySomething copy;

}DynamicArray;

DynamicArray* createArray(int capacity, destroySomething destroy, copySomething copy);

void destroyArray(DynamicArray *TArray);

void addArray(DynamicArray *TArray, TElem elem);

void resize(DynamicArray *TArray);

DynamicArray* copyArray(DynamicArray* TArray);
