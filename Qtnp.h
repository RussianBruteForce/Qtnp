#ifndef QTNP_H
#define QTNP_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "DigitalClock.h"

namespace Ui {
class Qtnp;
}

class Qtnp : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Qtnp(QWidget *parent = 0);
	~Qtnp();
	void makeConnections();
	void loadStatusbar();
	
private:
	Ui::Qtnp *ui;

private slots:
	void newFile();
	void save();
	void saveAs();
	void exit();
	void fullScreen();
	void changePens();
	void saveFileBecause(QString reason);
	void openFile();
	void addGrid();
	void setTool_NONE();
	void setTool_PEN();
	void setTool_LINE();
	void setTool_SQUARE();
	void setTool_ELLIPSE();
	void setTool_JOGGED_LINE();
	void setStyle_win();
	void setStyle_winxp();
	void setStyle_gtk();
	void setStyle_cde();
	void setStyle_plastique();
	void setStyle_motif();
	void about();
	void drawGraphic();
	void wrongExp();
	void textToStatusbar(QString text);
};

#endif // QTNP_H
