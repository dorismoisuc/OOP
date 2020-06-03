#include "lab11GUI.h"
#include "qmessagebox.h"

using namespace std;


lab11GUI::lab11GUI(Service&s,savedTabelModel*model, QWidget* parent)
	: QMainWindow(parent), serv{ s } , model(model)
{
	ui.setupUi(this);
	this->populateList();
	this->populateSaved();
	this->changeMode();
	this->getSelectedIndexS();
	this->connectSignalsAndSlots();
	this->connectSignalsAndSlotsS();
}


void lab11GUI::changeMode()
{
	if (modeChange == 0)
	{
		this->modeChange = 1;
		this->ui.addButton->setEnabled(true);
		this->ui.deleteButton->setEnabled(true);
		this->ui.updateButton->setEnabled(true);
		this->ui.filterButton->setEnabled(false);
		this->ui.saveButton->setEnabled(false);
		this->ui.nextButton->setEnabled(false);
		this->ui.undoButton->setEnabled(true);
		this->ui.redoButton->setEnabled(true);
		this->ui.modeButton->setEnabled(true);
	}
	else if (modeChange == 1)
	{
		this->modeChange = 0;
		this->ui.modeButton->setEnabled(true);
		this->ui.addButton->setEnabled(false);
		this->ui.deleteButton->setEnabled(false);
		this->ui.updateButton->setEnabled(false);
		this->ui.filterButton->setEnabled(true);
		this->ui.saveButton->setEnabled(true);
		this->ui.nextButton->setEnabled(true);
		this->ui.undoButton->setEnabled(false);
		this->ui.redoButton->setEnabled(false);
	}
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

void lab11GUI::help()
{
	string helpForTheApp;
	helpForTheApp += "Hello!\n With this GUI app you can:\n1. Add a new chore.\n2. Update one of the chores.\n";
	helpForTheApp += "3. Delete one of the chores. \n";
	helpForTheApp += "4. With the undo button or CTRL+Z you can undo your last operation.\n";
	helpForTheApp += "5. With the redo button or CTRL+Y you can redo your last operation.\n";
	helpForTheApp += "All of the above in the first mode.\n You can also change mode\n And do the following:\n";
	helpForTheApp += "1. By clicking next, you'll see the chores one by one.\n";
	helpForTheApp += "2. By saving, you can save the wanted chore.\n";
	helpForTheApp += "3. With filter, you'll see the chores with <times performed> less than the value you entered and the type you choose.\n";
	helpForTheApp += "In addition, you can see the saved chores in a table, by clicking 'show'\n";
	helpForTheApp += "Have fun with this app!\n";
	QFont myFont("Calibri", 12);
	myFont.setBold(true);
	QMessageBox mb("Help :)",
		QString::fromStdString(helpForTheApp),
		QMessageBox::NoIcon,
		QMessageBox::Ok | QMessageBox::Default,
		QMessageBox::NoButton,
		QMessageBox::NoButton);
	mb.setFont(myFont);
	QPixmap exportIconita("floare.png");
	mb.setIconPixmap(exportIconita);
	mb.exec();
	
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

void lab11GUI::undoGUI()
{
	
		if (!this->serv.undo())
			QMessageBox::information(this, "No undo!", "No more undos available");

		this->populateList();

		int lastElement = this->serv.getAllChoresInRepo().size() - 1;

		this->ui.choreListWidget->setCurrentRow(lastElement);
	
}

void lab11GUI::saved()
{
	this->model->layoutAboutToBeChanged();
	this->model->layoutChanged();
	
	savedC.show();
}

void lab11GUI::redoGUI()
{
	if (!this->serv.redo())
		QMessageBox::information(this, "No redo!", "No more redos available");
	this->populateList();

	int lastElement = this->serv.getAllChoresInRepo().size() - 1;

	this->ui.choreListWidget->setCurrentRow(lastElement);
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
	//QObject::connect(this->ui.modeButton, &QPushButton::clicked, this, &lab11GUI::changeMode);
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
	QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &lab11GUI::undoGUI);
	QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &lab11GUI::redoGUI);
	QObject::connect(this->ui.modeButton, &QPushButton::clicked, this, &lab11GUI::changeMode);
	QObject::connect(this->ui.showButton, &QPushButton::clicked, this, &lab11GUI::saved);
	QObject::connect(this->ui.helpButton, &QPushButton::clicked, this, &lab11GUI::help);
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

			vector<Chore> savedChores = this->serv.getServantList();

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