#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11GUI.h"
#include "Chores.h"
#include "Service.h"
#include "Repo.h"
#include "savedWidget.h"

class lab11GUI : public QMainWindow
{
	Q_OBJECT

public:
	lab11GUI(Service &s, savedTabelModel* model, QWidget *parent = Q_NULLPTR);
	 

private:
	int modeChange=0; 
	savedTabelModel* model;
	savedWidget savedC{ model };

	Service& serv;
	Ui::lab11GUIClass ui;

	void changeMode();

	void populateList();

	void help();

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

	void undoGUI();

	void saved();

	void redoGUI();
};
