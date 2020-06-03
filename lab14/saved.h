#pragma once

#include <QWidget>
#include "ui_saved.h"

class saved : public QWidget, public Ui::saved
{
	Q_OBJECT

public:
	saved(QWidget *parent = Q_NULLPTR);
	~saved();
};
