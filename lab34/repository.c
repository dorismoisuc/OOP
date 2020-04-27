#include "repository.h"


/*
input: cataloging number, dynamic array
output: the position where the substance with the given cataloging number is found
		-1 if it is not found
*/
int verifyExisting(char catalogingNumber[], DynamicArray* substRepo) 
{

	int it = 0;
	for (it = 0; it < substRepo->size; it++)
	{
		if (strcmp(getCatalogingNumber(substRepo->elems[it]), catalogingNumber)==0)
			return it;
	}
	return -1;

}
/*
input: a substance and a dynamic array
output: 1 if the substance is added  
*/
int addSubstance_repository(Substance* substToAdd, DynamicArray* substRepo)
{

	substRepo->elems[substRepo->size++]=copySubstance(substToAdd);
	return 1;

}
/*
input: a substance, a dynamic array, an index to the position to update
output: updated substance
*/
void updateSubstance_repository(Substance* substToUpdate, DynamicArray* substRepo, int iter)
{

	destroySubstance(substRepo->elems[iter]);
	substRepo->elems[iter] = copySubstance(substToUpdate);

}
/*
input : cataloging number, dynamic array
output: -1 if the cataloging number doesn't exist
		1 if the substance is deleted

*/
int deleteSubstance_repository(char catalogingNumber[], DynamicArray* substRepo)
{

	int iter = verifyExisting(catalogingNumber,substRepo);
	if (iter == -1)
	{
		return -1;
	}
	substRepo->size--;
	destroySubstance(substRepo->elems[iter]);
	for (int it = iter; it < substRepo->size; it++)
	{
		substRepo->elems[it] = substRepo->elems[it + 1];
	}
	return 1;

}
/*
input: dynamic array
output: all substances
*/
DynamicArray* allSubstances(DynamicArray* dynArray)
{

	DynamicArray* aux = createArray(dynArray->capacity, dynArray->destroy, dynArray->copy);
	for (int it = 0; it < dynArray->size; it++)
		addArray(aux, dynArray->elems[it]);
	return aux;
}
/*
input: dynamic array, a value
output: all substances with potency less than the given value

*/
DynamicArray* potencyLessThan(DynamicArray* dynArray, int value)
{
	DynamicArray* aux = createArray(dynArray->capacity, dynArray->destroy, dynArray->copy);
	for (int it = 0; it < dynArray->size; it++)
		if (getPotency(dynArray->elems[it]) < value)
			addArray(aux, dynArray->elems[it]);
	return aux;
	

}