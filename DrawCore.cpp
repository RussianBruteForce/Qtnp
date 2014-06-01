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

#include "DrawCore.h"

DrawCore::DrawCore()
{
	image = nullptr;
	painter = nullptr;

	oldImages.reserve(3);

	//newImage(1280,1024,Qt::white);

	modified = false;
	gridMaxX = 0;
	gridMaxY = 0;
	gridMinX = 0;
	gridMinY = 0;

	sticking = false;

	setAlignment(Qt::AlignTop);

	pen.setColor(Qt::black);
	rpen.setColor(Qt::white);

	brush.setColor(Qt::green);

	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	rpen.setCapStyle(Qt::RoundCap);
	rpen.setJoinStyle(Qt::RoundJoin);
}

/*
 * Creates new emty image x*y with colored background
 */
void DrawCore::newImage(int x, int y, QColor color)
{
	if (!image)
		delete image;
	image = new QPixmap(x,y);

	if (!painter)
		delete painter;
	painter = new QPainter(image);

	painter->fillRect(0,0, x,y, color);
	painter->end();
	//refresh();
	height = image->height();
	width = image->width();
	emit resetToolMenu();
	setActiveTool(DrawTool::NONE);
	oldImages.append(*image);
	cX = width/2;
	cY = height/2;
	gridStep = -1;
	cpStep = -1;

	modified = false;

	refresh();
}

/*
 * Loads image from path
 */
bool DrawCore::loadImage(const QString path)
{
	if(image->load(path)) {
		setPixmap(*image);
		height = image->height();
		width = image->width();
		emit resetToolMenu();
		setActiveTool(DrawTool::NONE);
		oldImages.append(*image);
		cX = width/2;
		cY = height/2;
		gridStep = -1;
		cpStep = -1;
		modified = false;
		return true;
	} else
		return false;
}

/*
 * Applies NEGATIVE to image
 */
void DrawCore::negative()
{
	auto img = image->toImage();
	int x,y;
	QRgb pixel;

	for(x=0; x<width; x++){
		for(y=0; y<height; y++){
			pixel = img.pixel(x,y);
			pixel = qRgb(255-qRed(pixel),255-qGreen(pixel),255-qBlue(pixel));
			img.setPixel(x,y,pixel);
		}
	}
	*image = QPixmap::fromImage(img);
	remember();
	refresh();
}

/*
 * Applies GRAYSCALE to image
 */
void DrawCore::grayscale()
{
	auto img = image->toImage();
	int x,y,r,g,b;
	QRgb pixel;
	for(x=0; x<width; x++){
		for(y=0; y<height; y++){
			pixel = img.pixel(x,y);
			r = g = b = (int) (0.299 * qRed(pixel) + 0.587 * qGreen(pixel) + 0.114 * qBlue(pixel));
			pixel = qRgb(r,g,b);
			img.setPixel(x,y,pixel);
		}
	}
	*image = QPixmap::fromImage(img);
	remember();
	refresh();
}


/*
 * Saves image to path
 */
bool DrawCore::saveImage(const QString path)
{
	return pixmap()->save(path);
}

/*
 * Updates label's pixmap
 */
void DrawCore::refresh()
{
	setPixmap(*image);
}

/*
 * Mouse press event handler
 */
void DrawCore::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::LINE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::SQUARE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::ELLIPSE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::CIRCLE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::JOGGED_LINE:
			painting = 1;
			remember();
			if (joggedLineFirstClickDone == true) {
				joggedLineFirstClickDone = false;
				start = event->pos();
			} else {
				end = event->pos();
				drawLine(pen);
				start = end;
			}
			break;
		case DrawTool::FILL:
			remember();
			start = event->pos();
			fill(pen.color().rgb());
			break;
		default:
			break;
		}
	} else if (event->button() == Qt::RightButton) {
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::LINE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::SQUARE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::ELLIPSE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::CIRCLE:
			painting = 1;
			remember();
			start = end = event->pos();
			break;
		case DrawTool::JOGGED_LINE:
			painting = 0;
			joggedLineFirstClickDone = true;
			break;
		case DrawTool::FILL:
			qDebug() << "MOUSE R PRESS EVENT";
			remember();
			start = event->pos();
			fill(rpen.color().rgb());
			break;
		default:
			break;
		}
	}
}

/*
 * Mouse move event handler
 */
