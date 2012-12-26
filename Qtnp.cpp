#include "Qtnp.h"
#include "ui_Qtnp.h"

Qtnp::Qtnp(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Qtnp)
{
	ui->setupUi(this);
	image = new DrawCore(ui->scrollArea);
	clock = new DigitalClock(ui->toolBar);

	_openedFileLocation = "0";

	rpenWidget = new ColorWidget(255,255,255);
	rpenWidget->setToolTip(tr("Right pen color!"));
	penWidget = new ColorWidget(0,0,0);
	penWidget->setToolTip(tr("Pen color!"));

	thicksessBox = new QSpinBox(ui->toolBar);
	thicksessBox->setRange(1,200);
	thicksessBox->setValue(1);

	prevButton = new QToolButton(ui->toolBar);
	prevButton->setIcon(QIcon(":/resources/prev.png"));
	prevButton->setToolTip(tr("Previous"));

	newFileButton = new QToolButton(ui->toolBar);
	newFileButton->setIcon(QIcon(":/resources/new.png"));
	newFileButton->setToolTip(tr("New"));

	gridButton = new QToolButton(ui->toolBar);
	gridButton->setIcon(QIcon(":/resources/grid.png"));
	gridButton->setToolTip(tr("Grid"));

	graphicButton = new QToolButton(ui->toolBar);
	graphicButton->setIcon(QIcon(":/resources/graphic.png"));
	graphicButton->setToolTip(tr("Graphic"));

	changePensButton = new QToolButton(ui->toolBar);
	changePensButton->setIcon(QIcon(":/resources/change_pens_ico.png"));
	changePensButton->setToolTip(tr("Swap pens"));

	fullscreenButton = new QToolButton(ui->toolBar);
	fullscreenButton->setIcon(QIcon(":/resources/fullscreen.png"));
	fullscreenButton->setToolTip(tr("Fullscreen"));

	stickyDrawCheckBox = new QCheckBox(ui->toolBar);
	stickyDrawCheckBox->setToolTip(tr("Stick to web's points"));
	stickyDrawCheckBox->setChecked(false);


	toolsMenu = new QMenu(this);
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


	statusLine = new QLineEdit(ui->toolBar);
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
	delete rpenWidget;
	delete penWidget;
}

