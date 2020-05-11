#include "lab11GUI.h"
#include <QtWidgets/QApplication>
#include "FileRepository.h"
#include "Service.h"
#include <memory>
#include "GUI.h"
#include <qicon.h>
#include <qfont.h>
#include <qpalette.h>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
 
	
		FileRepo repo{};
		Service service{ repo };

		service.file_location("chores.txt");

		GUI gui{ service};
	
		QIcon myIcon("myiconita.ico");
	
		gui.setWindowIcon(myIcon);

		QFont serifFont("Times", 12);
		gui.setFont(serifFont);

		gui.setStyleSheet("background-color:#faf2f2;");

		gui.show();

	
	return a.exec();
}
