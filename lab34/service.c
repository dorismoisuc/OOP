#include "service.h"

/*
input: dynamic array, cataloging number, state, intended use, potency
output: -1 if the substance already exists
		1 if the substance is added 

*/
int addSubstance_service(DynamicArray* substRepo, char* catalogingNumber, char* state, char* intendedUse, int potency)
{

	if (verifyExisting(catalogingNumber,substRepo)!=-1)
		return -1;
	Substance* substToAdd = createSubstance(catalogingNumber, state, intendedUse, potency);
	addArray(substRepo, substToAdd);
	destroySubstance(substToAdd);
	return 1;

}

/*
input: dynamic array, cataloging number, new state, new intended use, new potency
output: -1 if the substance doesn't exist
		1 if the substance is updated

*/
int updateSubstance_service(DynamicArray* substRepo, char catalogingNumber[], char* state, char* intendedUse, int potency)
{
	int updateIter = verifyExisting(catalogingNumber, substRepo);
	if (updateIter == -1)
		return -1;
	Substance* substToUpdate = createSubstance(catalogingNumber, state, intendedUse, potency);
	updateSubstance_repository(substToUpdate, substRepo, updateIter);
	destroySubstance(substToUpdate);
	return 1;

}
/*
input: dynamic array, cataloging number
output: the dynamic array modified after the delete
*/
int deleteSubstance_service(DynamicArray* substRepo, char catalogingNumber[])
{

	return deleteSubstance_repository(catalogingNumber, substRepo);
}
/*
input: dynamic array, string
output: - 
	the string containing all substances
*/
void listSubstances(DynamicArray* substRepo, char listSubstances[])
{

	for (int it = 0; it < substRepo->size; it++)
	{
		createString(substRepo->elems[it],listSubstances);
	}
}
/*
input: dynamic array, intended use, the string 
output: -
creates a string containing only the elements with the given intended use
*/
void listSubstancesByIntendedUse(DynamicArray* substRepo, char intededUse[], char listSubstances[])
{

	for (int it = 0; it < substRepo->size; it++)
	{
		if (strcmp(getIntendedUse(substRepo->elems[it]), intededUse) == 0)
		{
			createString(substRepo->elems[it],listSubstances);
		}
	}
}
/*
input: dynamic array
output: sorts the substances by potency
*/
void sortSubstancesByPotency(DynamicArray* substSort)
{

	for (int it = 0; it < substSort->size - 1; it++)
	{
		for (int it2 = it + 1; it2 < substSort->size; it2++)
		{
			if (getPotency(substSort->elems[it]) < getPotency(substSort->elems[it2]))
			{
				Substance* aux;
				aux = substSort->copy(substSort->elems[it]);
				substSort->destroy(substSort->elems[it]);
				substSort->elems[it] = substSort->copy(substSort->elems[it2]);
				substSort->destroy(substSort->elems[it2]);
				substSort->elems[it2] = substSort->copy(aux);
				substSort->destroy(aux);
			}
		}
	}

}
/*
input: dynamic array
output: sorts the substances by state
*/
void sortSubstancesByState(DynamicArray* substSort)
{

	for (int it = 0; it < substSort->size - 1; it++)
	{
		for (int it2 = it + 1; it2 < substSort->size; it2++)
		{
			if (strcmp(getState(substSort->elems[it]),getState(substSort->elems[it2]))>0)
			{
				Substance* aux;
				aux = substSort->copy(substSort->elems[it]);
				substSort->destroy(substSort->elems[it]);
				substSort->elems[it] = substSort->copy(substSort->elems[it2]);
				substSort->destroy(substSort->elems[it2]);
				substSort->elems[it2] = substSort->copy(aux);
				substSort->destroy(aux);
			}
		}
	}

}


/*
input: dynamic array, string
output: the string with the elems ordered decreasingly by potency
*/
void listDecreasingPotency(DynamicArray* substRepo, char listSubstances[])
{

	DynamicArray* substSort = allSubstances(substRepo);
	sortSubstancesByPotency(substSort);
	for (int it = 0; it < substSort->size; it++)
		createString(substSort->elems[it], listSubstances);
	destroyArray(substSort);

}
/*
input: dynamic array, the string
output: the string created with the maximum potency
*/
void listMaximumPotency(DynamicArray* substRepo, char listSubstances[])
{
	DynamicArray* maxPotency = allSubstances(substRepo);
	sortSubstancesByPotency(maxPotency);
	createString(maxPotency->elems[0], listSubstances);
	destroyArray(maxPotency);
}
/* 
input: dynamic array, a value, the string
ouput: creates a string with substances which have the potency < given value
*/
void listPotencyLessThan(DynamicArray* substRepo, int value, char listSubstances[])
{

	DynamicArray* lessThan = potencyLessThan(substRepo,value);
	sortSubstancesByState(lessThan);
	for (int it = 0; it < lessThan->size; it++)
		createString(lessThan->elems[it],listSubstances);
	destroyArray(lessThan);

}


