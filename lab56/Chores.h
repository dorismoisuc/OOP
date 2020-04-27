#pragma once
#include <iostream>
#include<string>

class Chore
{
private:
	std::string title;
	std::string type;
	std::string lastPerformed;
	int timesPerformed;
	std::string vision;

public:
	//default constructor for a chore
	Chore();

	//constructor with parameters
	Chore(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision);

	std::string getTitle() const;
	std::string getType() const;
	std::string getLastPerformed() const;
	int getTimesPerformed() const;
	std::string getVision() const;

	//friend std::ostream& operator<<(std::ostream& os, const Chore& c);
	//returns a string with the Chore's data
	std::string toString();

};