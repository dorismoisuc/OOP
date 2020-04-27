#include "assert.h"
#include "unitests.h"

void testSubstance()
{

	char catNr[] = "7";
	char state[] = "a";
	char intendedUse[] = "b";
	int potency = 3;
	Substance* testSubstance = createSubstance(catNr, state, intendedUse, potency);
	assert(strcmp(getCatalogingNumber(testSubstance), "7") == 0);
	assert(getPotency(testSubstance) == 3);
	assert(strcmp(getState(testSubstance), "a") == 0);
	assert(strcmp(getIntendedUse(testSubstance), "b") == 0);
	destroySubstance(testSubstance);

}

void test_Add()
{

	DynamicArray* testSubstRepo = createArray(1, &destroySubstance, &copySubstance);
	assert(addSubstance_service(testSubstRepo, "7", "a", "b", 3) == 1);
	assert(getPotency(testSubstRepo->elems[0]) == 3);
	assert(addSubstance_service(testSubstRepo, "7", "b", "c", 3) == -1);
	destroyArray(testSubstRepo);

}

void test_Update()
{
	DynamicArray* testSubstRepo = createArray(1, &destroySubstance, &copySubstance);
	assert(addSubstance_service(testSubstRepo,"7", "a", "b", 3) == 1);
	assert(updateSubstance_service(testSubstRepo, "7", "b", "a", 3) == 1);
	assert(updateSubstance_service(testSubstRepo, "3", "a", "b", 3) == -1);
	assert(getPotency(testSubstRepo->elems[0] == 3));
	destroyArray(testSubstRepo);

}

void test_Delete()
{

	DynamicArray* testSubstRepo = createArray(1, &destroySubstance, &copySubstance);
	assert(addSubstance_service(testSubstRepo, "7", "a", "b", 3) == 1);
	assert(deleteSubstance_service(testSubstRepo, "7") == 1);
	assert(deleteSubstance_service(testSubstRepo, "3")==-1);
	destroyArray(testSubstRepo);

}

void test_List()
{

	DynamicArray* testSubstRepo = createArray(1, &destroySubstance, &copySubstance);
	assert(addSubstance_service(testSubstRepo, "7", "a", "b", 3) == 1);
	char testString[42];
	testString[0] = 0;
	listSubstances(testSubstRepo, testString);
	assert(strcmp(testString, "7 a b 3\n") == 0);
	destroyArray(testSubstRepo);

}

void test()
{
	testSubstance();
	test_Add();
	test_Delete();
	test_Update();
	test_List();
}