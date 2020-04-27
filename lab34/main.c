#define _CRTDBG_MAP_ALLOC
#include "ui.h"
#include "unitests.h"
#include <crtdbg.h>

int main()
{
	test();
	DynamicArray* substRepo = createArray(1, &destroySubstance, &copySubstance);
	DynamicArray* repoStack = createArray(1, &destroyArray, &copyArray);
	start(substRepo, repoStack);
	destroyArray(substRepo);
	destroyArray(repoStack);
	_CrtDumpMemoryLeaks();
	return 0;

}