void Qtnp::makeConnections()
{
	/*
	 * Menu actions:
	 */
	{
		connect(ui->actionNew, &QAction::triggered,
		        this, &Qtnp::newFile);
		connect(ui->actionOpen, &QAction::triggered,
		        this, &Qtnp::openFile);
		connect(ui->actionSave, &QAction::triggered,
		        this, &Qtnp::save);
		connect(ui->actionSave_as, &QAction::triggered,
		        this, &Qtnp::saveAs);
		connect(ui->actionExit, &QAction::triggered,
		        this, &Qtnp::exit);
		connect(ui->actionFullscreen, &QAction::triggered,
		        this, &Qtnp::fullScreen);

		// style
		connect(ui->actionGTK, &QAction::triggered,
		        this, &Qtnp::setStyle_gtk);
		connect(ui->actionPlastique, &QAction::triggered,
		        this, &Qtnp::setStyle_plastique);
		connect(ui->actionCDE, &QAction::triggered,
		        this, &Qtnp::setStyle_cde);
		connect(ui->actionMotif, &QAction::triggered,
		        this, &Qtnp::setStyle_motif);
		connect(ui->actionWindows, &QAction::triggered,
		        this, &Qtnp::setStyle_win);
		connect(ui->actionWindows_XP, &QAction::triggered,
		        this, &Qtnp::setStyle_winxp);
		connect(ui->actionAbout_Qtnp, &QAction::triggered,
		        this, &Qtnp::about);

		// effects
		connect(ui->actionGrayscale, &QAction::triggered,
		        image, &DrawCore::grayscale);
		connect(ui->actionNegative, &QAction::triggered,
		        image, &DrawCore::negative);
	}

	/*
	 * toolBar
	 */
	{
		connect(image, &DrawCore::parserMsg,
		        statusLine, &QLineEdit::setText);

		connect(newFileButton, &QToolButton::clicked,
		        this, &Qtnp::newFile);
		connect(gridButton, &QToolButton::clicked,
		        this, &Qtnp::drawGrid);
		connect(graphicButton, &QToolButton::clicked,
		        this, &Qtnp::drawGraphic);
		connect(prevButton, &QToolButton::clicked,
		        image, &DrawCore::prev);
		connect(stickyDrawCheckBox, &QCheckBox::toggled,
		        image, &DrawCore::setSticky);

		connect(penWidget, &ColorWidget::sendColor,
		        image, &DrawCore::setPenColor);
		connect(rpenWidget, &ColorWidget::sendColor,
		        image, &DrawCore::setRPenColor);

		connect(changePensButton, &QToolButton::clicked,
		        this, &Qtnp::swapPens);
		// Qt5 crutch
		void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;
		connect(thicksessBox, signal,
		        image, &DrawCore::setThickness);
		connect(fullscreenButton, &QToolButton::clicked,
		        this, &Qtnp::fullScreen);
	}


	/*
	 * Tools menu actions
	 */
	{
		// Implemented in constructor
	}

	connect(image, &DrawCore::resetToolMenu,
	        this, &Qtnp::setTool_NONE);
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
		ui->toolBar->addWidget(gridButton);
		ui->toolBar->addWidget(graphicButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(prevButton);
		ui->toolBar->addWidget(toolsButton);
		ui->toolBar->addWidget(stickyDrawCheckBox);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(penWidget);
		ui->toolBar->addWidget(rpenWidget);
		ui->toolBar->addWidget(changePensButton);
		ui->toolBar->addWidget(thicksessBox);
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
	if(_openedFileLocation == "0") {
		saveFileBecause(tr("Where to save?"));
	} else {
		image->saveImage(_openedFileLocation);
		statusLine->setText(tr("Save completed"));
	}
	statusLine->setText(tr("Save earlier"));
}

void Qtnp::saveAs()
{
	saveFileBecause(tr("Save current image as..."));
}

void Qtnp::exit()
{
	this->close();
}

void Qtnp::fullScreen()
{
	if (!this->isFullScreen())
		this->showFullScreen();
	else this->showNormal();
}

void Qtnp::swapPens()
{
}

void Qtnp::saveFileBecause(QString reason)
{
	QFileDialog::Options options;
	QString filter;
	options |= QFileDialog::DontUseNativeDialog;
	QString fileName = QFileDialog::getSaveFileName(
	                           this, reason,
	                           "",
	                           tr("*.png;;*.xbm;;*.xpm"),
	                           &filter,
	                           options
	                           );
	if(!fileName.isEmpty()) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		int length(filter.size());
		for(int i(length - 1); i > 0; i--) {
			if(filter[i] != fileName[fileName.size() - length + i]) {
				fileName += filter.mid(1);
				break;
			}
		}
		image->saveImage(fileName);
		statusLine->setText(tr("Save completed"));
		_openedFileLocation = fileName;
		QApplication::restoreOverrideCursor();
	}
}

void Qtnp::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image..."));
	if (!fileName.isEmpty()) {
		image->loadImage(fileName);
		statusLine->setText(tr("Image openned!"));
		image->resize(image->pixmap()->size());
		_openedFileLocation = fileName;
	} else {
		statusLine->setText(tr("Can't open Image!"));
	}
}

void Qtnp::drawGrid()
{
}

void Qtnp::setTool_NONE()
{
	toolsButton->setIcon(QIcon(":/resources/cursor.png"));
	image->setActiveTool(NONE);
}

void Qtnp::setTool_PEN()
{
	toolsButton->setIcon(QIcon(":/resources/pencil_ico.png"));
	image->setActiveTool(PEN);
}

void Qtnp::setTool_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/line_ico.png"));
	image->setActiveTool(LINE);
}

void Qtnp::setTool_SQUARE()
{
	image->setActiveTool(SQUARE);
}

void Qtnp::setTool_ELLIPSE()
{
	image->setActiveTool(ELLIPSE);
}

void Qtnp::setTool_CIRCLE()
{
	toolsButton->setIcon(QIcon(":/resources/circle.png"));
	image->setActiveTool(CIRCLE);
}

void Qtnp::setTool_JOGGED_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/jogged_ico.png"));
	image->setActiveTool(JOGGED_LINE);
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
	if (image->isModified()) {
		int r = QMessageBox::warning(this, tr("Qtnp"),
		                tr("The image has been modified.\n"
		                   "Do you want to save your changes?"),
		                QMessageBox::Yes | QMessageBox::Default,
		                QMessageBox::No,
		                QMessageBox::Cancel | QMessageBox::Escape);
		if (r == QMessageBox::Yes) {
			saveAs();
			event->accept();
		} else if (r == QMessageBox::Cancel) {
			event->ignore();
			return;
		}
		event->accept();
	} else event->accept();
}