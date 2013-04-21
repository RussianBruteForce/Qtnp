#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "Settings.h"
#include "ColorWidget.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit SettingsDialog(Settings &_s, QWidget *parent = 0);
	~SettingsDialog();
	
private:
	Ui::SettingsDialog *ui;
	Settings *s;
	ColorWidget *bg, *graphic, *grid, *cp, *penColor, *rpenColor;

	void setupTemplates();
	void addTemplate(QPoint resolution, QString addon);

public slots:
	void save();
	void updateUI();
	void restoreDefaults();
	void setPresentationDir();
};

#endif // SETTINGSDIALOG_H
