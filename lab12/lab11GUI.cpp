#include "lab11GUI.h"
#include "qmessagebox.h"

using namespace std;


lab11GUI::lab11GUI(Service&s,QWidget* parent)
	: QMainWindow(parent), serv{ s }
{
	ui.setupUi(this);
	this->populateList();
	this->populateSaved();
	this->getSelectedIndexS();
	this->connectSignalsAndSlots();
	this->connectSignalsAndSlotsS();
}


void lab11GUI::populateList()
{
	//this->serv.initialize();

	this->ui.choreListWidget->setStyleSheet("background-color:#f1d1d1;");
	QFont serifFont("Times", 14);

	this->ui.choreListWidget->setFont(serifFont);

	this->ui.choreListWidget->clear();

	vector<Chore> chores = this->serv.getAllChoresInRepo();
	for (Chore& c : chores)
		this->ui.choreListWidget->addItem(QString::fromStdString(c.getTitle() + " - " + c.getType()));

}

int lab11GUI::getSelectedIndexS() const
{

	QModelIndexList selectedIndexes = this->ui.savedCList->selectionModel()->selectedIndexes();
	
	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit_2->clear();
		this->ui.typeLineEdit_2->clear();
		this->ui.lastPerformedLineEdit_2->clear();
		this->ui.timesPerformedLineEdit_2->clear();
		this->ui.visionLineEdit_2->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	
	return selectedIndex;

}

int lab11GUI::getSelectedIndex() const
{
	
		QModelIndexList selectedIndexes = this->ui.choreListWidget->selectionModel()->selectedIndexes();
		if (selectedIndexes.size() == 0)
		{
			this->ui.titleLineEdit->clear();
			this->ui.typeLineEdit->clear();
			this->ui.lastPerformedLineEdit->clear();
			this->ui.timesPerformedLineEdit->clear();
			this->ui.visionLineEdit->clear();
			return -1;
		}

		int selectedIndex = selectedIndexes.at(0).row();
		return selectedIndex;


}

int lab11GUI::getSelectedIndexF() const
{
	QModelIndexList selectedIndexes = this->ui.savedCList->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0)
	{
		this->ui.titleLineEdit->clear();
		this->ui.typeLineEdit->clear();
		this->ui.lastPerformedLineEdit->clear();
		this->ui.timesPerformedLineEdit->clear();
		this->ui.visionLineEdit->clear();
		return -1;
	}

	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
	

}

void lab11GUI::nextC_gui()
{
	this->ui.savedCList->clear();
	Chore c = this->serv.next_Chore();
	this->ui.savedCList->addItem(QString::fromStdString(c.getTitle() + " - " + c.getType()+ " - " + c.getLastPerformed() + " - " + to_string(c.getTimesPerformed())+" - " + c.getVision()));
	this->ui.titleLineEdit_2->setText(QString::fromStdString(c.getTitle()));
	this->ui.typeLineEdit_2->setText(QString::fromStdString(c.getType()));
	this->ui.lastPerformedLineEdit_2->setText(QString::fromStdString(c.getLastPerformed()));
	this->ui.timesPerformedLineEdit_2->setText(QString::fromStdString(to_string(c.getTimesPerformed())));
	this->ui.visionLineEdit_2->setText(QString::fromStdString(c.getVision()));

}


void lab11GUI::deleteChore()
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

	this->populateList();

	int lastElement = this->serv.getAllChoresInRepo().size() - 1;

	this->ui.choreListWidget->setCurrentRow(lastElement);

}

void lab11GUI::connectSignalsAndSlotsS()
{
	QObject::connect(this->ui.savedCList, &QListWidget::itemSelectionChanged, [this]() {

		int selectedIndex = this->getSelectedIndexS();

		if (selectedIndex < 0)
			return;
		if (this->serv.getServantList().size() == 0)
			return;

		Chore c = this->serv.getServantList()[selectedIndex];
		this->ui.titleLineEdit_2->setText(QString::fromStdString(c.getTitle()));
		this->ui.typeLineEdit_2->setText(QString::fromStdString(c.getType()));
		this->ui.lastPerformedLineEdit_2->setText(QString::fromStdString(c.getLastPerformed()));
		this->ui.timesPerformedLineEdit_2->setText(QString::fromStdString(to_string(c.getTimesPerformed())));
		this->ui.visionLineEdit_2->setText(QString::fromStdString(c.getVision()));
	});
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &lab11GUI::saveByTitle);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &lab11GUI::filterByType);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &lab11GUI::nextC_gui);
}

void lab11GUI::connectSignalsAndSlots()
{
	QObject::connect(this->ui.choreListWidget, &QListWidget::itemSelectionChanged, [this]() {

		int selectedIndex = this->getSelectedIndex();

		if (selectedIndex < 0)
			return;
		Chore c = this->serv.getAllChoresInRepo()[selectedIndex];
		this->ui.titleLineEdit->setText(QString::fromStdString(c.getTitle()));
		this->ui.typeLineEdit->setText(QString::fromStdString(c.getType()));
		this->ui.lastPerformedLineEdit->setText(QString::fromStdString(c.getLastPerformed()));
		this->ui.timesPerformedLineEdit->setText(QString::fromStdString(to_string(c.getTimesPerformed())));
		this->ui.visionLineEdit->setText(QString::fromStdString(c.getVision()));

	});
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &lab11GUI::deleteChore);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &lab11GUI::addChore);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &lab11GUI::updateChore);
	//QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &lab11GUI::saveByTitle);
	//QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &lab11GUI::filterByType);
	//QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &lab11GUI::nextC);
}


