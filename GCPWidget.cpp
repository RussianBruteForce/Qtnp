#include "GCPWidget.h"
#include "ui_GCPWidget.h"

/*
 * Widget for chosing parameters of GRID and COORDINATE PLANE
 */
GCPWidget::GCPWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GCPWidget)
{
	ui->setupUi(this);

	ui->coordinatePlaneGroupBox->setDisabled(true);
	connect(ui->coordinatePlaneGroupBox, &QGroupBox::toggled,
	        ui->coordinatePlaneGroupBox, &QGroupBox::setEnabled);
}

GCPWidget::~GCPWidget()
{
	delete ui;
}

/*
 * Ask widget for emiting data
 */
void GCPWidget::askData()
{

}
