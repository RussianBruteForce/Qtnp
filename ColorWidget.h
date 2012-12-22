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

#ifndef ColorWidget_H
#define ColorWidget_H

#include <QLabel>
#include <QColor>
#include <QPainter>
#include <QColorDialog>
#include <QPixmap>
#include <QMouseEvent>



// виджет выбора цвета
class ColorWidget : public QLabel
{
	Q_OBJECT
public:
	ColorWidget(int, int, int, int b_s = 30);
	~ColorWidget();
	QColor getCurrentColor();

private:
	QColor *currentColor, clr;
	QPixmap *pixmapColor;
	QPainter *painterColor;
	int boxSize;

public slots:
	void setColor(QColor);

signals:
	void sendColor(QColor);

protected:
	void mousePressEvent(QMouseEvent *event);
};

#endif // ColorWidget_H
