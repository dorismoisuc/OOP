#include"Repo.h"
#include<string>

using namespace std;

Repository::Repository()
{
	this->chores = chores;
}

void Repository::addChore(Chore &c)
{
	chores.push_back(c);
}

void Repository::updateChore(Chore &c)
{
	for (int i = 0; i < chores.size(); i++)
	{
		if (chores.at(i).getTitle() == c.getTitle())
			this->chores.at(i) = c;
	}
}

void Repository::deleteChore(const string& title)
{
	for (int i = 0; i < chores.size(); i++)
	{
		if (chores.at(i).getTitle() == title)
			chores.erase(chores.begin()+i);
	}
}

vector<Chore> Repository::getChores()
{
	return this->chores;
}

bool Repository::isTitle(const Chore c,const std::string&title)
{
	if (c.getTitle() == title)
		return true;
	return false;
}

int Repository::getSize(vector<Chore> repo)
{
	return repo.size();
}


RepoServant::RepoServant()
{
	this->choresServant = choresServant;
}

void RepoServant::addChoreS(Chore &c)
{
	choresServant.push_back(c);
}

vector<Chore> RepoServant::getForServant()
{
	return this->choresServant;
}

Chore Repository::get_by_title(string title)
{
	for (const auto&chore:chores)
	{
		if (chore.getTitle()==title)
		{
			return chore;
		}
	}
}

Chore Repository::get_by_type(string type)
{
	for (const auto& chore : chores)
	{
		if (chore.getType() == type)
		{
			return chore;
		}
	}
}
void Repository::readFromFile()
{
	ifstream file(this->filename);
	if (!file.is_open())
		cout << "File couldn't be opened";
	else
	{
		Chore c;
		while (file >> c)
			this->chores.push_back(c);
		file.close();
	}

}
void Repository::writeToFile()
{
	ofstream file(this->filename);
	if (!file.is_open())
		cout << "File couldn't be opened";
	else
	{
		for (auto c : this->chores)
		{
			file << c;
		}
		file.close();
	}
}
/*
void Repository::initializeIterator()
{
	it = chores.end();
}

Chore Repository::next()
{
	it = chores.begin();
	if (it != chores.end())
	{
		return*(it++);
	}
	else if(it==chores.end())
	{
		it = chores.begin();
		return *(it++);
	}
}
*/


