#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(Settings &_s, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/resources/settings.png"));
	s = &_s;

	bg = new ColorWidget(s->bgColor());
	ui->bgL->addWidget(bg);

	graphic = new ColorWidget(s->graphicColor());
	ui->graphicL->addWidget(graphic);

	grid = new ColorWidget(s->gridColor());
	ui->gridL->addWidget(grid);

	cp = new ColorWidget(s->cpColor());
	ui->cpL->addWidget(cp);

	penColor = new ColorWidget(s->penColor());
	ui->penColorL->addWidget(penColor);

	rpenColor = new ColorWidget(s->rpenColor());
	ui->rpenColorL->addWidget(rpenColor);

	ui->language->addItem("English");
	ui->language->addItem("Russian");

	setupTemplates();

	this->updateUI();

	connect(ui->saveB, &QPushButton::clicked,
	        this, &SettingsDialog::save);
	connect(ui->restoreDefaultsB, &QPushButton::clicked,
	        this, &SettingsDialog::restoreDefaults);
	connect(ui->setPresentationDir, &QPushButton::clicked,
	        this, &SettingsDialog::setPresentationDir);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::setupTemplates()
{
	for (auto &i: *s->templates())
		addTemplate(i, "");
}

void SettingsDialog::addTemplate(QPoint resolution, QString addon)
{
	QString str;
	str += QString::number(resolution.x());
	str += 'x';
	str += QString::number(resolution.y());
	str += ' ';
	ui->templatesCB->addItem(
		QIcon(":/resources/template.png"),
		str + addon,
		resolution);
}

void SettingsDialog::save()
{
	s->setBgColor(bg->color());
	s->setGraphicColor(graphic->color());
	s->setGridColor(grid->color());
	s->setCpColor(cp->color());
	s->setPenColor(penColor->color());
	s->setRpenColor(rpenColor->color());

	s->setThickness(ui->penT->value());
	s->setGraphicThickness(ui->graphicT->value());
	s->setGridThickness(ui->gridT->value());
	s->setCpThickness(ui->cpT->value());

	s->setGridStep(ui->gridS->value());
	s->setCpStep(ui->cpS->value());

	s->setNumbersOpacity(ui->cpNumbersO->value());

	s->setSyncCPToGrid(ui->sync->isChecked());
	s->setAutoPresentation(ui->autoPresentation->isChecked());
	s->setReverseToolBar(ui->reverse->isChecked());
	s->setFullscreen(ui->fullscreen->isChecked());

	if (ui->language->currentIndex() == 0)
		s->setLanguage("en");
	else
		if (ui->language->currentIndex() == 1)
			s->setLanguage("ru");

	s->setImageTemplate(ui->templatesCB->currentIndex());

	s->setPresentationDirectory(ui->presentationDir->text());

	this->accept();
}

void SettingsDialog::updateUI()
{
	bg->setColor(s->bgColor());
	graphic->setColor(s->graphicColor());
	grid->setColor(s->gridColor());
	cp->setColor(s->cpColor());

	ui->penT->setValue(s->thickness());
	ui->graphicT->setValue(s->graphicThickness());
	ui->gridT->setValue(s->gridThickness());
	ui->cpT->setValue(s->cpThickness());

	ui->gridS->setValue(s->gridStep());
	ui->cpS->setValue(s->cpStep());

	ui->cpNumbersO->setValue(s->numbersOpacity());

	ui->reverse->setChecked(s->reverseToolBar());
	ui->sync->setChecked(s->syncCPToGrid());
	ui->autoPresentation->setChecked(s->autoPresentation());
	ui->fullscreen->setChecked(s->fullscreen());

	if (s->language() == "en")
		ui->language->setCurrentIndex(0);
	else if (s->language() == "ru")
		ui->language->setCurrentIndex(1);

	ui->templatesCB->setCurrentIndex(s->imageTemplate());
	ui->presentationDir->setText(s->presentationDirectory());

}

void SettingsDialog::restoreDefaults()
{
	s->restoreDefaults();
	this->updateUI();
}

void SettingsDialog::setPresentationDir()
{
	ui->presentationDir->setText(
	                        QFileDialog::getExistingDirectory(this, tr("Open Directory"),
	                                                          ui->presentationDir->text(),
	                                                          QFileDialog::ShowDirsOnly
	                                                          | QFileDialog::DontResolveSymlinks)
	                        );
}