void DrawCore::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && painting) {
		end = event->pos();
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			drawLine(pen);
			start = end;
			break;
		case DrawTool::LINE:
			*image = oldImages.last();
			drawLine(pen);
			break;
		case DrawTool::SQUARE:
			*image = oldImages.last();
			drawSquare(pen);
			break;
		case DrawTool::ELLIPSE:
			*image = oldImages.last();
			drawEllipse(pen);
			break;
		case DrawTool::CIRCLE:
			*image = oldImages.last();
			drawLine(pen);
			drawCircle(pen);
			break;
		default:
			break;
		}
	} else if ((event->buttons() & Qt::RightButton) && painting) {
		end = event->pos();
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			drawLine(rpen);
			start = end;
			break;
		case DrawTool::LINE:
			*image = oldImages.last();
			drawLine(rpen);
			break;
		case DrawTool::SQUARE:
			*image = oldImages.last();
			drawSquare(rpen);
			break;
		case DrawTool::ELLIPSE:
			*image = oldImages.last();
			drawEllipse(rpen);
			break;
		case DrawTool::CIRCLE:
			*image = oldImages.last();
			drawLine(rpen);
			drawCircle(rpen);
			break;
		default:
			break;
		}
	}
}

/*
 * Mouse release event handler
 */
void DrawCore::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && painting) {
		end = event->pos();
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			drawLine(pen);
			painting = 0;
			break;
		case DrawTool::LINE:
			*image = oldImages.last();
			drawLine(pen);
			painting = 0;
			break;
		case DrawTool::SQUARE:
			*image = oldImages.last();
			drawSquare(pen);
			painting = 0;
			break;
		case DrawTool::ELLIPSE:
			*image = oldImages.last();
			drawEllipse(pen);
			painting = 0;
			break;
		case DrawTool::CIRCLE:
			*image = oldImages.last();
			drawCircle(pen);
			painting = 0;
			break;
		default:
			break;
		}
	} else if (event->button() == Qt::RightButton && painting){
		end = event->pos();
		switch(activeTool) {
		case DrawTool::NONE:
			break;
		case DrawTool::PEN:
			drawLine(rpen);
			painting = 0;
			break;
		case DrawTool::LINE:
			*image = oldImages.last();
			drawLine(rpen);
			painting = 0;
			break;
		case DrawTool::SQUARE:
			*image = oldImages.last();
			drawSquare(rpen);
			painting = 0;
			break;
		case DrawTool::ELLIPSE:
			*image = oldImages.last();
			drawEllipse(rpen);
			painting = 0;
			break;
		case DrawTool::CIRCLE:
			*image = oldImages.last();
			drawCircle(rpen);
			painting = 0;
			break;
		default:
			break;
		}
	}
}

/*
 * Draws line with pen p
 */
void DrawCore::drawLine(const QPen &p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawLine(closestGridPoint(start), closestGridPoint(end));
	else
		painter->drawLine(start, end);
	painter->end();
	refresh();
}

/*
 * Draws square with pen p
 */
void DrawCore::drawSquare(const QPen &p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawRect(QRect(closestGridPoint(start), closestGridPoint(end)));
	else
		painter->drawRect(QRect(start, end));
	painter->end();
	refresh();
}

/*
 * Draws ellipse with pen p
 */
void DrawCore::drawEllipse(const QPen &p)
{
	painter->begin(image);
	painter->setPen(p);
	if (sticking)
		painter->drawEllipse(QRect(closestGridPoint(start), closestGridPoint(end)));
	else
		painter->drawEllipse(QRect(start, end));
	painter->end();
	refresh();
}

/*
 * Draws circle with pen p
 */
void DrawCore::drawCircle(const QPen &p)
{
	if (sticking) {
		start = closestGridPoint(start);
		end = closestGridPoint(end);
	}

	painter->begin(image);
	painter->setPen(p);
	int x_R, y_R, x_F, y_F, x_F2, y_F2;
	x_R = fabs(start.x() - end.x());
	y_R = fabs(start.y() - end.y());
	int R = sqrt(pow(x_R,2) + pow(y_R,2));
	if (end.x() > start.x()) {
		x_F = start.x() + R;
		x_F2 = start.x() - R;
	} else {
		x_F = start.x() - R;
		x_F2 = start.x() + R;
	}
	if (end.y() > start.y()) {
		y_F = start.y() + R;
		y_F2 = start.y() - R;
	} else {
		y_F = start.y() - R;
		y_F2 = start.y() + R;
	}
	painter->drawEllipse(QRect(QPoint(x_F,y_F), QPoint(x_F2,y_F2)));
	painter->end();
	refresh();
}

/*
 * next non-recursive scan line fill method
 */
typedef struct { int xl, xr, y, dy; } LINESEGMENT;

#define MAXDEPTH 10000

