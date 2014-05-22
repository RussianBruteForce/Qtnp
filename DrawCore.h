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

#include <QDebug>

#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>

#include "DrawTools.h"
#include "fparser/fparser.h"

class DrawCore : public QLabel
{
	Q_OBJECT
public:
	explicit DrawCore();
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
	void drawLine(QPen p);
	void drawSquare(QPen p);
	void drawEllipse(QPen p);
	void drawCircle(QPen p);
	void fill(QRgb color);
	void remember();
	QPoint closestGridPoint(QPoint p);
	QPoint getCoordinatesOfGridPoint(QPoint gridPoint,int step);
	QPoint getGridPointByCoordinates(QPoint coordinate, int step);
	int round(double num);
	QPolygon findAllPointsOfGraphic(QString function_string, double step);
	QList<QPolygon> splitGraphicToPolygons(QPolygon points_of_graphic);
	double getGraphicStep();

	bool modified;
	int width, height;
	bool painting, joggedLineFirstClickDone, _sticking, wrongExp;
	DrawTool activeTool;
	QPoint start, end;
	QPixmap *image;
	QPixmap imageCopy;
	QPen pen, rpen;
	QBrush brush;
	QPainter *painter;
	QList<QPixmap> prevList;
	int cX, cY; // image's center
	int gridMaxX, gridMaxY, gridMinX, gridMinY;
	int gridStep, cpStep;

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
	void drawGrid(int step, QColor color, int penWidth = 1);
	void drawCoordPlane(int coordPlaneStep, QColor clr, int penWidth = 1, qreal numbersOpacity = 1);
	void drawGraphic(QString func, QColor color, int penWidth);
	void setSticky(bool ans);

private slots:
	void functionExeption(QString msg);

signals:
	void resetToolMenu();
	void badGraphicExpError();
	void parserMsg(QString);
};

#endif // DRAWCORE_H
