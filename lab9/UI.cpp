#include"UI.h"
#include <iostream>
#include<string>

using namespace std;

void UI::menu()
{
	cout << endl;
	cout << "------------------------------MODE A------------------------------"<<endl<<endl;
	cout << "Add: eg. add cleanup, merchant room clean spill, 01-13-1248, 5, sparkling room" << endl;
	cout << "Update: eg. update cleanup, merchant room bring bathwater, 01-14-1248, 14, bathing patron" << endl;
	cout << "Delete: eg. delete cleanup"<<endl;
	cout << "List: eg. list"<<endl;
	cout << "Exit: exit"<<endl;
	cout << endl; 

}

void UI::servant_menu()
{
	cout << endl; 
	cout << "------------------------------MODE B------------------------------"<<endl<<endl;
	cout << "Next: to see the chores one by one." << endl;
	cout << "Save 'title': to save a chore" << endl;
	cout << "List with 2 parameters: eg. list merchant room clean spill, 5" << endl;
	cout << "Mylist: eg. mylist" << endl;
	cout << "Exit: exit" << endl;
	cout << endl; 
}

void UI::modes()
{
	cout << "----------------------------START MENU----------------------------"<<endl<<endl;
	cout << "!!!!! You must provide the fileLocation and mylistLocation !!!!!"<<'\n'<<endl;
	cout << "In order to modify something, you must use admin mode"<<endl;
	cout << "To be able to save the chores only in your list and visualize them, you must use servant mode" << endl;
	cout << "The administrator mode is: mode A"<<endl;
	cout << "The servant mode is: mode B" << endl;
	cout << "The way to enter the file location: fileLocation <PATH>"<<endl;
	cout << "The way to enter the mylist location: mylistLocation <PATH>" << endl;
	cout << "You can also exit: exit" << endl;
	cout << endl;
}

void UI::addChore_ui()
{
	string title, type, lastPerformed,vision;
	int timesPerformed;
	char separator = ',';
	//std::getline(std::cin, title, separator);
	//std::getline(std::cin, type, separator);
	//std::getline(std::cin, lastPerformed, separator);
	//std::getline(std::cin, timesPerformed, separator);
	//std::getline(std::cin, vision);
	std::string titleWithoutSpace;
	string line;
	Chore c;
	getline(cin, line);
	vector<string>tokens = c.tokenize(line, ',');
	if (tokens.size() != 5)
		cout << "No! The nr of params is incorrect.\n";
	else {
		title = tokens.at(0);
		title.erase(title.begin() + 0);
		type = tokens.at(1);
		lastPerformed = tokens.at(2);
		timesPerformed = stoi(tokens.at(3));
		vision = tokens.at(4);
		if (!this->service.addChore_service(title, type, lastPerformed, timesPerformed, vision))
			cout << "No!";
	}
}
void UI::updateChore_ui()
{
	string title, type, lastPerformed, vision;
	int timesPerformed;
	char separator = ',';
	//std::getline(std::cin, title, separator);
	//std::getline(std::cin, type, separator);
	//std::getline(std::cin, lastPerformed, separator);
	//std::getline(std::cin, timesPerformed, separator);
	//std::getline(std::cin, vision);
	//std::string titleWithoutSpace;

	//for (int i = 1; i < title.length(); i++)
		//titleWithoutSpace += title[i];
	string line;
	Chore c;
	getline(cin, line);
	vector<string>tokens = c.tokenize(line, ',');
	if (tokens.size() != 5)
		cout << "No! The nr of params is incorrect.\n";
	else
	{
		title = tokens.at(0);
		title.erase(title.begin() + 0);
		type = tokens.at(1);
		lastPerformed = tokens.at(2);
		timesPerformed = stoi(tokens.at(3));
		vision = tokens.at(4);
		if (!this->service.updateChore_service(title, type, lastPerformed, timesPerformed, vision))
			cout << "No!\n";
	}
}

void UI::deleteChore_ui()
{
	std::string title;
	getline(cin, title);
	if (title == "")
		cout << "Please enter a valid title";
	else {
		title.erase(title.begin() + 0);

		if (!this->service.deleteChore_service(title))
			cout << "No! Invalid chore\n";

	}
}
int UI::get_mode()
{
	std::string mode;
	std::getline(std::cin, mode);
	if (mode[1] == 'A')
		return 0;
	else if (mode[1] == 'B')
		return 1;

}

void UI::listChores_ui()
{
	vector<Chore> chores = this->service.getAllChoresInRepo();
	for (int i = 0; i < chores.size(); i++)
	{
		Chore c = chores.at(i);
		cout << c.toString() << endl;
	}
}

void UI::list_by_type_ui()
{
	string type,more;
	int timesPerformed;
	char separator1 = ' ,';
	Chore c;
	getline(cin, more);
	if (more != "")
	{
		vector<string>tokens = c.tokenize(more, ',');
		type = tokens.at(0);
		timesPerformed = stoi(tokens.at(1));
		type.erase(type.begin() + 0);
		vector<Chore>chores = this->service.get_by_type(type, timesPerformed);
		for (int i = 0; i < chores.size(); i++)
		{
			Chore c2 = chores.at(i);
			cout << c2.toString() << endl;
		}
	}
	//for (int i = 1; i < type.length(); i++)
		//typeWithoutTheSpace += type[i];

	//vector<Chore> chores = service.get_by_type(typeWithoutTheSpace,tP);
	//for (int i = 0; i < chores.size(); ++i)
//	{
	//	Chore c = chores.at(i);
		//cout << c.toString() << endl;
	//}


}