#define PUSH(XL, XR, Y, DY) \
    if( sp < stack+MAXDEPTH && Y+(DY) >= 0 && Y+(DY) <= DrawCore::height -1) \
    { sp->xl = XL; sp->xr = XR; sp->y = Y; sp->dy = DY; ++sp; }

#define POP(XL, XR, Y, DY) \
    { --sp; XL = sp->xl; XR = sp->xr; Y = sp->y+(DY = sp->dy); }

void DrawCore::fill(const QRgb color)
{
	auto img = image->toImage();

	auto oldColor = img.pixel(start);
	if (oldColor == color)
		return;

	auto x = start.x(), y = start.y();
	if (
			x < 0 ||
			y < 0 ||
			x >= width-1 ||
			y >= height-1)
		return;

	int left, x1, x2, dy;

	LINESEGMENT stack[MAXDEPTH], *sp = stack;

	PUSH(x, x, y, 1);       /* needed in some cases */
	PUSH(x, x, y+1, -1);    /* seed segment (popped 1st) */

	while (sp > stack) {
		POP(x1, x2, y, dy);

		for (x = x1; x >= 0 && img.pixel(x, y) == oldColor; --x)
			img.setPixel(x, y, color);

		if (x >= x1)
			goto SKIP;

		left = x+1;
		if (left < x1)
			PUSH(y, left, x1-1, -dy);    /* leak on left? */

		x = x1+1;

		do {
			for ( ; x<=width-1 && img.pixel(x, y) == oldColor; ++x )
				img.setPixel(x, y, color);

			PUSH(left, x-1, y, dy);

			if (x > x2+1 )
				PUSH(x2+1, x-1, y, -dy);    /* leak on right? */

SKIP:			for (++x; x <= x2 && img.pixel(x, y) != oldColor; ++x) {;}

			left = x;
		} while(x <= x2);
	}

	*image = QPixmap::fromImage(img);
	refresh();
}

/*
 * Sets the pen color
 */
void DrawCore::setPenColor(QColor color)
{
	pen.setColor(color);
}

/*
 * Sets right pen color
 */
void DrawCore::setRPenColor(QColor color)
{
	rpen.setColor(color);
}

/*
 * Sets pen trickness to size
 */
void DrawCore::setThickness(int size)
{
	pen.setWidth(size);
	rpen.setWidth(size);
}

/*
 * Set back previous image
 */
void DrawCore::undo(void)
{
	if (!oldImages.isEmpty()) {
		*image = oldImages.takeLast();
		refresh();
	}
}

/*
 * Remembers current image
 */
void DrawCore::remember(void)
{
	if (oldImages.size() > 7) oldImages.pop_front();
	oldImages.append(*image);

	modified = true;
}

/*
 * Returns the closest point of grid
 */
QPoint DrawCore::closestGridPoint(const QPoint &p)
{
	return getCoordinatesOfGridPoint(
				getGridPointByCoordinates(p, gridStep),
				gridStep);
}

/*
 * Returns coordinates of grid point on image
 */
QPoint DrawCore::getCoordinatesOfGridPoint(QPoint gPoint, int step)
{
	return QPoint(cX+step*gPoint.x(), cY-step*gPoint.y());
}

/*
 * Returns grid point by coordinates
 */
QPoint DrawCore::getGridPointByCoordinates(QPoint coordinate, int step)
{
	QPoint ret;
	double x, y;
	if (coordinate.x() > cX)
		x =((double)(coordinate.x()-cX)/step);
	else if (coordinate.x() < cX)
		x = (-1*(double)(cX-coordinate.x())/step);
	else
		x = (0);
	if (coordinate.y() > cY)
		y = (-1*(double)(coordinate.y()-cY)/step);
	else if (coordinate.y() < cY)
		y = ((double)(cY-coordinate.y())/step);
	else
		y = (0);

	ret.setX(round(x));
	ret.setY(round(y));

	return ret;
}

/*
 * Rounds num to near integer
 */
int DrawCore::round(double num)
{
	return nearbyint(num);
}

QPolygon* DrawCore::findAllPointsOfGraphic(QString &function_string, double step)
{
	ExpParser fparser;
	fparser.setE(function_string);
	connect(&fparser,&ExpParser::badExp,
		this,&DrawCore::functionExeption);

	if (fparser.getR(0) == 666) {
		emit badGraphicExpError();
		return nullptr;
	}

	double sX, sY, bX, bY;
	bX = gridMinX;
	bY = fparser.getR(bX);
	sX = cX+gridStep*bX;
	sY = cY-gridStep*bY;

	auto grphc = new QPolygon;
	grphc->append(QPoint(round(sX),round(sY)));

	for (double i = gridMinX; i < gridMaxX; i += step) {
		bX = i;
		bY = fparser.getR(i);

		sX = cX+gridStep*bX;
		sY = cY-gridStep*bY;
		grphc->append(QPoint(round(sX),round(sY)));
	}
	emit drawError(tr("Last value ") + QString::number(bY));
	return grphc;
}

