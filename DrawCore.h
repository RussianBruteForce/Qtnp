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
	void loadImage(const QString ImageFile);
	void saveImage(const QString ImageFile);
	QColor getPenColor(bool pen);
	bool isChanged();

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
	void drawGrid(int step, QColor color,int width = 1);
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
