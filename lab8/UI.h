#pragma once
#include "Service.h"
#include "Validator.h"

class UI
{
	private:
		Service service;
	public:
		UI(const Service& s) : service(s) {}
		static void servant_menu();
		void run();
	
	private:
		
		static void menu();
		static void modes();
		
		void addChore_ui();
		void listChores_ui();
		void updateChore_ui();
		void deleteChore_ui();
		int get_mode();

		void admin_mode();
		void servant_mode();

		void list_by_type_ui();
		void save();
		void my_list();
		void next_ui(vector<Chore>& chores, vector<Chore>::iterator& it);


		void file_location();


};