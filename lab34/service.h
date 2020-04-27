#pragma once
#include "repository.h"
#include <stdio.h>


int addSubstance_service(DynamicArray* dynArray, char* catalogingNumber, char* state, char* intededUse, int potency);

int updateSubstance_service(DynamicArray* dynArray, char catalogingNumber[], char state[], char intededUse[], int potency);

int deleteSubstance_service(DynamicArray* dynArray,char catalogingNumber[]);

void listSubstances(DynamicArray* substRepo, char listSubstances[]);

void listSubstancesByIntendedUse(DynamicArray* substRepo, char intendedUse[], char listSubstances[]);

void sortSubstancesByPotency(DynamicArray* substSort);

void sortSubstancesByState(DynamicArray* substSort);

void listDecreasingPotency(DynamicArray* substRepo, char listSubstances[]);

void listMaximumPotency(DynamicArray* substRepo, char listSubstances[]);

void listPotencyLessThan(DynamicArray* substRepo, int value, char listSubstances[]);