#pragma once
#include "Chores.h"

class FileChore : public Chore
{
protected:
	std::string filename;
public:
	FileChore();
	virtual ~FileChore() {}
	void setFileName(const std::string& filename);
	virtual void writeToFile() = 0;
	virtual void displayPlaylist() const = 0;

};