QList<QPolygon> *DrawCore::splitGraphicToPolygons(QPolygon *points_of_graphic)
{
	if (!points_of_graphic)
		return nullptr;
	auto polygons = new QList<QPolygon>;
	polygons->append(*points_of_graphic);
	auto *current = &polygons->last();
	for (int i = 1; i < current->size(); i++) {
		if (abs(
				current->at(i-1).x()
				-
				current->at(i).x()) <= 0
		    ||
		    abs(
				current->at(i-1).y()
				-
				current->at(i).y()) <= 0
		    ||
		    abs(
				current->at(i-1).y()
				-
				current->at(i).y()) > height
		    ||
		    abs(
				current->at(i-1).x()
				-
				current->at(i).x()) > width
		    ) {
			current->removeAt(i);
			polygons->append(current->mid(0, i));
			polygons->append(current->mid(i, current->size()-i));
			polygons->removeAt(polygons->size() - 3);
			current = &polygons->last();
			qDebug() << "HERE!";
		}
	}
	delete points_of_graphic;
	return polygons;
}

inline double DrawCore::getGraphicStep()
{
	return (double)1/cpStep;
}

/*
 * Sets choosen tool active
 */
void DrawCore::setActiveTool(DrawTool tool)
{
	activeTool = tool;
	painting = 0;
	joggedLineFirstClickDone = true;
	switch(activeTool) {
	case DrawTool::NONE:
		this->setCursor(Qt::ArrowCursor);
		break;
	case DrawTool::PEN:
		this->setCursor(Qt::CrossCursor);
		break;
	case DrawTool::LINE:
		this->setCursor(Qt::CrossCursor);
		break;
	case DrawTool::JOGGED_LINE:
		this->setCursor(Qt::CrossCursor);
		break;
	case DrawTool::CIRCLE:
		this->setCursor(Qt::CrossCursor);
		break;
	case DrawTool::FILL:
		this->setCursor(Qt::CrossCursor);
		break;
	default:
		break;
	}
}

bool DrawCore::isModified()
{
	return modified;
}

/*
 * Draws the grid
 */
void DrawCore::drawGrid(int step, QColor color, int penWidth)
{
	remember();
	int x,y;
	QPen gridPen;
	gridPen.setColor(color);
	gridPen.setWidth(penWidth);

	gridStep = step;

	painter->begin(image);
	painter->setPen(gridPen);

	for(x=cX; x<width; x+=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height));
	}
	for(y=cY; y<height; y+=step) {
		painter->drawLine(QPoint(0,y), QPoint(width,y));
	}

	for(x=cX; x>0; x-=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height));
	}
	for(y=cY; y>0; y-=step) {
		painter->drawLine(QPoint(0,y), QPoint(width,y));
	}

	painter->end();

	refresh();
}

/*
 * Draws the coordinate plane
 */
