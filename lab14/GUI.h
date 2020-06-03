#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>


class GUI :
	public QWidget
{
private: 
	Service& serv;

	// graphical elements 
	QListWidget* choresListWidget;
	QLineEdit* titleLineEdit; 
	QLineEdit* typeLineEdit;
	QLineEdit* lastPerformedLineEdit;
	QLineEdit* timesPerformedLineEdit;
	QLineEdit* visionLineEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QListWidget* savedChoresListWidget;


public:
	GUI(Service& s);

private:
	void initGUI();
	
	void populateChores();
	
	void connectSignalsandSlots();
	
	int getSelectedIndex() const;
	
	void addChore();

	void deleteChore();

	void updateChore();

	void guiUndo();

	void guiRedo();

};

