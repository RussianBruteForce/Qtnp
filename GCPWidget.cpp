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
