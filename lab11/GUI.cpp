#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include "Chores.h"
#include <vector>
#include <qmessagebox.h>
#include <qicon.h>
#include <qmainwindow.h>
#include <qpalette.h>
#include <qstring>
#include <qlabel.h>
#include <qimage.h>
#include <qpixmap.h>
using namespace std;

GUI::GUI(Service& s) :serv{ s }
{
	this->initGUI();
	this->populateChores();
	this->connectSignalsandSlots();
}

void GUI::initGUI()
{
	this->choresListWidget = new QListWidget{};
	this->titleLineEdit = new QLineEdit{};
	this->typeLineEdit = new QLineEdit{};
	this->lastPerformedLineEdit = new QLineEdit{};
	this->timesPerformedLineEdit = new QLineEdit{};
	this->visionLineEdit = new QLineEdit{};
	this->addButton = new QPushButton{"add chore"};
	this->deleteButton = new QPushButton{"delete chore"};
	this->updateButton = new QPushButton{"update chore"};
	
	

	//QPalette pal = addButton->palette();
	//pal.setColor(QPalette::Button, QColor(0,102,255));
	//addButton->setAutoFillBackground(true);
	addButton->setStyleSheet("background-color:#ffe0ac;");
	QFont serifFont("Times", 16,QFont::Bold);
	addButton->setFont(serifFont);

	//QPalette pal2 = updateButton->palette();
	//pal2.setColor(QPalette::Button, QColor(0,255,0));
	//updateButton->setAutoFillBackground(true);
	//updateButton->setPalette(pal2);
	updateButton->setStyleSheet("background-color:#6886c5;");
	updateButton->setFont(serifFont);
	//QPalette pal3 = deleteButton->palette();
	//pal3.setColor(QPalette::Button, QColor(204,51,153));
	//deleteButton->setAutoFillBackground(true);
	//deleteButton->setPalette(pal3);
	deleteButton->setStyleSheet("background-color:#ffacb7;");
	deleteButton->setFont(serifFont);
	QLabel* label = new QLabel{ "CHORE LIST" };
	QLabel* infoLabel = new QLabel{ "When you press on a chore, you'll see the details :) " };
	infoLabel->setAlignment(Qt::AlignCenter);

	QFont labelFont("Times", 12, QFont::Bold);

	labelFont.setItalic(true);

	label->setAlignment(Qt::AlignCenter);

	label->setFont(serifFont);
	
	infoLabel->setFont(labelFont);
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	mainLayout->addWidget(label);
	mainLayout->addWidget(infoLabel);

	mainLayout->addWidget(this->choresListWidget);
	
	QFormLayout* choresDetails = new QFormLayout{ this };

	QLabel* label2 = new QLabel{ "CHORE DETAILS" };
	
	label2->setAlignment(Qt::AlignCenter);
	QFont anotherType("Times", 14, QFont::Bold);

	anotherType.setItalic(true);

	label2->setFont(anotherType);

	mainLayout->addWidget(label2);

	choresDetails->addRow("Title", this->titleLineEdit);
	choresDetails->addRow("Type", this->typeLineEdit);
	choresDetails->addRow("Last Performed", this->lastPerformedLineEdit);
	choresDetails->addRow("Times Performed", this->timesPerformedLineEdit);
	choresDetails->addRow("Vision", this->visionLineEdit);
	
	mainLayout->addLayout(choresDetails);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);

	mainLayout->addLayout(buttonsLayout);

	QGridLayout* buttonsLayout2 = new QGridLayout{};
	
	buttonsLayout2->addWidget(this->updateButton, 0, 0);
	buttonsLayout2->setAlignment(Qt::AlignCenter);

	mainLayout->addLayout(buttonsLayout2);

}

