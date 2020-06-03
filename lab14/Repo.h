#pragma once
#include "Chores.h"

#include <vector>
#include <iostream>
using namespace std;

class Repository 
{
	private:

		vector<Chore> chores;
		std::string filename;
		//vector<Chore>::iterator it;


	public:

		//initializes an object of type repository
		Repository();

		/*
		Adds a chore to the repository
			input: c - chore
			output: the chore is added to the repository
		*/
		void addChore(Chore& c);

		/*
		Updates a chore from the repository
			input: c - new chore
			output: the chore updated
		*/
		void updateChore(Chore& c);

		/*
		Deletes a chore from the repository by the title
			input: title - string
			output: the deleted chore
		*/
		void deleteChore(const string& title);

		//returns the DynamicVector containing the chores
		vector<Chore> getChores();

		bool isTitle(const Chore c,const std::string&title);

		int getSize(vector<Chore> repo);

		Chore get_by_title(std::string title);

		Chore get_by_type(std::string type);
		Chore next();

		//virtual Chore nextChore() = 0;
		//virtual void initializeIt() = 0;
		void initializeIterator();
private:
	void readFromFile();
	void writeToFile();
};



class RepoServant
{
	private:
		vector<Chore> choresServant;
	public:
		RepoServant();
		void addChoreS(Chore& c);
		vector<Chore> getForServant();

};

