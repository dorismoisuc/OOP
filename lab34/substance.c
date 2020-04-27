#include "substance.h"
#include<stdlib.h>

/*
input: cataloging number, state, intended use, potency
output: the substance created

*/
Substance *createSubstance(char* catalogingNumber, char *state, char *intendedUse, int potency)
{

	Substance *substance = (Substance*)malloc(sizeof(Substance));
	substance->catalogingNumber = (char*)malloc(sizeof(char)*(strlen(catalogingNumber)+1));
	strcpy(substance->catalogingNumber,catalogingNumber);
	substance->state = (char*)malloc(sizeof(char) * (strlen(state) + 1));
	strcpy(substance->state, state);
	substance->intendedUse = (char*)malloc(sizeof(char) * (strlen(intendedUse) + 1));
	strcpy(substance->intendedUse, intendedUse);
	substance->potency = potency;
	return substance;

}
/*
input: the substance
output: returns the cataloging number

*/
char* getCatalogingNumber(Substance* subst)
{

	return subst->catalogingNumber;
}
/*
input: the substance
output: returns the state

*/
char* getState(Substance* subst)
{
	return subst->state;
}
/*
input: the substance
output: returns the intended use

*/
char* getIntendedUse(Substance* subst)
{
	return subst->intendedUse;
}
/*
input: the substance
output: returns the potency

*/
int getPotency(Substance* subst)
{
	if (subst == NULL)
		return;
	return subst->potency;
}
/*
input: the substance for destroy
output: - 
the substance is destroyed

*/
void destroySubstance(Substance* substForDestroy)
{

	if (substForDestroy == NULL)
		return;
	free(substForDestroy->catalogingNumber);
	free(substForDestroy->state);
	free(substForDestroy->intendedUse);
	free(substForDestroy);

}

/*
input: a substance
output: a copy of the substance

*/
Substance* copySubstance(Substance* substToCopy)
{
	Substance* copy = (Substance*)malloc(sizeof(Substance));
	copy->catalogingNumber = (char*)malloc(sizeof(char)*(strlen(substToCopy->catalogingNumber)+1));
	strcpy(copy->catalogingNumber,substToCopy->catalogingNumber);
	copy->state = (char*)malloc(sizeof(char) * (strlen(substToCopy->state) + 1));
	strcpy(copy->state, substToCopy->state);
	copy->intendedUse = (char*)malloc(sizeof(char) * (strlen(substToCopy->intendedUse) + 1));
	strcpy(copy->intendedUse, substToCopy->intendedUse);
	copy->potency = substToCopy->potency;
	return copy;

}
/*
input: a substance, a string
output: - creates a string with the substance's values 
*/
void createString(Substance* printSubstance, char concatenate[])
{
	char aux[41];
	strcpy(aux,printSubstance->catalogingNumber);
	strcat(concatenate, aux);
	strcat(concatenate, " ");
	strcat(concatenate, printSubstance->state);
	strcat(concatenate, " ");
	strcat(concatenate, printSubstance->intendedUse);
	strcat(concatenate, " ");
	_itoa(printSubstance->potency, aux, 10);
	strcat(concatenate, aux);
	strcat(concatenate, "\n");

}