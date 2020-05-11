using namespace std;
#include<assert.h>
#include "UnitTests.h"
#include "Chores.h"
// #include "DynamicVector.h"
#include "Repo.h"
#include "Service.h"
#include "FileRepository.h"
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

void testAdd()
{
	string textFile = "fortests.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	//assert(service.addChore_service(title, type, lastPerformed, timesPerformed, vision) == 1);
	string title2 = "a", type2 = "b", lastPerformed2 = "c", vision2 = "d";
	int timesPerformed2 = 1;
	//assert(service.addChore_service(title2, type2, lastPerformed2, timesPerformed2, vision2) == 0);
	remove("fortests.txt");
}

void testUpdate()
{
	string textFile = "fortests.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	assert(service.addChore_service(title, type, lastPerformed, timesPerformed, vision) == 1);
	int timesPerformed2 = 2;
	string typeUpdate = "c", lastPerformedUpd = "d", visionUpd = "e";
	string invalidTitle = "p";
	assert(service.updateChore_service(title, typeUpdate, lastPerformedUpd, timesPerformed2, visionUpd) == 1);
	assert(service.updateChore_service(invalidTitle, type, lastPerformed, timesPerformed, vision) == 0);
	remove("fortests.txt");
}

void testDelete()
{
	string textFile = "fortests.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	assert(service.addChore_service(title, type, lastPerformed, timesPerformed, vision) == 1);
	string titleDelete = "a";
	assert(service.deleteChore_service(titleDelete) == 1);
	string title2 = "c";
	assert(service.addChore_service(title2, type, lastPerformed, timesPerformed, vision) == 1);
	assert(service.deleteChore_service(titleDelete) == 0);
	remove("fortests.txt");
}

void testSave()
{

	string textFile = "fortests.txt";
	FileRepo repo{};
	Service service{ repo };
	service.file_location(textFile);
	string title = "a", type = "b", lastPerformed = "c", vision = "d";
	int timesPerformed = 1;
	assert(service.addChore_service(title, type, lastPerformed, timesPerformed, vision) == 1);
	service.save(title);
	assert(service.getServantList().size() == 1);
	remove("fortests.txt");

}
void testToString()
{
	Chore c{ "a","b","c",1,"d" };
	string toString = "Title:a, Type: b, LastPerformed: c, TimesPerformed: 1, Vision: d";
	assert(c.toString() == toString);
}

void test()
{
	testChores();
	testAdd();
	testDelete();
	testUpdate();
	testSave();
	testToString();
}