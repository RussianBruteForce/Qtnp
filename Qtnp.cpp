#include "Qtnp.h"
#include "ui_Qtnp.h"

Qtnp::Qtnp(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Qtnp)
{
	ui->setupUi(this);
	image = new DrawCore(ui->scrollArea);
	clock = new DigitalClock(ui->toolBar);

	isFullscreen = 0;

	openedFileLocation = "0";

	rpenWidget = new ColorWidget(255,255,255);
	rpenWidget->setToolTip(tr("Right pen color!"));
	penWidget = new ColorWidget(0,0,0);
	penWidget->setToolTip(tr("Pen color!"));

	tricksessBox = new QSpinBox(ui->toolBar);
	tricksessBox->setRange(1,200);
	tricksessBox->setValue(1);

	prevButton = new QToolButton(ui->toolBar);
	prevButton->setIcon(QIcon(":/resources/prev.png"));
	prevButton->setToolTip(tr("Previous"));

	newFileButton = new QToolButton(ui->toolBar);
	newFileButton->setIcon(QIcon(":/resources/new.png"));
	newFileButton->setToolTip(tr("New"));

	addGridButton = new QToolButton(ui->toolBar);
	addGridButton->setIcon(QIcon(":/resources/grid.png"));
	addGridButton->setToolTip(tr("Grid"));

	drawGraphicButton = new QToolButton(ui->toolBar);
	drawGraphicButton->setIcon(QIcon(":/resources/graphic.png"));
	drawGraphicButton->setToolTip(tr("Graphic"));

	changePensButton = new QToolButton(ui->toolBar);
	changePensButton->setIcon(QIcon(":/resources/change_pens_ico.png"));
	changePensButton->setToolTip(tr("Swap pens"));

	fullscreenButton = new QToolButton(ui->toolBar);
	fullscreenButton->setIcon(QIcon(":/resources/fullscreen.png"));
	fullscreenButton->setToolTip(tr("Fullscreen"));

	stickyDrawCheckBox = new QCheckBox(ui->toolBar);
	stickyDrawCheckBox->setToolTip(tr("Stick to web's points"));
	stickyDrawCheckBox->setChecked(false);


	toolsMenu = new QMenu;
	toolsMenu->addAction(QIcon(":/resources/cursor.png"),tr("Cursor"),this,SLOT(setTool_NONE()));
	toolsMenu->addAction(QIcon(":/resources/line_ico.png"),tr("Line"),this,SLOT(setTool_LINE()));
	toolsMenu->addAction(QIcon(":/resources/circle.png"),tr("Circle"),this,SLOT(setTool_CIRCLE()));
	toolsMenu->addAction(QIcon(":/resources/jogged_ico.png"),tr("Jogged Line"),this,SLOT(setTool_JOGGED_LINE()));
	toolsMenu->addAction(QIcon(":/resources/pencil_ico.png"),tr("Pen"),this,SLOT(setTool_PEN()));
	toolsMenu->setToolTip(tr("Tools"));

	toolsButton = new QToolButton(ui->toolBar);
	toolsButton->setToolTip(tr("Tools"));
	toolsButton->setMenu(toolsMenu);
	toolsButton->setPopupMode(QToolButton::InstantPopup);
	this->setTool_NONE();


	statusLine = new QLineEdit;
	statusLine->setReadOnly(true);

	this->ui->scrollArea->setWidget(image);
	this->ui->scrollArea->setBackgroundRole(QPalette::Dark);
	this->ui->scrollArea->setAlignment(Qt::AlignTop);
	this->setCentralWidget(this->ui->scrollArea);

	resize(1050,850);
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

		// style
		connect(ui->actionGTK, &QAction::triggered, this, &Qtnp::setStyle_gtk);
		connect(ui->actionPlastique, &QAction::triggered, this, &Qtnp::setStyle_plastique);
		connect(ui->actionCDE, &QAction::triggered, this, &Qtnp::setStyle_cde);
		connect(ui->actionMotif, &QAction::triggered, this, &Qtnp::setStyle_motif);
		connect(ui->actionWindows, &QAction::triggered, this, &Qtnp::setStyle_win);
		connect(ui->actionWindows_XP, &QAction::triggered, this, &Qtnp::setStyle_winxp);
		connect(ui->actionAbout_Qtnp, &QAction::triggered, this, &Qtnp::about);

		// effects
		connect(ui->actionGrayscale, &QAction::triggered, image, &DrawCore::grayscale);
		connect(ui->actionNegative, &QAction::triggered, image, &DrawCore::negative);
	}

	/*
	 * toolBar actions
	 */
	{

	}

	/*
	 * Tools menu actions
	 */
	{
		// Implemented in constructor
	}
}

void Qtnp::loadToolbar(bool reverse)
{
	QWidget *spacerWidget = new QWidget(this);
	spacerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spacerWidget->setVisible(true);

	ui->toolBar->setMovable(false);

	if (!reverse) {
		statusLine->setAlignment(Qt::AlignLeft);
		statusLine->setText("CHECK OLOLO");
		ui->toolBar->addWidget(statusLine);
		ui->toolBar->addWidget(spacerWidget);
		ui->toolBar->addWidget(clock);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(newFileButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(addGridButton);
		ui->toolBar->addWidget(drawGraphicButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(prevButton);
		ui->toolBar->addWidget(toolsButton);
		ui->toolBar->addWidget(stickyDrawCheckBox);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(penWidget);
		ui->toolBar->addWidget(rpenWidget);
		ui->toolBar->addWidget(changePensButton);
		ui->toolBar->addWidget(tricksessBox);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(fullscreenButton);
	} else {

	}
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
	toolsButton->setIcon(QIcon(":/resources/cursor.png"));
}

void Qtnp::setTool_PEN()
{
	toolsButton->setIcon(QIcon(":/resources/pencil_ico.png"));
}

void Qtnp::setTool_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/line_ico.png"));
}

void Qtnp::setTool_SQUARE()
{
}

void Qtnp::setTool_ELLIPSE()
{
}

void Qtnp::setTool_CIRCLE()
{
	toolsButton->setIcon(QIcon(":/resources/circle.png"));
}

void Qtnp::setTool_JOGGED_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/jogged_ico.png"));
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

void Qtnp::textToToolBar(QString text)
{
}

void Qtnp::closeEvent(QCloseEvent *event)
{
	saveFileBecause(tr("Save before closing?"));
	event->accept();
}
