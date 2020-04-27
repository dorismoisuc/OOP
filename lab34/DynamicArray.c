#include "DynamicArray.h"


/*
input: capacity, destroy function, copy function
output: created dynamic array
*/
DynamicArray* createArray(int capacity, destroySomething destroy, copySomething copy)
{
	DynamicArray* TArray = (DynamicArray*)malloc(sizeof(DynamicArray));
	TArray->capacity = capacity;
	TArray->size = 0;
	TArray->elems = (TElem*)malloc(sizeof(TElem) * capacity);
	TArray->destroy = destroy;
	TArray->copy = copy;

	return TArray;
}

/*
input: dynamic array
output: -
destroys a dynamic array
*/
void destroyArray(DynamicArray* TArray)
{

	if (TArray == NULL)
		return;

	for (int it = 0; it < TArray->size; it++)
	{
		TArray->destroy(TArray->elems[it]);
	}
	free(TArray->elems);
	free(TArray);

}

/*
input: dynamic array, and the element to add to it 
output: - 
this functions adds an element to a dynamic array

*/
void addArray(DynamicArray* TArray, TElem elem)
{

	if (TArray->size == TArray->capacity)
	{
		resize(TArray);
	}
	TArray->elems[TArray->size++] = TArray->copy(elem);

}

/*
input: dynamic array
output: the dynamic array resized

*/

void resize(DynamicArray* TArray)
{
	TArray->capacity *= 2;
	TElem* newElems = (TElem*)malloc(sizeof(TElem) * TArray->capacity);
	for (int it = 0; it < TArray->size; it++)
	{
		newElems[it] = TArray->elems[it];
	}
	free(TArray->elems);
	TArray->elems = newElems;
}

/*
input: dynamic array
output: copy of the dynamic array

*/

DynamicArray* copyArray(DynamicArray* TArray)
{
	DynamicArray* newTArray = (DynamicArray*)malloc(sizeof(DynamicArray));
	newTArray->capacity = TArray->capacity;
	newTArray->size = TArray->size;
	newTArray->elems = (TElem*)malloc(sizeof(TElem) * newTArray->capacity);

	newTArray->destroy = TArray->destroy;
	newTArray->copy = TArray->copy;

	for (int it = 0; it < TArray->size; it++)
		newTArray->elems[it] = TArray->copy(TArray->elems[it]);

	return newTArray;

}

