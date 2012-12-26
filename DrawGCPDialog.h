#ifndef DRAWGCPDIALOG_H
#define DRAWGCPDIALOG_H

#include <QDialog>

#include "GCPWidget.h"

namespace Ui {
class DrawGCPDialog;
}

class DrawGCPDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit DrawGCPDialog(QWidget *parent = 0);
	~DrawGCPDialog();

	GCPWidget *gcp;
	
private:
	Ui::DrawGCPDialog *ui;
};

#endif // DRAWGCPDIALOG_H
