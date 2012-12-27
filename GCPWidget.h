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

#ifndef GCPWIDGET_H
#define GCPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

#include "ColorWidget.h"
#include "Settings.h"

namespace Ui {
class GCPWidget;
}

class GCPWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit GCPWidget(Settings &_s, QWidget *parent = 0);
	~GCPWidget();

public slots:
	void askData();
	
private:
	Ui::GCPWidget *ui;
	QLabel *gridStepL, *coordinatePlaneStepL,
	*gridColorThicknessL, *coordinatePlaneColorThicknessL;
	QSpinBox *gridStep, *coordinatePlaneStep,
	*gridThickness, *coordinatePlaneThickness;
	ColorWidget *gridColor, *coordinatePlaneColor;
	QSpacerItem *gSpacer, *cSpacer;
	Settings *s;



signals:
	void drawGrid(int step, QColor color, int width = 1);
	void drawCoordinatePlane(int coordPlaneStep, QColor clr, int width = 1);
};

#endif // GCPWIDGET_H
