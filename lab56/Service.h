#pragma once
#include "Repo.h"

class Service 
{
	private:
		Repository repo;
		RepoServant repoServant;
	public:
		//initializes the service by the repository 
		Service(Repository& r) :repo{ r } {}

		//returns the repository 
		Repository getRepo() const { return repo; }
		
		/*
		returns all the chores in the repository
		*/
		DynamicVector<Chore> getAllChoresInRepo();

		/*
		Adds a chore if it doesn't already exist.
			input: title, type, lastPerformed, vision- string
				   timesPerformed- int
			output: 1- if the title doesn't exist and the chore is added
					0- if the title already exists and the chore is not added
		*/
		int addChore_service(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision);
		
		/*
		Updates a chore if it is valid.
			input: title, newType, newLastPerformed, newVision- string
				   newTimesPerformed- int
			output: 1- if the title is valid and the chore is updated
					0- if the title is existent and the chore is not updated
		*/
		int updateChore_service(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision);
		
		/*
		Delete a chore if it is valid.
			input: title- string
			output: 1- if the title is valid and the chore is deleted
					0- if the title is not valid and the chore is not deleted
		*/
		int deleteChore_service(const std::string& title);

		/*
	Checks if a title exists in the DynamicVector of chores
		input: title- string
		output: 1- if the title is found in the DynamicVector of chores
				0- if the title is not found in the DynamicVector of chores
	*/
		int checkExisting(const std::string& title);
	
	
		/*
		returns the chores filtered by type
		*/
		DynamicVector<Chore> get_by_type(const std::string& type, int timesPerformed);

		/*
		Saves a chore by title
		*/
		void save(std::string title);

		/*
		Returns the list for the servant
		*/
		DynamicVector<Chore> getServantList();

		/*
		returns the next chore
		*/
		Chore next_service();


};