void DrawCore::drawCoordPlane(int coordPlaneStep, QColor clr, int penWidth, qreal numbersOpacity)
{
	remember();
	cpStep = coordPlaneStep;
	int markSize;

	if (coordPlaneStep >= 8)
		markSize = coordPlaneStep/4;
	else
		markSize = 2;

	QPen coordPlanePen;
	coordPlanePen.setColor(clr);
	coordPlanePen.setWidth(penWidth);
	//coordPlanePen.setCapStyle(Qt::RoundCap);
	coordPlanePen.setJoinStyle(Qt::RoundJoin);

	int cStartH, cEndH, cStartV, cEndV;
	cEndV = height*0.027;
	cStartV = height*0.973;
	cEndH = width*0.973;
	cStartH = width*0.027;

	painter->begin(image);
	painter->setPen(coordPlanePen);

	{
		painter->drawLine(QPoint(cX,cStartV),QPoint(cX,cEndV));
		painter->drawLine(QPoint(cStartH,cY),QPoint(cEndH,cY));
	}

	{
		painter->drawLine(QPoint(cX,height*0.027),
				  QPoint(cX-width*0.01,height*(0.037*1.5)));
		painter->drawLine(QPoint(cX,height*0.027),
				  QPoint(cX+width*0.01,height*(0.037*1.5)));

		painter->drawLine(QPoint(width*0.973,cY),
				  QPoint(width*(1-(0.037*1.5)),cY-height*0.01));
		painter->drawLine(QPoint(width*0.973,cY),
				  QPoint(width*(1-(0.037*1.5)),cY+height*0.01));
	}

	QFont markFont("Monospace");
	if (coordPlaneStep >= 20)
		markFont.setPixelSize(coordPlaneStep/2);
	else
		markFont.setPixelSize(10);

	markFont.setLetterSpacing(QFont::PercentageSpacing,75);
	painter->setFont(markFont);

	painter->setOpacity(numbersOpacity);

	{
		// Signing OX from 0 to right
		int mrk = 0;
		for (int i = cX; i < (cEndH-coordPlaneStep); i += coordPlaneStep) {
			painter->drawLine(QPoint(i,cY-markSize),QPoint(i,cY+markSize));
			if (mrk < 9) painter->drawText(
						i-markFont.pixelSize()*0.83-penWidth/2,
						cY+markFont.pixelSize()+penWidth/2+1,
						QString::number(mrk++));
			else painter->drawText(
						i-markFont.pixelSize()*0.83*1.6-penWidth/2,
						cY+markFont.pixelSize()+penWidth/2+1,
						QString::number(mrk++));
			gridMaxX = mrk;

		}
		// Signing OX from -1 to left
		mrk = 0;
		for (int i = cX-coordPlaneStep; i > cStartH; i -= coordPlaneStep) {
			painter->drawLine(QPoint(i,cY-markSize),QPoint(i,cY+markSize));
			if (mrk > -9) painter->drawText(
						i-markFont.pixelSize()*1.2-penWidth/2,
						cY+markFont.pixelSize()+penWidth/2+1,
						QString::number(--mrk));
			else painter->drawText(
						i-markFont.pixelSize()*1.2*1.6-penWidth/2,
						cY+markFont.pixelSize()+penWidth/2+1,
						QString::number(--mrk));
			gridMinX = mrk;
		}
		// Signing OY from 1 to up
		mrk = 0;
		for (int i = cY; i > (cEndV+coordPlaneStep); i -= coordPlaneStep) {
			painter->drawLine(QPoint(cX-markSize,i),QPoint(cX+markSize,i));
			if (mrk < 9) painter->drawText(
						cX-markFont.pixelSize()+penWidth/2,
						i+penWidth/2-(coordPlaneStep*0.5-markFont.pointSize()),
						QString::number(++mrk));
			else painter->drawText(
						cX-markFont.pixelSize()*1.4+penWidth/2,
						i+penWidth/2-(coordPlaneStep*0.5-markFont.pointSize()),
						QString::number(++mrk));
			gridMaxY = mrk;
		}
		// Signing OY from -1 to down
		mrk = 0;
		for (int i = cY; i < cStartV; i += coordPlaneStep) {
			painter->drawLine(QPoint(cX-markSize,i),QPoint(cX+markSize,i));
			if (mrk > -9) painter->drawText(
						cX-markFont.pixelSize()*1.2+penWidth/2,
						i+penWidth/2+markFont.pixelSize()+coordPlaneStep,
						QString::number(--mrk));
			else painter->drawText(
						cX-markFont.pixelSize()*1.2*1.4+penWidth/2,
						i+penWidth/2+markFont.pixelSize()+coordPlaneStep,
						QString::number(--mrk));
			gridMinY = mrk;
		}
	}

	painter->end();

	refresh();
}

/*
 * Draws graphic of func
 */
void DrawCore::drawGraphic(QString func, QColor color, int penWidth)
{
	if (cpStep == -1) {
		emit drawError("No coordinate plane drawed!");
		return;
	}
	remember();

	painter->begin(image);
	QPen gpen;
	gpen.setColor(color);
	gpen.setWidth(penWidth);
	gpen.setJoinStyle(Qt::RoundJoin);
	gpen.setCapStyle(Qt::RoundCap);
	painter->setPen(gpen);

	painter->setRenderHint(QPainter::Antialiasing);

	auto polygons = splitGraphicToPolygons(
					   findAllPointsOfGraphic(
						   func,
						   getGraphicStep()));

	if (!polygons) {
		emit drawError("Can't draw this!");
	} else {
		for (auto i : *polygons)
			painter->drawPolyline(i);

		painter->end();
		delete polygons;

		refresh();
	}
}


/*
 * Sets all tools sticky to grid
 */
void DrawCore::setSticky(bool ans)
{
	sticking = ans;
}

/*
 * Emits error message to GUI
 */
void DrawCore::functionExeption(QString msg)
{
	emit drawError(msg);
}
