#pragma once
#include <iostream>
#include<string>
#include <fstream>
#include <vector>
#include<sstream>

using namespace std;


class Chore
{
private:
	string title;
	string type;
	string lastPerformed;
	int timesPerformed;
	string vision;

public:
	//default constructor for a chore
	Chore();

	//constructor with parameters
	Chore(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision);

	string getTitle() const;
	string getType() const;
	string getLastPerformed() const;
	int getTimesPerformed() const;
	string getVision() const;

	//friend std::ostream& operator<<(std::ostream& os, const Chore& c);
	//returns a string with the Chore's data
	string toString();
	void reset_chore();
	vector<string>tokenize(const string& str, char separator);
	void setTitle(string title);
	void setType(string type);
	void setLastPerformed(string lastPerformed);
	void setTimesPerformed(int timesPerformed);
	void setVision(string vision);

	friend bool operator==(const Chore&, const Chore&);

	friend istream& operator>>(istream& is, Chore& c);
	friend ostream& operator<<(ostream& os, const Chore& c);

};