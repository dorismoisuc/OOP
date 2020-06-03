#include "lab11GUI.h"
#include <QtWidgets/QApplication>
#include "FileRepository.h"
#include "Service.h"
#include <memory>
//#include "GUI.h"
#include <qicon.h>
#include <qfont.h>
#include <qpalette.h>
#include "lab11GUI.h"
#include "savedWidget.h"

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
 
	
		FileRepo repo{};
		RepoServant repo2;
		Service service{ repo,repo2 };
		QIcon myIcon("myIconita.ico");

		service.file_location("chores.txt");

		savedTabelModel* model = new savedTabelModel{ repo2 };

		savedWidget tabelView{ model };

		lab11GUI GUI{ service,model };
		GUI.setWindowIcon(myIcon);
		GUI.show();
	
	return a.exec();
}
