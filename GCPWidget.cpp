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
GCPWidget::GCPWidget(Settings &_s, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GCPWidget)
{
	ui->setupUi(this);
	s = &_s;

	gridStepL = new QLabel(this);
	gridStepL->setText(tr("Step:"));
	ui->grid->addWidget(gridStepL);

	gridStep = new QSpinBox(this);
	gridStep->setFixedWidth(60);
	gridStep->setMinimum(3);
	gridStep->setValue(s->gridStep());
	ui->grid->addWidget(gridStep);

	gSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
	ui->grid->addSpacerItem(gSpacer);

	gridColorThicknessL = new QLabel(this);
	gridColorThicknessL->setText(tr("Color and thickness:"));
	ui->grid->addWidget(gridColorThicknessL);

	gridColor = new ColorWidget(s->gridColor());
	ui->grid->addWidget(gridColor);

	gridThickness = new QSpinBox(this);
	gridThickness->setFixedWidth(60);
	gridThickness->setMinimum(1);
	gridThickness->setValue(s->gridThickness());
	ui->grid->addWidget(gridThickness);


	coordinatePlaneStepL = new QLabel(this);
	coordinatePlaneStepL->setText(tr("Step:"));
	ui->coordinatePlane->addWidget(coordinatePlaneStepL);

	coordinatePlaneStep = new QSpinBox(this);
	coordinatePlaneStep->setFixedWidth(60);
	coordinatePlaneStep->setMinimum(3);
	coordinatePlaneStep->setValue(s->cpStep());
	ui->coordinatePlane->addWidget(coordinatePlaneStep);

	cSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Minimum);
	ui->coordinatePlane->addSpacerItem(cSpacer);

	coordinatePlaneColorThicknessL = new QLabel(this);
	coordinatePlaneColorThicknessL->setText(tr("Color and thickness:"));
	ui->coordinatePlane->addWidget(coordinatePlaneColorThicknessL);

	coordinatePlaneColor = new ColorWidget(s->cpColor());
	ui->coordinatePlane->addWidget(coordinatePlaneColor);

	coordinatePlaneThickness = new QSpinBox(this);
	coordinatePlaneThickness->setFixedWidth(60);
	coordinatePlaneThickness->setMinimum(1);
	coordinatePlaneThickness->setValue(s->cpThickness());
	ui->coordinatePlane->addWidget(coordinatePlaneThickness);

	coordinatePlaneNumbersOpacityL = new QLabel(this);
	coordinatePlaneNumbersOpacityL->setText(tr("Coordinate plane opacity:"));
	ui->coordinatePlaneOpacity->addWidget(coordinatePlaneNumbersOpacityL);

	coordinatePlaneNumbersOpacity = new QDoubleSpinBox(this);
	coordinatePlaneNumbersOpacity->setFixedWidth(60);
	coordinatePlaneNumbersOpacity->setMaximum(1);
	coordinatePlaneNumbersOpacity->setMinimum(0);
	coordinatePlaneNumbersOpacity->setSingleStep(0.05);
	coordinatePlaneNumbersOpacity->setValue(s->numbersOpacity());
	ui->coordinatePlaneOpacity->addWidget(coordinatePlaneNumbersOpacity);


	ui->coordinatePlane->setEnabled(false);
	connect(ui->coordinatePlaneGroupBox, &QGroupBox::toggled,
	        ui->coordinatePlane, &QHBoxLayout::setEnabled);
	ui->coordinatePlaneOpacity->setEnabled(false);
	connect(ui->coordinatePlaneGroupBox, &QGroupBox::toggled,
		ui->coordinatePlaneOpacity, &QHBoxLayout::setEnabled);

	if (s->syncCPToGrid()) {
		connect(gridColor, &ColorWidget::colorChanged,
		        coordinatePlaneColor, &ColorWidget::setColor);
		void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;
		connect(gridStep, signal,
		        coordinatePlaneStep, &QSpinBox::setValue);
		connect(gridThickness, signal,
		        coordinatePlaneThickness, &QSpinBox::setValue);
	}
}

GCPWidget::~GCPWidget()
{
	delete ui;
	delete gridColor;
	delete coordinatePlaneColor;

	delete gridStepL;
	delete coordinatePlaneStepL,
	delete gridColorThicknessL;
	delete coordinatePlaneColorThicknessL;
	delete gridStep;
	delete coordinatePlaneStep;
	delete gridThickness;
	delete coordinatePlaneThickness;

	gSpacer->~QSpacerItem();
	cSpacer->~QSpacerItem();
}

void GCPWidget::makeDedicated()
{
	ui->gridGroupBox->setCheckable(true);
	ui->gridGroupBox->setChecked(false);
	ui->coordinatePlaneGroupBox->setDisabled(true);
	connect(ui->gridGroupBox, &QGroupBox::toggled,
	        ui->coordinatePlaneGroupBox, &QGroupBox::setEnabled);
}

/*
 * Ask widget for emiting data
 */
void GCPWidget::askData()
{
	if (!ui->gridGroupBox->isCheckable() || (ui->gridGroupBox->isChecked())) {
		emit drawGrid(gridStep->value(),
		              gridColor->color(),
		              gridThickness->value());

		if (ui->coordinatePlaneGroupBox->isChecked())
			emit drawCoordinatePlane(coordinatePlaneStep->value(),
						 coordinatePlaneColor->color(),
						 coordinatePlaneThickness->value(),
						 coordinatePlaneNumbersOpacity->value());
	}
}
