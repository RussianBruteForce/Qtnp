#ifndef QTNP_H
#define QTNP_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QMenu>
#include <QFileDialog>
#include <QLineEdit>

#include "DigitalClock.h"
#include "DrawCore.h"
#include "ColorWidget.h"

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
	void loadToolbar(bool reverse);
	
private:
	Ui::Qtnp *ui;
	DrawCore *image;
	DigitalClock *clock;
	ColorWidget *penWidget, *rpenWidget;
	QSpinBox *thicksessBox;
	QCheckBox *stickyDrawCheckBox;
	QToolButton *changePensButton, *fullscreenButton,
	*newFileButton, *gridButton,
	*graphicButton,*prevButton, *toolsButton;
	QMenu *toolsMenu;
	QLineEdit *statusLine;
	//QtnpNewFileDialog *new_file_dialog;
	//QtnpAddGridDialog *add_grid_dialog;
	//QtnpGraphicDialog *draw_graphic_dialog;
	QString _openedFileLocation;

private slots:
	void newFile();
	void save();
	void saveAs();
	void exit();
	void fullScreen();
	void swapPens();
	void saveFileBecause(QString reason);
	void openFile();
	void drawGrid();
	void setTool_NONE();
	void setTool_PEN();
	void setTool_LINE();
	void setTool_SQUARE();
	void setTool_ELLIPSE();
	void setTool_CIRCLE();
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
	void textToToolBar(QString text);

protected:
	void closeEvent(QCloseEvent* event);
};

#endif // QTNP_H
