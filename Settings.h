#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QColor>

#define BG_COLOR "bgColor"
#define DBG_COLOR         white
#define GRID_COLOR "gridColor"
#define DGRID_COLOR           black
#define CP_COLOR "cpColor"
#define DCP_COLOR         black
#define P_COLOR "penColor"
#define DP_COLOR          black
#define R_COLOR "rpenColor"
#define DR_COLOR           white
#define IMAGE_TEMPLATE "imageTemplate"
#define DIMAGE_TEMPLATE               0
#define GRID_THICKNESS "gridThickness"
#define DGRID_THICKNESS               1
#define CP_THICKNESS "cpThickness"
#define DCP_THICKNESS             3
#define GRID_STEP "gridStep"
#define DGRID_STEP          50
#define CP_STEP "cpStep"
#define DCP_STEP        50
#define REVERSE_TOOLBAR "reverseToolBar"
#define DREVERSE_TOOLBAR                false
#define LANGUAGE "language"
#define DLANGUAGE          "en"
#define THICKNESS "thickness"
#define DTHICKNESS           3
#define GRID_S_TO_CP "gridSettingsToCp"
#define DGRID_S_TO_CP                  true

class Settings : public QSettings
{
	Q_OBJECT
public:
	explicit Settings(QObject *parent = 0);

	QColor bgColor();
	QColor gridColor();
	QColor cpColor();
	QColor penColor();
	QColor rpenColor();
	int imageTemplate();
	int thickness();
	int gridThickness();
	int cpThickness();
	int gridStep();
	int cpStep();
	bool reverseToolBar();
	bool gridSettingsToCp();
	QString language();
	
signals:
	
public slots:
	void restoreDefault();

	void setBgColor(QColor c);
	void setGridColor(QColor c);
	void setCpColor(QColor c);
	void setPenColor(QColor c);
	void setRpenColor(QColor c);
	void setImageTemplate(int t);
	void setThickness(int t);
	void setGridThickness(int t);
	void setCpThickness(int t);
	void setGridStep(int s);
	void setCpStep(int s);
	void setReverseToolBar(bool r);
	void setGridSettingsToCp(bool p);
	void setLanguage(QString l);

private:
	QColor white, black;

};

#endif // SETTINGS_H
