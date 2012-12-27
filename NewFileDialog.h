#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

#include "GCPWidget.h"
#include "Settings.h"
#include "ColorWidget.h"

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit NewFileDialog(Settings &_s, QWidget *parent = 0);
	~NewFileDialog();
	GCPWidget *gcp;
	
private:
	Ui::NewFileDialog *ui;
	Settings *s;
	ColorWidget *backgroundColor;

	void setupTemplates();
	void addTemplate(QPoint resolution, QString addon);

public slots:
	void draw();

private slots:
	void setTemplate(int t);

signals:
	void newImage(int x, int y, QColor color);
};

#endif // NEWFILEDIALOG_H
