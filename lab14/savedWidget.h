#pragma once

#include <QWidget>
#include "ui_savedWidget.h"
#include "savedTabelModel.h"

class savedWidget : public QWidget
{
	Q_OBJECT

public:
	savedWidget(savedTabelModel* model, QWidget *parent = Q_NULLPTR);
	~savedWidget();

private:
	Ui::savedWidget ui;
	savedTabelModel* model;
};
