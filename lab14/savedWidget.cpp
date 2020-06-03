#include "savedWidget.h"

savedWidget::savedWidget(savedTabelModel* model,QWidget *parent)
	: QWidget(parent), model{ model }
{
	ui.setupUi(this);

	ui.savedtableView->setModel(model);
}

savedWidget::~savedWidget()
{
}
