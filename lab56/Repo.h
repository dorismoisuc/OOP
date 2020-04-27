#pragma once
#include "Chores.h"
#include"DynamicVector.h"

class Repository 
{
	private:

		DynamicVector<Chore> chores;
		DynamicVector<Chore>::iterator it;


	public:

		//initializes an object of type repository
		Repository()
		{
		}

		/*
		Adds a chore to the repository
			input: c - chore
			output: the chore is added to the repository
		*/
		void addChore(Chore c);

		/*
		Updates a chore from the repository
			input: c - new chore
			output: the chore updated
		*/
		void updateChore(Chore c);

		/*
		Deletes a chore from the repository by the title
			input: title - string
			output: the deleted chore
		*/
		void deleteChore(const std::string& title);

		//returns the DynamicVector containing the chores
		DynamicVector<Chore> getChores();

		// verifies if a given title is a title in the Dynamic Vector
		bool isTitle(const Chore c,const std::string&title);

		// returns the size 
		int getSize(DynamicVector<Chore> repo);

		// returns a chore by its name
		Chore get_by_title(std::string title);

		// returns the next chore
		Chore next();
};

class RepoServant
{
	private:
		DynamicVector<Chore> choresServant;
	public:
		RepoServant();
		void addChoreS(Chore c);
		DynamicVector<Chore> getForServant();

};

