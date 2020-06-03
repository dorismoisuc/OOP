#include "FileChore.h"

FileChore::FileChore() : Chore{}, filename{ "" }
{

}

void FileChore::setFileName(const std::string& filename)
{
	this->filename = filename;
}