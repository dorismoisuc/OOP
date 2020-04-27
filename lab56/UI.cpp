#include"UI.h"
#include <iostream>
#include<string>

using namespace std;

void UI::menu()
{

	cout << "Add: eg. add cleanup, merchant room clean spill, 01-13-1248, 5, sparkling room" << endl;
	cout << "Update: eg. update cleanup, merchant room bring bathwater, 01-14-1248, 14, bathing patron" << endl;
	cout << "Delete: eg. delete cleanup"<<endl;
	cout << "List: eg. list"<<endl;
	cout << "Exit: exit"<<endl;

}

void UI::servant_menu()
{
	cout << "Next: to see the chores one by one." << endl;
	cout << "Save 'title': to save a chore" << endl;
	cout << "List with 2 parameters: eg. list merchant room clean spill, 5" << endl;
	cout << "Mylist: eg. mylist" << endl;
	cout <<"Exit: exit"<<endl;
}

void UI::modes()
{
	cout << "In order to modify something, you must use admin mode"<<endl;
	cout << "To be able to save the chores only in your list and visualize them, you must use servant mode" << endl;
	cout << "The administrator mode is: mode A"<<endl;
	cout << "The servant mode is: mode B" << endl;
}

void UI::addChore_ui()
{
	std::string title, type, lastPerformed, timesPerformed, vision;
	char separator = ',';
	std::getline(std::cin, title, separator);
	std::getline(std::cin, type, separator);
	std::getline(std::cin, lastPerformed, separator);
	std::getline(std::cin, timesPerformed, separator);
	std::getline(std::cin, vision);
	std::string titleWithoutSpace;

	for (int i = 1; i < title.length(); i++)
		titleWithoutSpace += title[i];

	if (!this->service.addChore_service(titleWithoutSpace, type, lastPerformed,std::stoi(timesPerformed), vision))
		cout << "No!\n";

}
void UI::updateChore_ui()
{
	std::string title, type, lastPerformed, timesPerformed, vision;
	char separator = ',';
	std::getline(std::cin, title, separator);
	std::getline(std::cin, type, separator);
	std::getline(std::cin, lastPerformed, separator);
	std::getline(std::cin, timesPerformed, separator);
	std::getline(std::cin, vision);
	std::string titleWithoutSpace;

	for (int i = 1; i < title.length(); i++)
		titleWithoutSpace += title[i];

	if (!this->service.updateChore_service(titleWithoutSpace, type, lastPerformed, std::stoi(timesPerformed), vision))
		cout << "No!\n";

}

void UI::deleteChore_ui()
{
	std::string title;
	std::getline(std::cin, title);
	std::string titleWithoutSpace;

	for (int i = 1; i < title.length(); i++)
		titleWithoutSpace += title[i];
	
	if (!this->service.deleteChore_service(titleWithoutSpace))
		cout << "No!\n";
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
	DynamicVector<Chore> chores = this->service.getAllChoresInRepo();
	for (int i = 0; i < chores.getSize(); i++)
	{
		Chore c = chores.get(i);
		cout << c.toString() << endl;
	}
}

void UI::list_by_type_ui()
{
	std::string type, timesPerformed;
	char separator1 = ' ,';
	std::getline(std::cin, type, separator1);
	std::getline(std::cin, timesPerformed);
	int tP = std::stoi(timesPerformed);
	std::string typeWithoutTheSpace;

	for (int i = 1; i < type.length(); i++)
		typeWithoutTheSpace += type[i];

	DynamicVector<Chore> chores = service.get_by_type(typeWithoutTheSpace,tP);
	for (int i = 0; i < chores.getSize(); ++i)
	{
		Chore c = chores.get(i);
		cout << c.toString() << endl;
	}


}

void UI::next_ui()
{
	Chore c = service.next_service();
	cout << c.toString() << endl;
}

void UI::save()
{
	std::string title;
	std::getline(std::cin, title);
	std::string titleWithoutSpace;

	for (int i = 1; i < title.length(); i++)
		titleWithoutSpace += title[i];

	service.save(titleWithoutSpace);

}

void UI::my_list()
{
	DynamicVector<Chore> chores = service.getServantList();
	for (int i = 0; i < chores.getSize(); ++i)
	{
		Chore c = chores.get(i);
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
		if (command == "add")
			addChore_ui();
		else if (command == "update")
			updateChore_ui();
		else if (command == "delete")
			deleteChore_ui();
		else if (command == "list")
			listChores_ui();
		
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
		}
		else if (command == "exit")
			exit(0);
		else cout << "Inexistent command\n";

	}

}


void UI::servant_mode()
{
	int ok = 0;
	UI::servant_menu();
	while (true)
	{
		std::string servComm;
		cout << "-";
		cin >> servComm;
		
		if (servComm == "list")
			list_by_type_ui();

		else if (servComm == "next")
			next_ui();

		else if (servComm == "save")
			save();

		else if (servComm == "mylist")
			my_list();

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
			}
		else if (servComm == "exit")
			exit(0);
		else
		{
			cout << "Inexistent command\n";
		}
	}
}

void UI::run()
{
	//this->service.addChore_service("Cleanup", "Merchant room", "01-01-1999", 5, "Sparkling water");
	//this->service.addChore_service("Tea", "Kitchen", "01-02-1999", 1, "Hot water");
	//this->service.addChore_service("Dusting", "Living room", "01-01-1248", 5, "Anti-dust spray");
	//this->service.addChore_service("Vacuuming", "All the castle", "02-04-2019", 1, "Vacuum cleaner");
	//this->service.addChore_service("Food", "Kitchen", "01-01-1990", 2, "Kitchen supplies");

	UI::modes();
	while (true)
	{
		string mode;
		cout << "The mode you choose is: ";
		getline(cin, mode);

		if (mode == "mode A")
		{
			admin_mode();
		}

		else if (mode == "mode B")
		{
			servant_mode();
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