void UI::next_ui(vector<Chore>&chores,vector<Chore>::iterator&it)
{
	if (chores.begin() == chores.end())
		cout << "No chores found";
	if (it != chores.end())
	{
		++it;
		if (it == chores.end())
			it = chores.begin();
		cout << (*it).toString() << "\n";
	}
}

void UI::file_location()
{
	string Path;
	getline(cin, Path);
	Path.erase(Path.begin() + 0);
	this->service.file_location(Path);
}

void UI::mylist_location()
{
	string Path;
	getline(cin, Path);
	Path.erase(Path.begin() + 0);
	this->service.set_mylist_location(Path);
}

void UI::save()
{
	string title;
	getline(cin, title);
	//std::string titleWithoutSpace;
	title.erase(title.begin() + 0);
	//for (int i = 1; i < title.length(); i++)
		//titleWithoutSpace += title[i];

	service.save(title);

}

void UI::my_list()
{
	vector<Chore> chores = service.getServantList();
	for (int i = 0; i < chores.size(); ++i)
	{
		Chore c = chores.at(i);
		cout << c.toString() << endl;

	}
}

void UI::admin_mode()
{
	int ok = 0;
	UI::menu();
	while (true)
	{
		std::string command;
		cout << ">";
		cin >> command;
		try {
			if (command == "add")
				addChore_ui();
			else if (command == "update")
				updateChore_ui();
			else if (command == "delete")
				deleteChore_ui();
			else if (command == "list")
				listChores_ui();
			else if (command == "fileLocation")
				file_location();
			else if (command == "mode")
			{
				ok = get_mode();
				if (ok == 1)
				{
					servant_mode();
				}
				else if (ok == 0)
				{
					admin_mode();
				}
				else if (ok != 0 && ok != 1)
				{
					cout << "Inexistent mode" << endl;
				}
			}
			else if (command == "exit")
				exit(0);
			else
				cout << "Inexistent command\n";
		}
		catch (Exceptions & exception)
		{
			cout << exception.get_message();
		}
		catch (exception & error)
		{
			cout << "Unknown error: \n" << error.what() << endl;
		}

	}

}


void UI::servant_mode()
{
	int ok = 0;
	UI::servant_menu();
	
	vector<Chore>chores = this->service.getAllChoresInRepo();
	vector<Chore>::iterator it = chores.begin();

	while (true)
	{

		
		std::string servComm;
		cout << "-";
		cin >> servComm;
		try {
			if (servComm == "list")
				list_by_type_ui();

			else if (servComm == "next")
				next_ui(chores, it);

			else if (servComm == "save")
				save();

			else if (servComm == "mylist")
				my_list();

			else if (servComm == "fileLocation")
			{
				file_location();
			}

			else if (servComm == "mode")
			{
				ok = get_mode();
				if (ok == 0)
				{
					admin_mode();
				}
				else if (ok == 1)
				{
					servant_mode();
				}
				else if (ok != 0 && ok != 1)
				{
					cout << "Inexistent mode" << endl;
				}
			}
			else if (servComm == "exit")
				exit(0);
			else
			{
				cout << "Inexistent command\n";
			}
		}
		catch (Exceptions & exception)
		{
			cout << exception.get_message();
		}
		catch (exception & error)
		{
			cout << "Unknown error:\n" << error.what();
		}
	}
}

void UI::run()
{
	/*this->service.addChore_service("Cleanup", "Merchant room", "01-01-1999", 5, "Sparkling water");
	this->service.addChore_service("Tea", "Kitchen", "01-02-1999", 1, "Hot water");
	this->service.addChore_service("Dusting", "Living room", "01-01-1248", 5, "Anti-dust spray");
	this->service.addChore_service("Vacuuming", "All the castle", "02-04-2019", 1, "Vacuum cleaner");
	this->service.addChore_service("Food", "Kitchen", "01-01-1990", 2, "Kitchen supplies");
	*/
	/*
	string Path;
	cout << "fileLocation:";
	getline(cin, Path);
	this->service.file_location(Path);
	cout << endl; 
	*/

	UI::modes();
	while (true)
	{
		string mode;
		cout << "\n     Make sure you add the FILES before entering a mode   \n";
		cout << " \n                        Example: * fileLocation (name).txt\n";
		cout << "\n                                   * mylistLocation (name).csv or .html \n";
		cout << "\n\nEnter: ";
		getline(cin, mode);

		if (mode == "mode A")
		{
			admin_mode();
		}

		else if (mode == "mode B")
		{
			servant_mode();
		}
		else if (mode.find("fileLocation") == 0)
		{
			string auxMode;
			for (int j = 13; j < mode.size(); j++)
				auxMode += mode[j];
			this->service.file_location(auxMode);
		}
		else if (mode.find("mylistLocation") == 0)
		{
			string auxMode;
			
			for (int j = 15; j < mode.size(); j++)
				auxMode += mode[j];

			this->service.set_mylist_location(auxMode);

		}
		else if (mode == "exit")
		{
			exit(0);
		}
		else
		{
			cout << "Inexistent mode!\n";
		}

	}
}


