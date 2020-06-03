#include "FileRepository.h"
#include "Validator.h"
#include<string>
#include<iostream>

using namespace std;

vector<Chore>FileRepo::load_chores()
{
	ifstream file{ this->Path };
	vector<Chore> chores;
	Chore c;
	while (file >> c)
		chores.push_back(c);
	file.close();
	return chores;
}

void FileRepo::save_chores(vector<Chore>chores)
{
	ofstream file{ this->Path };
	for (const auto& chore : chores)
		file << chore;
	file.close();
}

FileRepo::FileRepo() {}

void FileRepo::addChore(Chore& c)
{
	vector<Chore>chores = this->load_chores();
	chores.push_back(c);
	this->save_chores(chores);
}

void FileRepo::updateChore(Chore& c)
{	
	int ok = 0;
	vector<Chore>chores = this->load_chores();
	for (int i = 0; i < chores.size(); i++)
		if (chores.at(i).getTitle() == c.getTitle())
		{
			chores.at(i) = c;
			ok = 1;
		}
	if (ok == 0)
		throw RepoException("There is no such chore\n");
	this->save_chores(chores);
}

void FileRepo::deleteChore(const string& title)
{
	int ok = 0;
	vector<Chore>chores = this->load_chores();
	for (int i = 0; i < chores.size(); i++)
		if (chores.at(i).getTitle() == title)
		{
			chores.erase(chores.begin() + i);
			ok = 1;
		}
	if (ok == 0)
		throw RepoException("There is no such chore\n");
	this->save_chores(chores);
}			

vector<Chore> FileRepo::getChores()
{
	vector<Chore>chores = this->load_chores();
	return chores;
}

/*void FileRepo::initializeIterator()
{
	next_chores = this->load_chores();
	it = next_chores.end();
}*/

Chore FileRepo::get_by_title(string title)
{
	vector<Chore>chores = this->load_chores();
	for (const auto& chore : chores)
		if (chore.getTitle() == title)
			return chore;
}
/*
Chore FileRepo::next()
{
	if (next_chores.begin() != next_chores.end())
	{
		it = next_chores.begin();
	}
	else
	{
		cout << "No chores found!";
	}
	if (it != next_chores.end())
	{
		return *(it++);
	}
	else if (it == next_chores.end())
	{
		it = next_chores.begin();
		return *(it++);
	}
}
	*/

void FileRepo::set_file(string& Path)
{
	this->Path = Path;
}

int FileRepo::getPositionChore(const Chore&c)
{
	vector<Chore> chores = this->load_chores();
	vector<Chore>::iterator iteratorChores;
	iteratorChores = find(chores.begin(), chores.end(), c);

	int index = distance(chores.begin(), iteratorChores);
	return index;
}
int FileRepo::getRepoSize()
{
	std::vector<Chore> chores = this->load_chores();
	return chores.size();
}
Chore FileRepo::getChore()
{
	std::vector<Chore> chores = this->load_chores();
	return chores[this->iteratorIndex];
}

void FileRepo::nextC()
{
	this->iteratorIndex++;
	if (this->iteratorIndex == this->getRepoSize())
		this->iteratorIndex = 0;
}
/*
void FileRepo::initializeIt()
{
	next_chores = this->load_chores();
	it = next_chores.end();
}

Chore FileRepo::nextChore()
{
	if (it == next_chores.end())
		it = next_chores.begin();
	return *(it++);
}
*/