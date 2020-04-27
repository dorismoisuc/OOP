#include"Chores.h"
// #include"DynamicVector.h"
#include"Repo.h"
#include "Service.h"
#include "UI.h"
#include"UnitTests.h"
#include<crtdbg.h>

int main()
{
	system("color f4");
	//test();
	{
		FileRepo repo{};
		Service service{ repo };
		UI ui{ service };
		ui.run();
	}
	_CrtDumpMemoryLeaks();
}