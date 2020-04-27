#include "Chores.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>

Chore::Chore() : title(""), type(""), lastPerformed(""), timesPerformed(), vision("") {}

Chore::Chore(const std::string& title, const std::string& type, const std::string& lastPerformed, const int timesPerformed, const std::string& vision)
{
	this->title = title;
	this->type = type;
	this->lastPerformed = lastPerformed;
	this->timesPerformed = timesPerformed;
	this->vision = vision; 
}

std::string Chore::getTitle() const
{
	return this->title;
}

std::string Chore::getType() const
{
	return this->type;
}

std::string Chore::getLastPerformed() const
{
	return this->lastPerformed;
}

int Chore::getTimesPerformed() const
{
	return this->timesPerformed;
}

std::string Chore::getVision() const
{
	return this->vision;
}

std::string Chore::toString()
{
	return "Title:"+this->getTitle() + ", Type: " + this->getType() + ", LastPerformed: " + this->getLastPerformed() + ", TimesPerformed: " + std::to_string(this->getTimesPerformed()) + ", Vision: " + this->getVision(); 
}
//std::ostream& operator<<(std::ostream& os, const Chore& c)
//{
	//os << c.title << ' ' << c.type << ' ' << c.lastPerformed << ' ' << c.timesPerformed << ' ' << ' ' << c.vision <<'\n';
	//return os;
//}