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

#include "Qtnp.h"
#include "ui_Qtnp.h"

#include "QDebug"

Qtnp::Qtnp(Settings &settings, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Qtnp)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/resources/icon.png"));

	s = &settings;
}

Qtnp::~Qtnp()
{
	delete ui;
	delete image;
	delete rpenColor;
	delete penColor;
}

void Qtnp::makeConnections()
{
	/*
	 * Menu actions:
	 */
	{
		// file
		connect(ui->actionNew, &QAction::triggered,
		        this, &Qtnp::newFile);
		connect(ui->actionOpen, &QAction::triggered,
		        this, &Qtnp::openFile);
		connect(ui->actionSave, &QAction::triggered,
		        this, &Qtnp::save);
		connect(ui->actionSave_as, &QAction::triggered,
		        this, &Qtnp::saveAs);
		connect(ui->actionSettings, &QAction::triggered,
		        this, &Qtnp::settings);
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
		connect(image, &DrawCore::drawError,
		        statusLine, &QLineEdit::setText);

		connect(newFileButton, &QToolButton::clicked,
		        this, &Qtnp::newFile);
		connect(gridButton, &QToolButton::clicked,
		        this, &Qtnp::drawGCP);
		connect(graphicButton, &QToolButton::clicked,
		        this, &Qtnp::drawGraphic);
		connect(prevButton, &QToolButton::clicked,
		        image, &DrawCore::undo);
		connect(stickyDraw, &QCheckBox::toggled,
		        image, &DrawCore::setSticky);

		connect(penColor, &ColorWidget::colorChanged,
		        image, &DrawCore::setPenColor);
		connect(rpenColor, &ColorWidget::colorChanged,
		        image, &DrawCore::setRPenColor);

		connect(changePensButton, &QToolButton::clicked,
		        this, &Qtnp::swapPens);
		// Qt5 crutch
		void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;
		connect(thicksessBox, signal,
		        image, &DrawCore::setThickness);
		connect(fullscreenButton, &QToolButton::clicked,
		        this, &Qtnp::fullScreen);

		connect(nImage, &QToolButton::clicked,
		        this, &Qtnp::nextImage);
		connect(pImage, &QToolButton::clicked,
		        this, &Qtnp::prevImage);
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

void Qtnp::makeUI()
{
	image = new DrawCore();
	auto p = s->templates()->at(s->imageTemplate());
	image->newImage(p.x(), p.y(), s->bgColor());
	clock = new DigitalClock(ui->toolBar);

	openedFileLocation = "0";

	rpenColor = new ColorWidget(s->rpenColor());
	image->setRPenColor(s->rpenColor());
	rpenColor->setToolTip(tr("Right pen color"));
	penColor = new ColorWidget(s->penColor());
	image->setPenColor(s->penColor());
	penColor->setToolTip(tr("Pen color"));

	thicksessBox = new QSpinBox(ui->toolBar);
	thicksessBox->setRange(1,200);
	thicksessBox->setValue(s->thickness());
	image->setThickness(s->thickness());

	nImage = new QToolButton(ui->toolBar);
	nImage->setToolButtonStyle(Qt::ToolButtonIconOnly);
	nImage->setIcon(QIcon(":/resources/arrow_right.png"));
	nImage->setToolTip(tr("Next image"));
	pImage = new QToolButton(ui->toolBar);
	pImage->setToolButtonStyle(Qt::ToolButtonIconOnly);
	pImage->setIcon(QIcon(":/resources/arrow_left.png"));
	pImage->setToolTip(tr("Previous image"));

	prevButton = new QToolButton(ui->toolBar);
	prevButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	prevButton->setIcon(QIcon(":/resources/prev.png"));
	prevButton->setToolTip(tr("Previous"));

	newFileButton = new QToolButton(ui->toolBar);
	newFileButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	newFileButton->setIcon(QIcon(":/resources/new.png"));
	newFileButton->setToolTip(tr("New"));

	gridButton = new QToolButton(ui->toolBar);
	gridButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	gridButton->setIcon(QIcon(":/resources/grid.png"));
	gridButton->setToolTip(tr("Grid"));

	graphicButton = new QToolButton(ui->toolBar);
	graphicButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	graphicButton->setIcon(QIcon(":/resources/graphic.png"));
	graphicButton->setToolTip(tr("Graphic"));

	changePensButton = new QToolButton(ui->toolBar);
	changePensButton->setIcon(QIcon(":/resources/change_pens_ico.png"));
	changePensButton->setToolTip(tr("Swap pens"));

	fullscreenButton = new QToolButton(ui->toolBar);
	fullscreenButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	fullscreenButton->setIcon(QIcon(":/resources/fullscreen.png"));
	fullscreenButton->setToolTip(tr("Fullscreen"));

	stickyDraw = new QCheckBox(ui->toolBar);
	stickyDraw->setToolTip(tr("Stick to web's points"));
	stickyDraw->setChecked(false);


	toolsMenu = new QMenu(this);
	toolsMenu->addAction(QIcon(":/resources/cursor.png"),tr("Cursor"),this,SLOT(setTool_NONE()));
	toolsMenu->addAction(QIcon(":/resources/line_ico.png"),tr("Line"),this,SLOT(setTool_LINE()));
	toolsMenu->addAction(QIcon(":/resources/circle.png"),tr("Circle"),this,SLOT(setTool_CIRCLE()));
	toolsMenu->addAction(QIcon(":/resources/jogged_ico.png"),tr("Jogged Line"),this,SLOT(setTool_JOGGED_LINE()));
	toolsMenu->addAction(QIcon(":/resources/pencil_ico.png"),tr("Pen"),this,SLOT(setTool_PEN()));
	toolsMenu->addAction(QIcon(":/resources/fill_ico.png"),tr("Fill"),this,SLOT(setTool_FILL()));
	toolsMenu->setToolTip(tr("Tools"));

	toolsButton = new QToolButton(ui->toolBar);
	toolsButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
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

	// Icons to menu
	ui->actionFullscreen->setIcon(QIcon(":/resources/fullscreen.png"));
	ui->actionNew->setIcon(QIcon(":/resources/new.png"));
	ui->actionOpen->setIcon(QIcon(":/resources/open.png"));
	ui->actionExit->setIcon(QIcon(":/resources/exit.png"));
	ui->actionSave->setIcon(QIcon(":/resources/save.png"));
	ui->actionSettings->setIcon(QIcon(":/resources/settings.png"));
	ui->actionAbout_Qtnp->setIcon(QIcon(":/resources/about.png"));
	ui->menuTheme->setIcon(QIcon(":/resources/themes.png"));
	ui->menuFile->setIcon(QIcon(":/resources/file.png"));
}

void Qtnp::loadToolbar(bool reverse)
{
	auto *spacerWidget = new QWidget(this);
	spacerWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spacerWidget->setVisible(true);

	ui->toolBar->setMovable(false);

	if (!reverse) {
		statusLine->setAlignment(Qt::AlignLeft);
		statusLine->setText(tr("Toolbar loaded"));
		ui->toolBar->addWidget(statusLine);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(pImage);
		ui->toolBar->addWidget(nImage);
		ui->toolBar->addSeparator();
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
		ui->toolBar->addWidget(stickyDraw);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(penColor);
		ui->toolBar->addWidget(rpenColor);
		ui->toolBar->addWidget(changePensButton);
		ui->toolBar->addWidget(thicksessBox);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(fullscreenButton);
	} else {
		ui->toolBar->addWidget(fullscreenButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(changePensButton);
		ui->toolBar->addWidget(rpenColor);
		ui->toolBar->addWidget(penColor);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(stickyDraw);
		ui->toolBar->addWidget(toolsButton);
		ui->toolBar->addWidget(prevButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(graphicButton);
		ui->toolBar->addWidget(gridButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(newFileButton);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(clock);
		ui->toolBar->addWidget(spacerWidget);
		ui->toolBar->addSeparator();
		ui->toolBar->addWidget(pImage);
		ui->toolBar->addWidget(nImage);
		ui->toolBar->addSeparator();
		statusLine->setAlignment(Qt::AlignRight);
		statusLine->setText(tr("Reverse toolbar loaded"));
		ui->toolBar->addWidget(statusLine);
	}
}

void Qtnp::preparePresentation()
{
	currentPresentationImage = -1;
	pImage->setDisabled(true);
	auto *d = new QDir(s->presentationDirectory());
	QStringList nf;
	nf += "*.png";
	nf += "*.jpg";
	nf += "*.bmp";
	presentationImages = d->entryList(nf ,QDir::Files, QDir::Name);
	if (presentationImages.isEmpty())
		nImage->setDisabled(true);
	else {
		nImage->setEnabled(true);
		if (s->autoPresentation()) {
			nextImage();
		}
	}
	delete d;
}


void Qtnp::newFile()
{
	this->setCursor(Qt::WaitCursor);
	this->setDisabled(true);

	nfd = new NewFileDialog(*s, this, ui->toolBar->height());
	connect(nfd, &NewFileDialog::newImage,
	        image, &DrawCore::newImage);
	connect(nfd->gcp, &GCPWidget::drawGrid,
	        image, &DrawCore::drawGrid);
	connect(nfd->gcp, &GCPWidget::drawCoordinatePlane,
	        image, &DrawCore::drawCoordPlane);

	nfd->exec();
	nfd->deleteLater();

	this->setEnabled(true);
	this->setCursor(Qt::ArrowCursor);
}

void Qtnp::save()
{
	if (image->isModified()) {
		if(openedFileLocation == "0")
			saveAs();
		else {
			if (image->saveImage(openedFileLocation))
				statusLine->setText(tr("Image saved as ") + openedFileLocation);
			else    statusLine->setText(tr("Couldn't save image as ") + openedFileLocation);
		}
	} else statusLine->setText(tr("Saved earlier"));
}

void Qtnp::saveAs()
{
	QString fileName;
	auto formats = tr("*.png;;*.xbm;;*.xpm;;*.bmp;;*.jpg;;*.jpeg;;*.ppm");
	if(openedFileLocation == "0")
		fileName = QFileDialog::getSaveFileName(
		                           this, tr("Save new image as..."),
		                           QDir::homePath(),
		                           formats
		                           );
	else
		fileName = QFileDialog::getSaveFileName(
		                           this, tr("Save image as..."),
					   openedFileLocation,
		                           formats
		                           );

	if(!fileName.isEmpty()) {
		this->setCursor(Qt::WaitCursor);
		this->setDisabled(true);

		if (image->saveImage(fileName)) {
			openedFileLocation = fileName;
			statusLine->setText(tr("Image saved as ") + fileName);
		} else
			statusLine->setText(tr("Couldn't save image as ") + fileName);

		this->setEnabled(true);
		this->setCursor(Qt::ArrowCursor);
	}
}

void Qtnp::exit()
{
	this->close();
}

void Qtnp::fullScreen()
{
	if (!this->isFullScreen()) {
		this->showFullScreen();
		ui->menuBar->setVisible(false);
		fullscreenButton->setIcon(QIcon(":/resources/normal.png"));
	}
	else {
		this->showNormal();
		ui->menuBar->setVisible(true);
		fullscreenButton->setIcon(QIcon(":/resources/fullscreen.png"));
	}
}

void Qtnp::swapPens()
{
	auto buf = this->penColor->color();
	penColor->setColor(this->rpenColor->color());
	rpenColor->setColor(buf);
}

void Qtnp::openFile()
{
	auto fileName = QFileDialog::getOpenFileName(this, tr("Open Image..."),
	                                                QDir::homePath(),
	                                                tr("Image Files (*.png *.jpg *.jpeg *.bmp *.xpm *.xbm *.gif *.pbm *.pgm *.ppm)"));
	if (!fileName.isEmpty()) {
		if (image->loadImage(fileName)) {
			statusLine->setText(tr("Image openned!"));
			image->resize(image->pixmap()->size());
			openedFileLocation = fileName;
		} else
			statusLine->setText(tr("Couldn't open image ") + fileName);
	}
}

void Qtnp::drawGCP()
{
	this->setCursor(Qt::WaitCursor);
	this->setDisabled(true);

	gcpd = new DrawGCPDialog(*s, this);
	connect(gcpd->gcp, &GCPWidget::drawGrid,
	        image, &DrawCore::drawGrid);
	connect(gcpd->gcp, &GCPWidget::drawCoordinatePlane,
	        image, &DrawCore::drawCoordPlane);

	gcpd->exec();
	gcpd->deleteLater();

	this->setEnabled(true);
	this->setCursor(Qt::ArrowCursor);
}

void Qtnp::drawGraphic()
{
	this->setCursor(Qt::WaitCursor);
	this->setDisabled(true);

	gd = new DrawGraphicDialog(*s, this);
	connect(gd, &DrawGraphicDialog::drawGraphic,
	        image, &DrawCore::drawGraphic);

	gd->exec();
	gd->deleteLater();

	this->setEnabled(true);
	this->setCursor(Qt::ArrowCursor);
}

void Qtnp::settings()
{
	this->setCursor(Qt::WaitCursor);
	this->setDisabled(true);

	sd = new SettingsDialog(*s, this);

	sd->exec();
	sd->deleteLater();

	preparePresentation();

	this->setEnabled(true);
	this->setCursor(Qt::ArrowCursor);
}

void Qtnp::setTool_NONE()
{
	toolsButton->setIcon(QIcon(":/resources/cursor.png"));
	image->setActiveTool(DrawTool::NONE);
}

void Qtnp::setTool_PEN()
{
	toolsButton->setIcon(QIcon(":/resources/pencil_ico.png"));
	image->setActiveTool(DrawTool::PEN);
}

void Qtnp::setTool_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/line_ico.png"));
	image->setActiveTool(DrawTool::LINE);
}

void Qtnp::setTool_SQUARE()
{
	image->setActiveTool(DrawTool::SQUARE);
}

void Qtnp::setTool_ELLIPSE()
{
	image->setActiveTool(DrawTool::ELLIPSE);
}

void Qtnp::setTool_CIRCLE()
{
	toolsButton->setIcon(QIcon(":/resources/circle.png"));
	image->setActiveTool(DrawTool::CIRCLE);
}

void Qtnp::setTool_JOGGED_LINE()
{
	toolsButton->setIcon(QIcon(":/resources/jogged_ico.png"));
	image->setActiveTool(DrawTool::JOGGED_LINE);
}

void Qtnp::setTool_FILL()
{
	toolsButton->setIcon(QIcon(":/resources/fill_ico.png"));
	image->setActiveTool(DrawTool::FILL);
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
					   "<br>"
					   "&nbsp; Icons by <a href=\"http://icomoon.io\">icomoon.io</a> under <a href=\"http://creativecommons.org/licenses/by/3.0\">CC BY 3.0</a>"
					   ));
}

void Qtnp::wrongExp()
{
	this->setDisabled(true);
	QMessageBox::warning(this, tr("WRONG EXPRESSION"),
	                     tr("Wrong expression!\n"
	                        "It's can't be drawn"),
	                     QMessageBox::Ok);
	this->setEnabled(true);
}

void Qtnp::nextImage()
{
	if (currentPresentationImage + 1 < presentationImages.size())
		image->loadImage(QString(s->presentationDirectory() + "/")
				 +
				 presentationImages.at(
					 ++currentPresentationImage));

	if (currentPresentationImage + 1 == presentationImages.size())
		nImage->setDisabled(true);
	else
		nImage->setEnabled(true);

	if (currentPresentationImage == 0)
		pImage->setDisabled(true);
	else
		pImage->setEnabled(true);
}

void Qtnp::prevImage()
{
	if (currentPresentationImage > 0)
		image->loadImage(QString(s->presentationDirectory() + "/") + presentationImages.at(--currentPresentationImage));
	if (currentPresentationImage == 0)
		pImage->setDisabled(true);
	else pImage->setEnabled(true);
	if (currentPresentationImage + 1 == presentationImages.size())
		nImage->setDisabled(true);
	else nImage->setEnabled(true);
}

void Qtnp::closeEvent(QCloseEvent *event)
{
	if (image->isModified()) {
		this->setDisabled(true);
		int r = QMessageBox::warning(this, tr("Qtnp"),
		                tr("The image has been modified.\n"
		                   "Do you want to save your changes?"),
		                QMessageBox::Yes | QMessageBox::Default,
		                QMessageBox::No,
		                QMessageBox::Cancel | QMessageBox::Escape);
		this->setEnabled(true);

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
