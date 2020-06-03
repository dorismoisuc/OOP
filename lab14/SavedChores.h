#pragma once
#include "Chores.h"

#include <vector> 

class SavedChores
{
	protected: 
		std::string path;
	public:
		void add(const Chore& c);

		std::vector<Chore> get_all();

		void set_path(std::string path);

		virtual void save_file(std::vector<Chore> chores) {};

		virtual std::vector<Chore> load_file() { return std::vector<Chore>(); };

		virtual void open_file() {  };

};

class CSVmylist : public SavedChores
{
	public:
		void save_file(std::vector<Chore> chores)override;
		std::vector<Chore> load_file() override;
		//void open_file() override;
};

class HTMLmylist : public SavedChores
{
	public:
		void save_file(std::vector<Chore> chores)override;
		std::vector<Chore> load_file() override;
		//void open_file() override;
};

class TXTmylist : public SavedChores
{
public:
	void save_file(std::vector<Chore> chores)override;
	std::vector<Chore> load_file() override;

};