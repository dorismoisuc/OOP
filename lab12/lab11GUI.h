#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11GUI.h"
#include "Chores.h"
#include "Service.h"
#include "Repo.h"

class lab11GUI : public QMainWindow
{
	Q_OBJECT

public:
	lab11GUI(Service &s, QWidget *parent = Q_NULLPTR);

private:
	Service& serv;
	Ui::lab11GUIClass ui;

	void populateList();

	int getSelectedIndex() const;

	void deleteChore();

	void connectSignalsAndSlots();

	void addChore();

	void updateChore();

	void populateSaved();

	void saveByTitle();

	void filterByType();
	
	int getSelectedIndexS() const; 

	void connectSignalsAndSlotsS();

	int getSelectedIndexF() const;

	void nextC_gui();
	//void populateFiltered();
};
