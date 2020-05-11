#include"Service.h"
#include "FileRepository.h"
#include <iostream>
#include "Validator.h"
using namespace std;

vector<Chore> Service::getAllChoresInRepo()
{
	return repo.getChores();
}

int Service::checkExisting(const string& title)
{
	vector<Chore> chores = this->getAllChoresInRepo();
	for (const auto&chore:chores)
	{
		if (chore.getTitle() == title)
			return 1;
	}
	return 0;
}

int Service::addChore_service(const string& title, const string& type, const string& lastPerformed, const int timesPerformed, const string& vision)
{
	int ok = 0;
	Chore c{ title,type,lastPerformed,timesPerformed,vision };
	try {
		ChoreValidator::validate(c);
	}
	catch (ValidationException & ex)
	{
		ok = 1;
		cout << ex.getMessage() << endl;
	}
	if (this->checkExisting(title) == 0 && ok == 0 )
	{
		this->repo.addChore(c);
		return 1;
	}
	return 0;
}

int Service::updateChore_service(const string& title, const string& type, const string& lastPerformed, const int timesPerformed, const string& vision)
{
	int ok = 0;
	Chore c{ title,type,lastPerformed,timesPerformed,vision };
	try
	{
		ChoreValidator::validate(c);
	}
	catch (ValidationException& ex)
	{
		ok = 1;
		cout << ex.getMessage()<<endl;
	}
	if (this->checkExisting(title) == 1 && ok ==0)
	{
		this->repo.updateChore(c);

		return 1;
	}
	return 0;
}

int Service::deleteChore_service(const string& title)
{

	if (this->checkExisting(title))
	{
		this->repo.deleteChore(title);
		return 1;
	}
	return 0;
		
}

vector<Chore> Service::get_by_type(const std::string& type, int timesPerformed)
{
	vector<Chore> filterChores;
	vector<Chore> chores = this->getAllChoresInRepo();
	for(const auto&c:chores )
	{
		if (c.getType() == type && c.getTimesPerformed() < timesPerformed)
			filterChores.push_back(c);
	}
	if (filterChores.size() == 0)
	{
		throw ServiceException("No chores matching\n");
	}
	return filterChores;
}

void Service::save(std::string title)
{
	int constanta;
	constanta = checkExisting(title);
	if (constanta == 1)
	{
		Chore c = repo.get_by_title(title);
		this->saved_chores->add(c);
	}
	else if (constanta == 0)
		throw ServiceException("The title is inexistent \n");
	
}

vector<Chore> Service::getServantList()
{
	vector<Chore> chores = this->repoServant.getForServant();
	return chores;

}
/*
Chore Service::next_service()
{
	chores = repo.getChores();
	it = chores.begin();
	if (chores.begin() == chores.end())
	{
		cout << "No chores found";
	}
	if (it == chores.end())
	{
		it = chores.begin();
	}
	return *(it++);

}*/

void Service::file_location(string Path)
{
	this->repo.set_file(Path);
}


void Service::set_mylist_location(std::string path)
{
	string extensie = path.substr(path.size() - 4);

	
	if (extensie == ".csv")
	{
		this->saved_chores = new CSVmylist{};
	}
	else if (extensie == "html")
	{
		this->saved_chores = new HTMLmylist{};
	}
	//else throw ServiceException(" invalid path\n");
	this->saved_chores->set_path(path);

}
 
/*
void Service::open_file()
{
	this->saved_chores->open_file();
}

*/
