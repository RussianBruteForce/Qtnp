#include "Qtnp.h"
#include "ui_Qtnp.h"

Qtnp::Qtnp(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Qtnp)
{
	ui->setupUi(this);
}

Qtnp::~Qtnp()
{
	delete ui;
}

void Qtnp::makeConnections()
{
	/*
	 * Menu actions:
	 */
	{
		connect(ui->actionNew, &QAction::triggered, this, &Qtnp::newFile);
		connect(ui->actionOpen, &QAction::triggered, this, &Qtnp::openFile);
		connect(ui->actionSave, &QAction::triggered, this, &Qtnp::save);
		connect(ui->actionSave_as, &QAction::triggered, this, &Qtnp::saveAs);
		connect(ui->actionExit, &QAction::triggered, this, &Qtnp::exit);
		connect(ui->actionFullscreen, &QAction::triggered, this, &Qtnp::fullScreen);
		connect(ui->actionGTK, &QAction::triggered, this, &Qtnp::setStyle_gtk);
		connect(ui->actionPlastique, &QAction::triggered, this, &Qtnp::setStyle_plastique);
		connect(ui->actionCDE, &QAction::triggered, this, &Qtnp::setStyle_cde);
		connect(ui->actionMotif, &QAction::triggered, this, &Qtnp::setStyle_motif);
		connect(ui->actionWindows, &QAction::triggered, this, &Qtnp::setStyle_win);
		connect(ui->actionWindows_XP, &QAction::triggered, this, &Qtnp::setStyle_winxp);
		connect(ui->actionAbout_Qtnp, &QAction::triggered, this, &Qtnp::about);
	}

	/*
	 * Statusbar actions
	 */
	{

	}
}

void Qtnp::loadStatusbar()
{
}


void Qtnp::newFile()
{
}

void Qtnp::save()
{
}

void Qtnp::saveAs()
{
}

void Qtnp::exit()
{
}

void Qtnp::fullScreen()
{
}

void Qtnp::changePens()
{
}

void Qtnp::saveFileBecause(QString reason)
{
}

void Qtnp::openFile()
{
}

void Qtnp::addGrid()
{
}

void Qtnp::setTool_NONE()
{
}

void Qtnp::setTool_PEN()
{
}

void Qtnp::setTool_LINE()
{
}

void Qtnp::setTool_SQUARE()
{
}

void Qtnp::setTool_ELLIPSE()
{
}

void Qtnp::setTool_JOGGED_LINE()
{
}

void Qtnp::setStyle_win()
{
	qApp->setStyle("windows");
}

void Qtnp::setStyle_winxp()
{
	qApp->setStyle("indowsxp");
}

void Qtnp::setStyle_gtk()
{
	qApp->setStyle("gtk");
}

void Qtnp::setStyle_cde()
{
	qApp->setStyle("cde");
}

void Qtnp::setStyle_plastique()
{
	qApp->setStyle("plastique");
}

void Qtnp::setStyle_motif()
{
	qApp->setStyle("motif");
}

void Qtnp::about()
{
	QMessageBox::about(this, tr("About Qtnp"),
	                   tr(
	                           "<p align=\"center\"><span style=\" font-size:14pt; font-weight:600; color:#20AA20;\">Cute Noob-Painter Qt5</span></p>"
	                           "<br>"
	                           "&nbsp; Qtnp  Copyright &copy; 2012  Victor &lt;BruteForce&gt;<br>"
	                           "&nbsp; This program comes with ABSOLUTELY NO WARRANTY.<br>"
	                           "&nbsp; This is free software, and you are welcome to<br>"
	                           "&nbsp; redistribute it under certain conditions.<br>"
	                           "&nbsp; For more look at <a href=\"http://www.gnu.org/licenses/gpl-3.0.html\">www.gnu.org</a><br>"
	                           "<p align=\"center\"><img src=\":resources/GNU_GPLv3_Logo.png\" width=\"250\" height=\"124\" /></p>"
	                           "&nbsp; Official git repo: <a href=\"https://github.com/RussianBruteForce/Qtnp\">https://github.com/RussianBruteForce/Qtnp</a><br>"
	                           "<br>"
	                           "&nbsp; E-mail: <a href=\"mailto:bruteforce@sigil.tk\">bruteforce@sigil.tk</a>"
	                      ));
}

void Qtnp::drawGraphic()
{
}

void Qtnp::wrongExp()
{
	QMessageBox::warning(this, tr("WRONG EXPRESSION"),
	                     tr("Wrong expression!\n"
	                        "It's can't be drawn"),
	                     QMessageBox::Ok);
}

void Qtnp::textToStatusbar(QString text)
{
}
