#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11GUI.h"

class lab11GUI : public QMainWindow
{
	Q_OBJECT

public:
	lab11GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::lab11GUIClass ui;
};
