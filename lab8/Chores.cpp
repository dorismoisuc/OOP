#include "Chores.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>

Chore::Chore() : title(""), type(""), lastPerformed(""), timesPerformed(), vision("") {}

Chore::Chore(const string& title, const string& type, const string& lastPerformed, const int timesPerformed, const string& vision)
{
	this->title = title;
	this->type = type;
	this->lastPerformed = lastPerformed;
	this->timesPerformed = timesPerformed;
	this->vision = vision; 
}

string Chore::getTitle() const
{
	return this->title;
}

string Chore::getType() const
{
	return this->type;
}

string Chore::getLastPerformed() const
{
	return this->lastPerformed;
}

int Chore::getTimesPerformed() const
{
	return this->timesPerformed;
}

string Chore::getVision() const
{
	return this->vision;
}

string Chore::toString()
{
	return "Title:"+this->getTitle() + ", Type: " + this->getType() + ", LastPerformed: " + this->getLastPerformed() + ", TimesPerformed: " + std::to_string(this->getTimesPerformed()) + ", Vision: " + this->getVision(); 
}
//std::ostream& operator<<(std::ostream& os, const Chore& c)
//{
	//os << c.title << ' ' << c.type << ' ' << c.lastPerformed << ' ' << c.timesPerformed << ' ' << ' ' << c.vision <<'\n';
	//return os;
//}

void Chore::reset_chore()
{
	this->title = "";
	this->type = "";
	this->lastPerformed = "";
	this->timesPerformed = 0;
	this->vision = "";
}

void Chore::setTitle(string title)
{
	this->title = title;
}

void Chore::setType(string type)
{
	this->type = type;
}

void Chore::setLastPerformed(string lastPerformed)
{
	this->lastPerformed = lastPerformed;
}

void Chore::setTimesPerformed(int timesPerformed)
{
	this->timesPerformed = timesPerformed;
}

void Chore::setVision(string vision)
{
	this->vision = vision;
}

vector<string> Chore::tokenize(const string& str, char separator)
{
	vector<string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, separator))
		result.push_back(token);
	return result;
}

bool operator ==(const Chore& c1, const Chore& c2)
{
	return
	{
		c1.getTitle() == c2.getTitle() &&
		c1.getType() == c2.getType() &&
		c2.getLastPerformed() == c2.getLastPerformed()&&
		c1.getTimesPerformed() == c2.getTimesPerformed()&&
		c1.getVision() == c2.getVision()
	};
}

ostream& operator<<(ostream& os, const Chore& c)
{
	os << c.getTitle() << "," << c.getType() << "," << c.getLastPerformed() << "," << c.getTimesPerformed() << "," << c.getVision() << endl;
	return os;
}

istream& operator>>(istream& is, Chore& c)
{
	c.reset_chore();
	string line;
	getline(is, line);
	vector<string> tokens = c.tokenize(line, ',');
	if (tokens.size() != 5)
		return is;
	c.setTitle(tokens.at(0));
	c.setType(tokens.at(1));
	c.setLastPerformed(tokens.at(2));
	c.setTimesPerformed(stoi(tokens.at(3)));
	c.setVision(tokens.at(4));
	return is;
}