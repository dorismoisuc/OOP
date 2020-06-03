#pragma once
#include "Chores.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class FileRepo
{
private: 
	string Path;
	vector<Chore> next_chores;
	vector<Chore>::iterator it;
	int iteratorIndex = 0;
	
	void save_chores(vector<Chore>chores);
public:
	FileRepo();
	void addChore(Chore& c);
	void updateChore(Chore& c);
	void deleteChore(const string& title);
	vector<Chore>getChores();
	void initializeIterator();
	Chore get_by_title(string title);
	Chore next();
	Chore getChore();
	int getPositionChore(const Chore& c);
	void nextC();
	int getRepoSize();
	//Chore nextChore() override;
	void set_file(string& path);
	vector<Chore> load_chores();
	bool isTitle(const Chore c, const std::string& title);
	//void initializeIt() override;
};