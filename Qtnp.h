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
#include <QDir>
#include <QStringList>

#include "Settings.h"
#include "DigitalClock.h"
#include "DrawCore.h"
#include "ColorWidget.h"
#include "DrawGCPDialog.h"
#include "NewFileDialog.h"
#include "DrawGraphicDialog.h"
#include "SettingsDialog.h"

namespace Ui {
class Qtnp;
}

class Qtnp : public QMainWindow
{
	Q_OBJECT
	
public:
    explicit Qtnp(Settings &settings, QWidget *parent = 0);
	~Qtnp();
	void makeConnections();
	void makeUI();
	void loadToolbar(bool reverse);
	void preparePresentation();
	Settings *s;
	DrawCore *image;
	
private:
	Ui::Qtnp *ui;
	DigitalClock *clock;
	ColorWidget *penColor, *rpenColor;
	QSpinBox *thicksessBox;
	QCheckBox *stickyDraw;
	QToolButton *changePensButton, *fullscreenButton,
	*newFileButton, *gridButton,
	*graphicButton, *prevButton, *toolsButton,
	*nImage, *pImage;
	QMenu *toolsMenu;
	QLineEdit *statusLine;
	QString _openedFileLocation;
	DrawGCPDialog *gcpd;
	DrawGraphicDialog *gd;
	NewFileDialog *nfd;
	SettingsDialog *sd;
	QStringList presentationImages;
	uint _currentPresentationImage;

private slots:
	void newFile();
	void save();
	void saveAs();
	void exit();
	void fullScreen();
	void swapPens();
	void openFile();
	void drawGCP();
	void drawGraphic();
	void settings();
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
	void wrongExp();
	void nextImage();
	void prevImage();

protected:
	void closeEvent(QCloseEvent* event);
};

#endif // QTNP_H
