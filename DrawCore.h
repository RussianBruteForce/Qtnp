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

#ifndef DRAWCORE_H
#define DRAWCORE_H

#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

#include <DrawTools.h>
#include "fparser/fparser.h"

class DrawCore : public QLabel
{
	Q_OBJECT
public:
	explicit DrawCore(QObject *parent = 0);
	bool loadImage(const QString path);
	bool saveImage(const QString path);
	QColor getPenColor(bool pen);
	bool isModified();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void refresh();
	void prepareImage();
	void drawLine(QPen p);
	void drawSquare(QPen p);
	void drawEllipse(QPen p);
	void drawCircle(QPen p);
	void remember();
	QPoint closestGridPoint(QPoint p);
	int round(double num);

	bool _changed;
	int width_, height_;
	bool painting, joggedLineFirstClickDone, _sticking, wrongExp;
	DrawTool activeTool;
	QPoint start, end;
	QImage *image;
	QImage imageCopy;
	QPen pen, rpen;
	QBrush brush;
	QPainter *painter;
	QPoint getGridPointCoordinates(QPoint gridPoint,int step);
	QList<QImage> prevList;
	int cX, cY;
	int gridMaxX, gridMaxY, gridMinX, gridMinY;
	int gridStep;

public slots:
	void setPenColor(QColor color);
	void setRPenColor(QColor color);
	void setBrushColor(QColor color); // check
	void setThickness(int size);
	void prev();
	void setActiveTool(DrawTool);
	void newImage(int x, int y, QColor color);
	void negative();
	void grayscale();
	void drawGrid(int step, QColor color, int width = 1);
	void drawCoordPlane(int coordPlaneStep, QColor clr, int width = 1);
	void drawGraphic(QString str, QColor color, int width);
	void setSticky(bool ans);
	void functionExeption(QString msg);

signals:
	void resetToolMenu();
	void badGraphicExpError();
	void parserMsg(QString);
};

#endif // DRAWCORE_H
