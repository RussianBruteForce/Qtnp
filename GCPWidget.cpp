/*
 *This file is part of Qtnp.
 *
 * Qtnp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Qtnp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Qtnp.  If not, see <http://www.gnu.org/licenses/>.
 */

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


	gridStepL = new QLabel(this);
	gridStepL->setText(tr("Step:"));
	ui->grid->addWidget(gridStepL);

	gridStep = new QSpinBox(this);
	gridStep->setValue(50);
	gridStep->setMinimum(3);
	ui->grid->addWidget(gridStep);

	gSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
	ui->grid->addSpacerItem(gSpacer);

	gridColorThicknessL = new QLabel(this);
	gridColorThicknessL->setText(tr("Color and thickness:"));
	ui->grid->addWidget(gridColorThicknessL);

	gridColor = new ColorWidget(0,0,0);
	ui->grid->addWidget(gridColor);

	gridThickness = new QSpinBox(this);
	gridThickness->setMinimum(1);
	gridThickness->setValue(1);
	ui->grid->addWidget(gridThickness);


	coordinatePlaneStepL = new QLabel(this);
	coordinatePlaneStepL->setText(tr("Step:"));
	ui->coordinatePlane->addWidget(coordinatePlaneStepL);

	coordinatePlaneStep = new QSpinBox(this);
	coordinatePlaneStep->setValue(50);
	coordinatePlaneStep->setMinimum(3);
	ui->coordinatePlane->addWidget(coordinatePlaneStep);

	cSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
	ui->coordinatePlane->addSpacerItem(cSpacer);

	coordinatePlaneColorThicknessL = new QLabel(this);
	coordinatePlaneColorThicknessL->setText(tr("Color and thickness:"));
	ui->coordinatePlane->addWidget(coordinatePlaneColorThicknessL);

	coordinatePlaneColor = new ColorWidget(0,0,0);
	ui->coordinatePlane->addWidget(coordinatePlaneColor);

	coordinatePlaneThickness = new QSpinBox(this);
	coordinatePlaneThickness->setMinimum(1);
	coordinatePlaneThickness->setValue(3);
	ui->coordinatePlane->addWidget(coordinatePlaneThickness);

	ui->coordinatePlane->setEnabled(false);
	connect(ui->coordinatePlaneGroupBox, &QGroupBox::toggled,
	        ui->coordinatePlane, &QHBoxLayout::setEnabled);

	connect(gridColor, &ColorWidget::colorChanged,
	        coordinatePlaneColor, &ColorWidget::setColor);
	void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;
	connect(gridStep, signal,
	        coordinatePlaneStep, &QSpinBox::setValue);
	connect(gridThickness, signal,
	        coordinatePlaneThickness, &QSpinBox::setValue);
}

GCPWidget::~GCPWidget()
{
	delete ui;
	delete gridColor;
	delete coordinatePlaneColor;
	gSpacer->~QSpacerItem();
	cSpacer->~QSpacerItem();
}

/*
 * Ask widget for emiting data
 */
void GCPWidget::askData()
{
	emit drawGrid(gridStep->value(),
	              gridColor->color(),
	              gridThickness->value());

	if (ui->coordinatePlaneGroupBox->isChecked()) {
		emit drawCoordinatePlane(coordinatePlaneStep->value(),
		                         coordinatePlaneColor->color(),
		                         coordinatePlaneThickness->value());
	}
}
