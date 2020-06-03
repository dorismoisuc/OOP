#include "SavedChores.h"
#include <string>
#include <fstream>

#include <Windows.h>

using namespace std;

void SavedChores::add(const Chore& c)
{
		cout <<endl<< "CHORE SUCCESSFULLY SAVED"<<endl<<endl<<endl;
		vector<Chore> savedChores = this->load_file();
		savedChores.push_back(c);
		this->save_file(savedChores);
}

vector<Chore> SavedChores::get_all()
{
	vector<Chore> savedChores = this->load_file();
	return savedChores;
}

void SavedChores::set_path(std::string path)
{
	this->path = path;
}

std::vector<Chore> CSVmylist::load_file()
{
	std::vector<Chore> chores;
	Chore c;
	ifstream file{ this->path };
	while (file >> c)
		chores.push_back(c);
	file.close();
	return chores;
}

//void CSVmylist::open_file()
//{
	//ShellExecuteA(NULL, NULL, "notepad.exe", this->path.c_str(), NULL, SW_SHOWNORMAL);

//}

void CSVmylist::save_file(std::vector<Chore> chores)
{
	ofstream file{ this->path };
	for (const auto& chore : chores)
		file << chore << endl;
	file.close();
}

void HTMLmylist::save_file(std::vector<Chore> chores)
{
	ofstream file{ this->path };
	file << "<!DOCTYPE html>\n<html>\n<head>\n";
	file << "<title>SAVED CHORES</title>\n";
	file << "</head>\n<body style=\"background-color:#0099ff;\">\n<table border=\"1\"\n";
	
	file << "<tr>\n<td><b>Title</td></b>\n<td><b>Type</td></b>\n<td><b>LastPerformed</td></b>\n<td><b>TimesPerformed</td></b>\n<td><b>Vision</td></b>\n</tr>\n";
	
	for (auto chore : chores)
		file << chore.toHTML() << endl;

	file << "</table>\n</body>\n</html>";
	file.close();
}

std::vector<Chore> HTMLmylist::load_file()
{
	std::vector<Chore> savedChores;
	string line;
	ifstream file{ this->path };
	string title, type, lastPerformed, timesPerformed, vision;

	for (int i = 0; i <= 13; i++)
		getline(file, line);

	getline(file, line); //<tr>
	while (line == "<tr>")
	{
		getline(file, line);
		title = line.substr(4, line.size() - 9);
		getline(file, line);
		type = line.substr(4, line.size() - 9);
		getline(file, line);
		lastPerformed = line.substr(4, line.size() - 9);
		getline(file, line);
		timesPerformed = line.substr(4, line.size() - 9);
		getline(file, line);
		vision = line.substr(4, line.size() - 9);
	
		Chore c{ title,type,lastPerformed,stoi(timesPerformed),vision };
		savedChores.push_back(c);

		getline(file, line); //</tr>
		getline(file, line); //<tr>
	}
	file.close();
	return savedChores;
}


//void HTMLmylist::open_file()
//{
//	//
//}
