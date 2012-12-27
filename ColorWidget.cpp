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

#include "ColorWidget.h"

ColorWidget::ColorWidget(QColor c, int b_s)
{
	boxSize = b_s;
	setFrameStyle(QFrame::Box | QFrame::Raised);
	currentColor = new QColor(c);
	pixmapColor = new QPixmap(boxSize, boxSize);
	painterColor = new QPainter(pixmapColor);
	painterColor->fillRect(0, 0, boxSize, boxSize, *currentColor);
	painterColor->end();
	setPixmap(*pixmapColor);
	setAlignment(Qt::AlignTop);

	setFixedSize(boxSize, boxSize);
}

ColorWidget::~ColorWidget()
{
	delete currentColor;
	delete pixmapColor;
	delete painterColor;
}

void ColorWidget::setColor(QColor color)
{
	*currentColor = color;
	clr = color;
	painterColor->begin(pixmapColor);
	painterColor->fillRect(0, 0, boxSize, boxSize, *currentColor);
	painterColor->end();
	setPixmap(*pixmapColor);
}

void ColorWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		clr = QColorDialog::getColor(*currentColor, this);
		if(clr.isValid()) {
			setColor(clr);
			emit colorChanged(clr);
		}
	}
}

QColor ColorWidget::color()
{
	return clr;
}
