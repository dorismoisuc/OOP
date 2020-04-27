#pragma once 
#include "substance.h"
#include "DynamicArray.h"

typedef struct {
	
	Substance* substances;
	int size, capacity;

}Substances;

int verifyExisting(char catalogingNumber[], DynamicArray* substRepo);

int addSubstance_repository(Substance* substToAdd, DynamicArray* substRepo);

int deleteSubstance_repository(char catalogingNumber[], DynamicArray* substRepo);

void updateSubstance_repository(Substance* substUpdate, DynamicArray* substRepo, int iter);

DynamicArray* allSubstances(DynamicArray* dynArray); 

DynamicArray* potencyLessThan(DynamicArray* dynArray, int value);