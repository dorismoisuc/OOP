using namespace std;
#include<assert.h>
#include "UnitTests.h"
#include "Chores.h"
#include "DynamicVector.h"
#include "Repo.h"
#include "Service.h"
#include<iostream>
#include<crtdbg.h>

void testChores()
{
	Chore();
	Chore newChore{ "Title", "Type", "19-02-2000", 1, "Vision" };
	assert(newChore.getTitle() == "Title");
	assert(newChore.getType() == "Type");
	assert(newChore.getLastPerformed() == "19-02-2000");
	assert(newChore.getTimesPerformed() == 1);
	assert(newChore.getVision() == "Vision");
}

/*void testAddDynamicVector()
{
	DynamicVector();
	DynamicVector newDynamicVector{ 10 };
	TElement element;
	newDynamicVector.add(element);
	assert(newDynamicVector.getSize() == 1);
}

void testDeleteDynamicVector()
{
	DynamicVector();
	DynamicVector newDynamicVector{ 10 };
	TElement element1;
	TElement element2;
	TElement element3;
	newDynamicVector.add(element1);
	newDynamicVector.add(element2);
	newDynamicVector.add(element3);
	assert(newDynamicVector.getSize() == 3);
	newDynamicVector.deleteByPosition(1);
	assert(newDynamicVector.getSize() == 2);

}
*/


void testRepoAddElement()
{
	Repository repo;
	Chore chore{ "Title","Type","01-01-1999",1,"Vision" };
	repo.addChore(chore);
	assert(repo.isTitle(chore, "Title") == true);
}

void testRepoDeleteElement()
{
	Repository repo;
	Chore chore{ "Title","Type","01-01-1999",1,"Vision" };
	DynamicVector<Chore> chores;
	repo.addChore(chore);
	repo.deleteChore("Title");
	assert(repo.getSize(chores) == 0);

}

void testServiceAddElement()
{
	Repository repo;
	Service service{ repo };
	service.addChore_service("Titlu", "Type", "01-01-1999", 1, "Vision");
	assert(service.checkExisting("Titlu") == 1);

}

void testServiceDeleteElement()
{
	Repository repo;
	Service service{ repo };
	service.addChore_service("Titlu", "Type", "01-01-1999", 1, "Vision");
	service.addChore_service("Titlu2", "Type2", "01-02-1999", 2, "Vision2");
	service.deleteChore_service("Titlu");
	assert(service.checkExisting("Titlu") == 0);

}

void testServiceUpdateElement()
{
	Repository repo;
	Service service{ repo };
	service.addChore_service("Titlu", "Type", "01-01-1999", 1, "Vision");
	service.updateChore_service("Titlu", "Type2", "01-02-1999", 1, "Vision");
	assert(service.checkExisting("Titlu") == 1);
}

void testServiceCheckExisting()
{
	Repository repo;
	Service service{ repo };
	service.addChore_service("Titlu", "Type", "01-01-1999", 1, "Vision");
	assert(service.checkExisting("Titlu") == 1);
	service.deleteChore_service("Titlu");
	assert(service.checkExisting("Titlu") == 0);
}

void test()
{
	testChores();
	//testAddDynamicVector();
	//testDeleteDynamicVector();
	testRepoAddElement();
	testRepoDeleteElement();
	testServiceAddElement();
	testServiceDeleteElement();
	testServiceUpdateElement();
	testServiceCheckExisting();
}