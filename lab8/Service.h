#pragma once
#include "Repo.h"
#include "FileRepository.h"

class Service 
{
	private:
		FileRepo repo;
		RepoServant repoServant;
		vector<Chore> chores;
		vector<Chore>::iterator it;

	public:
		//initializes the service by the repository 
		Service(const FileRepo& r) :repo{ r } {}
		
		/*
		returns all the chores in the repository
		*/
		vector<Chore> getAllChoresInRepo();

		/*
		Adds a chore if it doesn't already exist.
			input: title, type, lastPerformed, vision- string
				   timesPerformed- int
			output: 1- if the title doesn't exist and the chore is added
					0- if the title already exists and the chore is not added
		*/
		int addChore_service(const string& title, const string& type, const string& lastPerformed, const int timesPerformed, const string& vision);
		
		/*
		Updates a chore if it is valid.
			input: title, newType, newLastPerformed, newVision- string
				   newTimesPerformed- int
			output: 1- if the title is valid and the chore is updated
					0- if the title is existent and the chore is not updated
		*/
		int updateChore_service(const string& title, const string& type, const string& lastPerformed, const int timesPerformed, const string& vision);
		
		/*
		Delete a chore if it is valid.
			input: title- string
			output: 1- if the title is valid and the chore is deleted
					0- if the title is not valid and the chore is not deleted
		*/
		int deleteChore_service(const string& title);

		/*
	Checks if a title exists in the DynamicVector of chores
		input: title- string
		output: 1- if the title is found in the DynamicVector of chores
				0- if the title is not found in the DynamicVector of chores
	*/
		int checkExisting(const string& title);
	
	
		/*
		returns the chores filtered by type
		*/
		vector<Chore> get_by_type(const string& type, int timesPerformed);

		/*
		Saves a chore by title
		*/
		void save(string title);

		/*
		Returns the list for the servant
		*/
		vector<Chore> getServantList();

		/*
		returns the next chore
		*/
		//Chore next_service();

		void file_location(string Path);
};