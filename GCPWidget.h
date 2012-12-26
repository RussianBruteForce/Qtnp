#ifndef GCPWIDGET_H
#define GCPWIDGET_H

#include <QWidget>

namespace Ui {
class GCPWidget;
}

class GCPWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit GCPWidget(QWidget *parent = 0);
	~GCPWidget();

public slots:
	void askData();
	
private:
	Ui::GCPWidget *ui;

signals:
	void drawGrid(int step, QColor color, int width = 1);
	void drawCoordinatePlane(int coordPlaneStep, QColor clr, int width = 1);
};

#endif // GCPWIDGET_H