void lab11GUI::addChore()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string type = this->ui.typeLineEdit->text().toStdString();
	string lastPerformed = this->ui.lastPerformedLineEdit->text().toStdString();
	string timesPerformed = this->ui.timesPerformedLineEdit->text().toStdString();
	string vision = this->ui.visionLineEdit->text().toStdString();
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

		this->populateList();

		int lastElement = this->serv.getAllChoresInRepo().size() - 1;

		this->ui.choreListWidget->setCurrentRow(lastElement);
	}
}


void lab11GUI::updateChore()
{
	string title = this->ui.titleLineEdit->text().toStdString();
	string type = this->ui.typeLineEdit->text().toStdString();
	string lastPerformed = this->ui.lastPerformedLineEdit->text().toStdString();
	string timesPerformed = this->ui.timesPerformedLineEdit->text().toStdString();
	string vision = this->ui.visionLineEdit->text().toStdString();

	if (this->serv.checkExisting(title) == 0)
	{
		QMessageBox::information(this, "Not updated!", "The chore doesn't exist");
	}
	else {
		this->serv.updateChore_service(title, type, lastPerformed, stoi(timesPerformed), vision);

		QMessageBox* updateBox;

		updateBox->information(this, "Updated!", "The chore was updated");

		this->populateList();

		int lastElement = this->serv.getAllChoresInRepo().size() - 1;

		this->ui.choreListWidget->setCurrentRow(lastElement);
	}
}


void lab11GUI::populateSaved()
{

	//this->serv.initialize();

	this->ui.savedCList->setStyleSheet("background-color:#93AAF9;");
	QFont serifFont("Times", 14);

	this->ui.savedCList->setFont(serifFont);

	this->ui.savedCList->clear();

	//this->ui.savedCList->addItem(QString::fromStdString("string"));
	
	vector<Chore> chores = this->serv.getServantList();
	for (Chore& c : chores)
		this->ui.savedCList->addItem(QString::fromStdString(c.getTitle() + " - " + c.getType()));

}

void lab11GUI::saveByTitle()
{
	int ok = 1;
	if (this->ui.titleLineEdit_2->text().size()==0)
	{
		ok = 0;
		QMessageBox::information(this, "Not saved", "Not enough information");
	}
	if (ok == 1) {
		string title = this->ui.titleLineEdit_2->text().toStdString();
		if (this->serv.checkExisting(title) == 0)
		{
			QMessageBox::information(this, "Not saved", "Title doesn't exist");
		}
		else
		{
			this->serv.save(title);

			QMessageBox::information(this, "Saved!", "The chore was saved");

			this->populateSaved();

			int lastElement = this->serv.getServantList().size() - 1;

			this->ui.savedCList->setCurrentRow(lastElement);
		}
	}
}

void lab11GUI::filterByType()
{
	int ok = 1;
	int index = 0;
	string type = this->ui.typeLineEdit_2->text().toStdString();
	string filterrr;
	if (this->ui.timesPerformedLineEdit_2->text().size()==0 || this->ui.typeLineEdit_2->text().size()==0)
	{
		ok = 0;
		QMessageBox::information(this, "Not filtered!", "There wasn't enough information added");
	}
	string timesPerformed = this->ui.timesPerformedLineEdit_2->text().toStdString();
	/*
	if (type.size() == 0 || timesPerformed.size() == 0)
	{
		ok = 0;
		QMessageBox::information(this, "Not filtered!", "There wasn't enough information added");
	}*/
	if (ok == 1) {
		vector<Chore> filtered = this->serv.get_by_type(type, stoi(timesPerformed));



		if (filtered.size() == 0)
		{
			QMessageBox::information(this, "Not filtered!", "There were not any chores matching");
		}
		else
		{
			//QMessageBox::information(this, "Filtered!", "There were some chores matching");
			this->ui.savedCList->setStyleSheet("background-color:#93AAF9;");
			QFont serifFont("Times", 14);

			this->ui.savedCList->setFont(serifFont);

			this->ui.savedCList->clear();

			for (Chore& c : filtered)
			{
				index++;
				filterrr += to_string(index) +". " + "Title: " + c.getTitle() +  "\n Type: " + c.getType() + "\n Last Performed: " + c.getLastPerformed() + "\n Times Performed: " + to_string(c.getTimesPerformed()) + "\n Vision: " + c.getVision() + '\n';

			}

			QMessageBox::information(this, "Filtered!", QString::fromStdString(filterrr));

			//this->ui.savedCList->setCurrentRow(index-1);
		
		}
		
	}
}


/*
void lab11GUI::nextC(vector<Chore>& chores,vector<Chore>::iterator& it)
{

	if (chores.begin() == chores.end())
		QMessageBox::information(this,"Empty chore list!","No chores found");
	if (it!=chores.end())
	{
		++it;
		if (it == chores.end())
			it = chores.begin();
		this->ui.savedCList->addItem(QString::fromStdString((*it).toString()));
	}
}
*/