void GUI::populateChores()
{
	this->choresListWidget->setStyleSheet("background-color:#f1d1d1;");
	QFont serifFont("Times", 14);

	this->choresListWidget->setFont(serifFont);

	this->choresListWidget->clear();

	vector<Chore> chores = this->serv.getAllChoresInRepo();
	for (Chore& c : chores)
		this->choresListWidget->addItem(QString::fromStdString(c.getTitle() + " - " + c.getType()));

}

void GUI::connectSignalsandSlots()
{
	QObject::connect(this->choresListWidget, &QListWidget::itemSelectionChanged, [this]() {
		
		int selectedIndex = this->getSelectedIndex();

		if (selectedIndex < 0)
			return;
		Chore c = this->serv.getAllChoresInRepo()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(c.getTitle()));
		this->typeLineEdit->setText(QString::fromStdString(c.getType()));
		this->lastPerformedLineEdit->setText(QString::fromStdString(c.getLastPerformed()));
		this->timesPerformedLineEdit->setText(QString::fromStdString(to_string(c.getTimesPerformed())));
		this->visionLineEdit->setText(QString::fromStdString(c.getVision()));

	});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addChore);

	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteChore);

	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateChore);

}

int GUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->choresListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->titleLineEdit->clear();
		this->typeLineEdit->clear();
		this->lastPerformedLineEdit->clear();
		this->timesPerformedLineEdit->clear();
		this->visionLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;


}

void GUI::addChore()
{
	string title = this->titleLineEdit->text().toStdString();
	string type = this->typeLineEdit->text().toStdString();
	string lastPerformed = this->lastPerformedLineEdit->text().toStdString();
	string timesPerformed = this->timesPerformedLineEdit->text().toStdString();
	string vision = this->visionLineEdit->text().toStdString();
	QMessageBox mb("Duplicate!",
		"The chore is already here.\n\nTry again",
		QMessageBox::NoIcon,
		QMessageBox::Ok | QMessageBox::Default,
		QMessageBox::NoButton,
		QMessageBox::NoButton);

	QPixmap exportDuplicate("duplicate.png");
	mb.setIconPixmap(exportDuplicate);

	if (serv.checkExisting(title) == 1)
	{
		mb.exec();
	}
	else if (title.size() == 0)
	{
		QMessageBox::information(this, "No title!", "Please enter a valid title");
	}
	else {
		this->serv.addChore_service(title, type, lastPerformed, stoi(timesPerformed), vision);

		QMessageBox::information(this, "Added!", "The chore was added");

		this->populateChores();

		int lastElement = this->serv.getAllChoresInRepo().size() - 1;

		this->choresListWidget->setCurrentRow(lastElement);
	}
}

void GUI::deleteChore()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Not deleted!", "No chore was selected!");
		return;
	}
	Chore c = this->serv.getAllChoresInRepo()[selectedIndex];
	this->serv.deleteChore_service(c.getTitle());

	QMessageBox::information(this, "Deleted!", "The chore was deleted");

	this->populateChores();

	int lastElement = this->serv.getAllChoresInRepo().size() - 1;
	
	this->choresListWidget->setCurrentRow(lastElement);
}

void GUI::updateChore()
{
	string title = this->titleLineEdit->text().toStdString();
	string type = this->typeLineEdit->text().toStdString();
	string lastPerformed = this->lastPerformedLineEdit->text().toStdString();
	string timesPerformed = this->timesPerformedLineEdit->text().toStdString();
	string vision = this->visionLineEdit->text().toStdString();

	if (this->serv.checkExisting(title) == 0)
	{
		QMessageBox::information(this, "Not updated!", "The chore doesn't exist");
	}
	else {
		this->serv.updateChore_service(title, type, lastPerformed, stoi(timesPerformed), vision);

		QMessageBox* updateBox;
		
		updateBox->information(this, "Updated!", "The chore was updated");

		this->populateChores();

		int lastElement = this->serv.getAllChoresInRepo().size() - 1;

		this->choresListWidget->setCurrentRow(lastElement);
	}
}

