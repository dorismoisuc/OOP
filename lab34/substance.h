#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<string.h>

typedef struct {

	char* catalogingNumber;
	char *state;
	char *intendedUse;
	int potency;

}Substance;

Substance* createSubstance(char* catalogingNumber, char* state, char* intededUse, int potency);

char* getCatalogingNumber(Substance *subst);
char *getState(Substance *subst);
char* getIntendedUse(Substance* subst);
int getPotency(Substance *subst);

void destroySubstance(Substance* substForDestroy);

Substance* copySubstance(Substance *substToCopy);

void createString(Substance* printSubstance, char concatenate[]);