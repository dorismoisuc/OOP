#include"Repo.h"
#include<string>

using namespace std;

void Repository::addChore(const Chore c)
{
	this->chores.add(c);
}

void Repository::updateChore(const Chore c)
{
	DynamicVector<Chore> chores = this->getChores();
	for (int i = 0; i < chores.getSize(); i++)
	{
		if (chores.get(i).getTitle() == c.getTitle())
			this->chores.update(c, i);
	}
}

void Repository::deleteChore(const std::string& title)
{
	DynamicVector<Chore> chores = this->getChores();
	for (int i = 0; i < chores.getSize(); i++)
	{
		if (chores.get(i).getTitle() == title)
			this->chores.deleteByPosition(i);
	}
}

DynamicVector<Chore> Repository::getChores()
{
	return chores;
}

bool Repository::isTitle(const Chore c,const std::string&title)
{
	if (c.getTitle() == title)
		return true;
	return false;
}

int Repository::getSize(DynamicVector<Chore> repo)
{
	return repo.getSize();
}


RepoServant::RepoServant()
{
	this->choresServant = choresServant;
}

void RepoServant::addChoreS(Chore c)
{
	choresServant.add(c);
}

DynamicVector<Chore> RepoServant::getForServant()
{
	return choresServant;
}

Chore Repository::get_by_title(std::string title)
{
	for (int i = 0; i < chores.getSize(); ++i)
	{
		if (chores[i].getTitle() == title)
		{
			return chores[i];
		}
	}
}

Chore Repository::next()
{
	if (it == NULL)
	{
		it = chores.begin();
	}
	DynamicVector<Chore>::iterator aux = it;
	
	if (it != chores.end())
	{
		return*(it++);
	}
	
	else if (it == chores.end())
	{
		it = chores.begin();
		return *(it++);
	}
}
