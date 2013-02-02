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

DrawCore::DrawCore(QObject *parent)
{
	image = new QImage(1,1,QImage::Format_RGB32);
	painter = new QPainter(image);

	//newImage(1280,1024,Qt::white);

	_changed = false;
	gridMaxX = 0;
	gridMaxY = 0;
	gridMinX = 0;
	gridMinY = 0;

	_sticking = false;

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
 * Preparing for setting new image
 */
void DrawCore::prepareImage()
{
	painter->end();
	delete image;
	delete painter;
}

/*
 * Create new emty image x*y with colored background
 */
void DrawCore::newImage(int x, int y, QColor color)
{
	prepareImage();
	image = new QImage(x,y,QImage::Format_RGB32);
	painter = new QPainter(image);
	painter->fillRect(0,0, x,y, color);
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
	height_ = image->height();
	width_ = image->width();
	emit resetToolMenu();
	setActiveTool(NONE);
	prevList.append(*image);
	cX = width_/2;
	cY = height_/2;
	gridStep = -1;
	cpStep = -1;

	_changed = false;
}

/*
 * Load image from path
 */
bool DrawCore::loadImage(const QString path)
{
	if(image->load(path)) {
		setPixmap(QPixmap::fromImage(*image));
		height_ = image->height();
		width_ = image->width();
		emit resetToolMenu();
		setActiveTool(NONE);
		prevList.append(*image);
		cX = width_/2;
		cY = height_/2;
		gridStep = -1;
		cpStep = -1;
		_changed = false;
		return true;
	} else return false;

}

/*
 * Apply NEGATIVE to image
 */
void DrawCore::negative()
{
	int x,y;
	QRgb pixel;

	for(x=0; x<width_; x++){
		for(y=0; y<height_; y++){
			pixel = image->pixel(x,y);
			pixel = qRgb(255-qRed(pixel),255-qGreen(pixel),255-qBlue(pixel));
			image->setPixel(x,y,pixel);
		}
	}
	remember();
	refresh();
}

/*
 * Apply GRAYSCALE to image
 */
void DrawCore::grayscale()
{
	int x,y,r,g,b;
	QRgb pixel;
	for(x=0; x<width_; x++){
		for(y=0; y<height_; y++){
			pixel = image->pixel(x,y);
			r = g = b = (int) (0.299 * qRed(pixel) + 0.587 * qGreen(pixel) + 0.114 * qBlue(pixel));
			pixel = qRgb(r,g,b);
			image->setPixel(x,y,pixel);
		}
	}
	remember();
	refresh();
}


/*
 * Save image to path
 */
bool DrawCore::saveImage(const QString path)
{
	refresh();
	return image->save(path);
}

/*
 * Update label's pixmap
 */
void DrawCore::refresh()
{
	setPixmap(QPixmap::fromImage(*image));
}

/*
 * Mouse press event handler
 */
void DrawCore::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		switch(activeTool) {
		case NONE:
			break;
		case PEN:
			painting = 1;
			remember();
			start = end = event -> pos();
			break;
		case LINE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case JOGGED_LINE:
			painting = 1;
			remember();
			if (joggedLineFirstClickDone == true) {
				joggedLineFirstClickDone = false;
				start = event->pos();
			} else {
				end = event->pos();
				drawLine(pen);
				start = end;
				imageCopy = *image;
			}
			break;
		}
	} else if (event->button() == Qt::RightButton) {
		switch(activeTool) {
		case NONE:
			break;
		case PEN:
			painting = 1;
			remember();
			start = end = event -> pos();
			break;
		case LINE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case SQUARE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case ELLIPSE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case CIRCLE:
			painting = 1;
			remember();
			imageCopy = *image;
			start = end = event -> pos();
			break;
		case JOGGED_LINE:
			painting = 0;
			joggedLineFirstClickDone = true;
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
		end = event -> pos();
		switch(activeTool) {
		case NONE:
			break;
		case PEN:
			drawLine(pen);
			start = end;
			break;
		case LINE:
			*image = imageCopy;
			drawLine(pen);
			break;
		case SQUARE:
			*image = imageCopy;
			drawSquare(pen);
			break;
		case ELLIPSE:
			*image = imageCopy;
			drawEllipse(pen);
			break;
		case CIRCLE:
			*image = imageCopy;
			drawLine(pen);
			drawCircle(pen);
			break;
		}
	} else if ((event->buttons() & Qt::RightButton) && painting) {
			end = event -> pos();
			switch(activeTool) {
			case NONE:
				break;
			case PEN:
				drawLine(rpen);
				start = end;
				break;
			case LINE:
				*image = imageCopy;
				drawLine(rpen);
				break;
			case SQUARE:
				*image = imageCopy;
				drawSquare(rpen);
				break;
			case ELLIPSE:
				*image = imageCopy;
				drawEllipse(rpen);
				break;
			case CIRCLE:
				*image = imageCopy;
				drawLine(rpen);
				drawCircle(rpen);
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
		end = event -> pos();
		switch(activeTool) {
		case NONE:
			break;
		case PEN:
			drawLine(pen);
			painting = 0;
			break;
		case LINE:
			*image = imageCopy;
			drawLine(pen);
			painting = 0;
			break;
		case SQUARE:
			*image = imageCopy;
			drawSquare(pen);
			painting = 0;
			break;
		case ELLIPSE:
			*image = imageCopy;
			drawEllipse(pen);
			painting = 0;
			break;
		case CIRCLE:
			*image = imageCopy;
			drawCircle(pen);
			painting = 0;
			break;
		}
	} else if (event->button() == Qt::RightButton && painting){
		end = event -> pos();
		switch(activeTool) {
		case NONE:
			break;
		case PEN:
			drawLine(rpen);
			painting = 0;
			break;
		case LINE:
			*image = imageCopy;
			drawLine(rpen);
			painting = 0;
			break;
		case SQUARE:
			*image = imageCopy;
			drawSquare(rpen);
			painting = 0;
			break;
		case ELLIPSE:
			*image = imageCopy;
			drawEllipse(rpen);
			painting = 0;
			break;
		case CIRCLE:
			*image = imageCopy;
			drawCircle(rpen);
			painting = 0;
			break;
		}
	}
}

/*
 * Draw line with pen p
 */
void DrawCore::drawLine(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (_sticking)
		painter->drawLine(closestGridPoint(start), closestGridPoint(end));
	else painter->drawLine(start, end);
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

/*
 * Draw square with pen p
 */
void DrawCore::drawSquare(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (_sticking)
		painter->drawRect(QRect(closestGridPoint(start), closestGridPoint(end)));
	else painter->drawRect(QRect(start, end));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

/*
 * Draw ellipse with pen p
 */
void DrawCore::drawEllipse(QPen p)
{
	painter->begin(image);
	painter->setPen(p);
	if (_sticking)
		painter->drawEllipse(QRect(closestGridPoint(start), closestGridPoint(end)));
	else painter->drawEllipse(QRect(start, end));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

/*
 * Draw circle with pen p
 */
void DrawCore::drawCircle(QPen p)
{
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
	if (_sticking)
		painter->drawEllipse(QRect(closestGridPoint(QPoint(x_F,y_F)), closestGridPoint(QPoint(x_F2,y_F2))));
	else painter->drawEllipse(QRect(QPoint(x_F,y_F), QPoint(x_F2,y_F2)));
	painter->end();
	setPixmap(QPixmap::fromImage(*image));
}

/*
 * Set the pen color
 */
void DrawCore::setPenColor(QColor color)
{
	pen.setColor(color);
}

/*
 * Set right pen color
 */
void DrawCore::setRPenColor(QColor color)
{
	rpen.setColor(color);
}

/*
 * Set color to brush
 */
void DrawCore::setBrushColor(QColor color)
{
	pen.setColor(color);
	pen.setBrush(brush);
}

/*
 * Set pen trickness to size
 */
void DrawCore::setThickness(int size)
{
	pen.setWidth(size);
	rpen.setWidth(size);
}

/*
 * Set back previous image
 */
void DrawCore::prev(void)
{
	if (!(prevList.size() < 3)) {
		*image = prevList.last();
		prevList.pop_back();
		refresh();
	}
}

/*
 * Remember current image
 */
void DrawCore::remember(void)
{
	if (prevList.size() > 7) prevList.pop_front();
	prevList.append(*image);

	_changed = true;
}

/*
 * Return the closest point of grid
 */
QPoint DrawCore::closestGridPoint(QPoint p)
{
	double x,y;
	if (p.x() > cX)
		x = (p.x()-cX)/gridStep;
	else if (p.x() < cX)
		x = -1*(cX-p.x())/gridStep;
	else
		x = 0;
	if (p.y() > cY)
		y = -1*(p.y()-cY)/gridStep;
	else if (p.y() < cY)
		y = (cY-p.y())/gridStep;
	else
		y = 0;

	return getGridPointCoordinates(QPoint(round(x),round(y)), gridStep);
}

/*
 * Rounding num to near integer
 */
int DrawCore::round(double num)
{
//	int mul = 10;
//	if (num > 0)
//		return floor(num * mul + .5) / mul;
//	else
//		return ceil(num * mul - .5) / mul;
	return nearbyint(num);
}

/*
 * Set choosen tool active
 */
void DrawCore::setActiveTool(DrawTool whichTool)
{
	activeTool = whichTool;
	painting = 0;
	joggedLineFirstClickDone = true;
	switch(activeTool) {
	case NONE:
		this->setCursor(Qt::ArrowCursor);
		break;
	case PEN:
		this->setCursor(Qt::CrossCursor);
		break;
	case LINE:
		this->setCursor(Qt::CrossCursor);
		break;
	case JOGGED_LINE:
		this->setCursor(Qt::CrossCursor);
		break;
	case CIRCLE:
		this->setCursor(Qt::CrossCursor);
		break;
	}
}

/*
 * Return pen's color, where pen is code:
 * *0 for left
 * *1 for right
 */
QColor DrawCore::getPenColor(bool pen)
{
	if (!pen) return this->pen.color();
	else return this->rpen.color();
}

bool DrawCore::isModified()
{
	return _changed;
}

/*
 * Draw the grid
 */
void DrawCore::drawGrid(int step, QColor color,int width)
{
	int x,y;
	QPen gridPen;
	gridPen.setColor(color);
	gridPen.setWidth(width);

	gridStep = step;

	painter->begin(image);
	painter->setPen(gridPen);

	for(x=cX; x<width_; x+=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height_));
	}
	for(y=cY; y<height_; y+=step) {
		painter->drawLine(QPoint(0,y), QPoint(width_,y));
	}

	for(x=cX; x>0; x-=step) {
		painter->drawLine(QPoint(x,0), QPoint(x,height_));
	}
	for(y=cY; y>0; y-=step) {
		painter->drawLine(QPoint(0,y), QPoint(width_,y));
	}

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

/*
 * Draw the coordinate plane
 */
void DrawCore::drawCoordPlane(int coordPlaneStep, QColor clr, int width)
{
	cpStep = coordPlaneStep;
	int markSize;

	if (coordPlaneStep >= 8) {
		markSize = coordPlaneStep/4;
	} else {
		markSize = 2;
	}

	QPen coordPlanePen;
	coordPlanePen.setColor(clr);
	coordPlanePen.setWidth(width);
	//coordPlanePen.setCapStyle(Qt::RoundCap);
	coordPlanePen.setJoinStyle(Qt::RoundJoin);

	int cStartH, cEndH, cStartV, cEndV;
	cEndV = height_*0.027;
	cStartV = height_*0.973;
	cEndH = width_*0.973;
	cStartH = width_*0.027;

	painter->begin(image);
	painter->setPen(coordPlanePen);

	{
		painter->drawLine(QPoint(cX,cStartV),QPoint(cX,cEndV));
		painter->drawLine(QPoint(cStartH,cY),QPoint(cEndH,cY));
	}

	{
		painter->drawLine(QPoint(cX,height_*0.027),QPoint(cX-width_*0.01,height_*(0.037*1.5)));
		painter->drawLine(QPoint(cX,height_*0.027),QPoint(cX+width_*0.01,height_*(0.037*1.5)));

		painter->drawLine(QPoint(width_*0.973,cY),QPoint(width_*(1-(0.037*1.5)),cY-height_*0.01));
		painter->drawLine(QPoint(width_*0.973,cY),QPoint(width_*(1-(0.037*1.5)),cY+height_*0.01));
	}


	QFont markFont("Monospace");
	if (coordPlaneStep >= 20) {
		markFont.setPointSize(coordPlaneStep/2);
	} else {
		markFont.setPointSize(10);
	}
	markFont.setLetterSpacing(QFont::PercentageSpacing,75);
	painter->setFont(markFont);

	painter->setOpacity(0.65);

	{
		int mrk = 0;
		for (int i = cX; i < (cEndH-coordPlaneStep); i += coordPlaneStep) {
			painter->drawLine(QPoint(i,cY-markSize),QPoint(i,cY+markSize));
			if (mrk < 9) painter->drawText(
						i-markFont.pointSize()-width,
						cY+markFont.pointSize()+width+1,
						QString::number(mrk++));
			else painter->drawText(
						i-markFont.pointSize()*1.5-width,
						cY+markFont.pointSize()+width+1,
						QString::number(mrk++));
			gridMaxX = mrk;

		}
		mrk = 0;
		for (int i = cX-coordPlaneStep; i > cStartH; i -= coordPlaneStep) {
			painter->drawLine(QPoint(i,cY-markSize),QPoint(i,cY+markSize));
			if (mrk > -9) painter->drawText(
						i-markFont.pointSize()*1.3-width,
						cY+markFont.pointSize()+width+1,
						QString::number(--mrk));
			else painter->drawText(
						i-markFont.pointSize()*1.8-width,
						cY+markFont.pointSize()+width+1,
						QString::number(--mrk));
			gridMinX = mrk;
		}
		mrk = 0;
		for (int i = cY; i > (cEndV+coordPlaneStep); i -= coordPlaneStep) {
			painter->drawLine(QPoint(cX-markSize,i),QPoint(cX+markSize,i));
			if (mrk < 9) painter->drawText(
						cX-markFont.pointSize()+width,
						i+width-(coordPlaneStep-markFont.pointSize()),
						QString::number(++mrk));
			else painter->drawText(
						cX-markFont.pointSize()*1.5+width,
						i+width-(coordPlaneStep-markFont.pointSize()),
						QString::number(++mrk));
			gridMaxY = mrk;
		}
		mrk = 0;
		for (int i = cY; i < cStartV; i += coordPlaneStep) {
			painter->drawLine(QPoint(cX-markSize,i),QPoint(cX+markSize,i));
			if (mrk > -9) painter->drawText(
						cX-markFont.pointSize()*1.5+width,
						i+width+markFont.pointSize()+coordPlaneStep,
						QString::number(--mrk));
			else painter->drawText(
						cX-markFont.pointSize()*2+width,
						i+width+markFont.pointSize()+coordPlaneStep,
						QString::number(--mrk));
			gridMinY = mrk;
		}
	}

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

/*
 * Return grid coordinate
 */
QPoint DrawCore::getGridPointCoordinates(QPoint gPoint, int step)
{
	return QPoint(cX+step*gPoint.x(), cY-step*gPoint.y());
}

/*
 * Draw graphic of str
 */
void DrawCore::drawGraphic(QString str, QColor color, int width)
{
	wrongExp = false;
	if (cpStep == -1) {
		emit parserMsg("No coordinate plane drawed!");
		return;
	}

	ExpParser fparser;
	fparser.setE(str);
	connect(&fparser,&ExpParser::badExp,this,&DrawCore::functionExeption);


	double i = gridMinX;
	double sX, sY, bX, bY;

	bX = gridMinX;
	bY = fparser.getR(i);
	if (wrongExp) {
		emit badGraphicExpError();
		return;
	}

	painter->begin(image);
	QPen gpen;
	gpen.setColor(color);
	gpen.setWidth(width);
	gpen.setJoinStyle(Qt::RoundJoin);
	gpen.setCapStyle(Qt::RoundCap);
	painter->setPen(gpen);

	sX = cX+gridStep*bX;
	sY = cY-gridStep*bY;

	QPolygon grphc;
	grphc.append(QPoint(round(sX),round(sY)));

	for (; i < gridMaxX; i += 0.05) {
		bX = i;
		bY = fparser.getR(i);
		emit parserMsg(tr("Last value ") + QString::number(bY));

		sX = cX+gridStep*bX;
		sY = cY-gridStep*bY;
		grphc.append(QPoint(round(sX),round(sY)));
	}

	painter->setRenderHint(QPainter::Antialiasing);
//	TODO: drawing point-by-point
	painter->drawPolyline(grphc);

	painter->end();
	setPixmap(QPixmap::fromImage(*image));

	remember();
	refresh();
}

/*
 * Set all tools sticky to grid
 */
void DrawCore::setSticky(bool ans)
{
	_sticking = ans;
}

/*
 * Emit error message to GUI
 */
void DrawCore::functionExeption(QString msg)
{
	wrongExp = true;
	emit parserMsg(msg);
}
