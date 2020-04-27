#include"Service.h"
#include <iostream>
using namespace std;

DynamicVector<Chore> Service::getAllChoresInRepo()
{
	return repo.getChores();
}

int Service::checkExisting(const std::string& title)
{
	DynamicVector<Chore> chores = this->getAllChoresInRepo();
	for (int i = 0; i < chores.getSize(); i++)
	{
		if (chores.get(i).getTitle() == title)
			return 1;
	}
	return 0;
}

int Service::addChore_service(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision)
{
	Chore c{ title,type,lastPerformed,timesPerformed,vision };
	if (this->checkExisting(title) == 0)
	{
		this->repo.addChore(c);
		return 1;
	}
	return 0;
}

int Service::updateChore_service(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision)
{
	Chore c{ title,type,lastPerformed,timesPerformed,vision };
	if (this->checkExisting(title) == 1)
	{
		this->repo.updateChore(c);
		return 1;
	}
	return 0;
}

int Service::deleteChore_service(const std::string& title)
{
	if (this->checkExisting(title))
	{
		this->repo.deleteChore(title);
		return 1;
	}
	return 0;
}

DynamicVector<Chore> Service::get_by_type(const std::string& type, int timesPerformed)
{
	DynamicVector<Chore> filterChores;
	DynamicVector<Chore> chores = repo.getChores();
	for (int i = 0; i < chores.getSize(); ++i)
	{
		Chore c = chores.get(i);
		if (c.getType() == type && c.getTimesPerformed() < timesPerformed)
			filterChores.add(c);
	}
	if (filterChores.getSize() == 0)
	{
		cout<<"No chores matching";
	}
	return filterChores;
}

void Service::save(std::string title)
{
	Chore c = repo.get_by_title(title);
	repoServant.addChoreS(c);
}

DynamicVector<Chore> Service::getServantList()
{
	DynamicVector<Chore> chores = repoServant.getForServant();
	return chores;

}

Chore Service::next_service()
{
	return repo.next();
}