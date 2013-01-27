#include "Settings.h"

Settings::Settings(QObject *parent) :
        QSettings(parent)
{
	white = Qt::white;
	black = Qt::black;

	_t.append(QPoint(1366, 768));
	_t.append(QPoint(1280, 1024));
	_t.append(QPoint(1024, 768));
	_t.append(QPoint(1920, 1080));
	_t.append(QPoint(1280, 800));
	_t.append(QPoint(1440, 900));
}

QColor Settings::bgColor()
{
	return this->value(BG_COLOR, DBG_COLOR).value<QColor>();
}

QColor Settings::gridColor()
{
	return this->value(GRID_COLOR, DGRID_COLOR).value<QColor>();
}

QColor Settings::cpColor()
{
	return this->value(CP_COLOR, DCP_COLOR).value<QColor>();
}

QColor Settings::graphicColor()
{
	return this->value(GRAPHIC_COLOR, DGRAPHIC_COLOR).value<QColor>();
}

QColor Settings::penColor()
{
	return this->value(P_COLOR, DP_COLOR).value<QColor>();
}

QColor Settings::rpenColor()
{
	return this->value(R_COLOR, DR_COLOR).value<QColor>();
}

int Settings::imageTemplate()
{
	return this->value(IMAGE_TEMPLATE, DIMAGE_TEMPLATE).toInt();
}

int Settings::thickness()
{
	return this->value(THICKNESS, DTHICKNESS).toInt();
}

int Settings::gridThickness()
{
	return this->value(GRID_THICKNESS, DGRID_THICKNESS).toInt();
}

int Settings::cpThickness()
{
	return this->value(CP_THICKNESS, DCP_THICKNESS).toInt();
}

int Settings::graphicThickness()
{
	return this->value(GRAPHIC_THICKNESS, DGRAPHIC_THICKNESS).toInt();
}

int Settings::gridStep()
{
	return this->value(GRID_STEP, DGRID_STEP).toInt();
}

int Settings::cpStep()
{
	return this->value(CP_STEP, DCP_STEP).toInt();
}

bool Settings::reverseToolBar()
{
	return this->value(REVERSE_TOOLBAR, DREVERSE_TOOLBAR).toBool();
}

bool Settings::syncCPToGrid()
{
	return this->value(SYNC_CP_TO_GRID, DSYNC_CP_TO_GRID).toBool();
}

bool Settings::autoPresentation()
{
	return this->value(AUTO_PRESENTATION, DAUTO_PRESENTATION).toBool();
}

QString Settings::language()
{
	return this->value(LANGUAGE, DLANGUAGE).toString();
}

QString Settings::presentationDirectory()
{
	return this->value(PRESENTATION_DIRECTORY, DPRESENTATION_DIRECTORY).toString();
}

QList<QPoint> *Settings::templates()
{
	return &_t;
}

void Settings::restoreDefaults()
{
	setBgColor(DBG_COLOR);
	setGridColor(DGRID_COLOR);
	setCpColor(DCP_COLOR);
	setGraphicColor(DGRAPHIC_COLOR);
	setPenColor(DP_COLOR);
	setRpenColor(DR_COLOR);
	setImageTemplate(DIMAGE_TEMPLATE);
	setGridThickness(DGRID_THICKNESS);
	setCpThickness(DCP_THICKNESS);
	setGraphicThickness(DGRAPHIC_THICKNESS);
	setGridStep(DGRID_STEP);
	setCpStep(DCP_STEP);
	setReverseToolBar(DREVERSE_TOOLBAR);
	setSyncCPToGrid(DSYNC_CP_TO_GRID);
	setAutoPresentation(DAUTO_PRESENTATION);
	setLanguage(DLANGUAGE);
	setPresentationDirectory(DPRESENTATION_DIRECTORY);
}

void Settings::setBgColor(QColor c)
{
	this->setValue(BG_COLOR, c);
}

void Settings::setGridColor(QColor c)
{
	this->setValue(GRID_COLOR, c);
}

void Settings::setCpColor(QColor c)
{
	this->setValue(CP_COLOR, c);
}

void Settings::setGraphicColor(QColor c)
{
	this->setValue(GRAPHIC_COLOR, c);
}

void Settings::setPenColor(QColor c)
{
	this->setValue(P_COLOR, c);
}

void Settings::setRpenColor(QColor c)
{
	this->setValue(R_COLOR, c);
}

void Settings::setImageTemplate(int t)
{
	this->setValue(IMAGE_TEMPLATE, t);
}

void Settings::setThickness(int t)
{
	this->setValue(THICKNESS, t);
}

void Settings::setGridThickness(int t)
{
	this->setValue(GRID_THICKNESS, t);
}

void Settings::setCpThickness(int t)
{
	this->setValue(CP_THICKNESS, t);
}

void Settings::setGraphicThickness(int t)
{
	this->setValue(GRAPHIC_THICKNESS, t);
}

void Settings::setGridStep(int s)
{
	this->setValue(GRID_STEP, s);
}

void Settings::setCpStep(int s)
{
	this->setValue(CP_STEP, s);
}

void Settings::setReverseToolBar(bool r)
{
	this->setValue(REVERSE_TOOLBAR, r);
}

void Settings::setSyncCPToGrid(bool p)
{
	this->setValue(SYNC_CP_TO_GRID, p);
}

void Settings::setAutoPresentation(bool p)
{
	this->setValue(AUTO_PRESENTATION, p);
}

void Settings::setLanguage(QString l)
{
	this->setValue(LANGUAGE, l);
}

void Settings::setPresentationDirectory(QString d)
{
	this->setValue(PRESENTATION_DIRECTORY, d);
}
