#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QColor>
#include <QPoint>
#include <QDir>

/*
 * Define Qtnp version
 */
#define VERSION "2.0.0-alpha"

/*
 * Config file settings:
 */

/*
 * Background color for new images
 */
#define BG_COLOR "bgColor"
#define DBG_COLOR         white

/*
 * Grid color for new grids
 */
#define GRID_COLOR "gridColor"
#define DGRID_COLOR           black

/*
 * Coordinate plane color for new coordinate planes
 */
#define CP_COLOR "cpColor"
#define DCP_COLOR         black

/*
 * Graphic color for new graphics
 */
#define GRAPHIC_COLOR "graphicColor"
#define DGRAPHIC_COLOR              black

/*
 * Pen color
 */
#define P_COLOR "penColor"
#define DP_COLOR          black

/*
 * Right pen color
 */
#define R_COLOR "rpenColor"
#define DR_COLOR           white

/*
 * Default template for new images
 */
#define IMAGE_TEMPLATE "imageTemplate"
#define DIMAGE_TEMPLATE               5

/*
 * Thicknesses for instruments
 */
#define THICKNESS "thickness"
#define DTHICKNESS           3
#define GRID_THICKNESS "gridThickness"
#define DGRID_THICKNESS               1
#define CP_THICKNESS "cpThickness"
#define DCP_THICKNESS             3
#define GRAPHIC_THICKNESS "graphicThickness"
#define DGRAPHIC_THICKNESS                  3

/*
 * Steps
 */
#define GRID_STEP "gridStep"
#define DGRID_STEP          50
#define CP_STEP "cpStep"
#define DCP_STEP        50

/*
 * Reverse toolsbar's buttons place
 * false for RIGHT_TO_LEFT
 * true for LEFT_TO_RIGHT
 * Starting with FULLSCREEN_BUTTON
 */
#define REVERSE_TOOLBAR "reverseToolBar"
#define DREVERSE_TOOLBAR                false

/*
 * Repeat grid's settings automaticaly for coordinate plane in GCPWidget
 */
#define SYNC_CP_TO_GRID "syncCPToGrid"
#define DSYNC_CP_TO_GRID              true


/*
 * Start presentation automaticaly
 */
#define AUTO_PRESENTATION "autoPresentation"
#define DAUTO_PRESENTATION                  false

/*
 * ui language
 */
#define LANGUAGE "language"
#define DLANGUAGE          "en"

/*
 * Presentation directory
 */
#define PRESENTATION_DIRECTORY "presentationDirectory"
#define DPRESENTATION_DIRECTORY                       QDir::homePath()



class Settings : public QSettings
{
	Q_OBJECT
public:
	explicit Settings(QObject *parent = 0);

	QColor bgColor();
	QColor gridColor();
	QColor cpColor();
	QColor graphicColor();
	QColor penColor();
	QColor rpenColor();
	int imageTemplate();
	int thickness();
	int gridThickness();
	int cpThickness();
	int graphicThickness();
	int gridStep();
	int cpStep();
	bool reverseToolBar();
	bool syncCPToGrid();
	bool autoPresentation();
	QString language();
	QString presentationDirectory();
	QList<QPoint>* templates();
	
signals:
	
public slots:
	void restoreDefaults();

	void setBgColor(QColor c);
	void setGridColor(QColor c);
	void setCpColor(QColor c);
	void setGraphicColor(QColor c);
	void setPenColor(QColor c);
	void setRpenColor(QColor c);
	void setImageTemplate(int t);
	void setThickness(int t);
	void setGridThickness(int t);
	void setCpThickness(int t);
	void setGraphicThickness(int t);
	void setGridStep(int s);
	void setCpStep(int s);
	void setReverseToolBar(bool r);
	void setSyncCPToGrid(bool p);
	void setAutoPresentation(bool p);
	void setLanguage(QString l);
	void setPresentationDirectory(QString d);

private:
	QColor white, black;
	QList<QPoint> _t;

};

#endif // SETTINGS_H
