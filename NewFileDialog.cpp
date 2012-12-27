#include "NewFileDialog.h"
#include "ui_NewFileDialog.h"

NewFileDialog::NewFileDialog(Settings &_s, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NewFileDialog)
{
	ui->setupUi(this);
	s = &_s;
	gcp = new GCPWidget(*s, this);
	gcp->makeDedicated();
	ui->GCPLayout->addWidget(gcp);

	backgroundColor = new ColorWidget(s->bgColor());
	ui->WHCLayout->addWidget(backgroundColor);

	setupTemplates();
	ui->templatesCB->setCurrentIndex(s->imageTemplate());
	setTemplate(s->imageTemplate());

	connect(ui->buttonBox, &QDialogButtonBox::accepted,
	        this, &NewFileDialog::draw);
	connect(ui->buttonBox, &QDialogButtonBox::rejected,
	        this, &NewFileDialog::reject);
	void (QComboBox:: *signal)(int) = &QComboBox::currentIndexChanged;
	connect(ui->templatesCB, signal,
	        this, &NewFileDialog::setTemplate);
}

NewFileDialog::~NewFileDialog()
{
	delete ui;
}

void NewFileDialog::setupTemplates()
{
	for (int i = 0; i < s->templates()->size(); i++) {
		addTemplate(s->templates()->at(i), "");
	}
}

void NewFileDialog::addTemplate(QPoint resolution, QString addon)
{
	QString str;
	str += QString::number(resolution.x());
	str += 'x';
	str += QString::number(resolution.y());
	str += ' ';
	ui->templatesCB->addItem(QIcon(":/resources/template.png"), str + addon, resolution);
}


void NewFileDialog::draw()
{
	emit newImage(ui->widthSB->value(), ui->heightSB->value(),
	              backgroundColor->color());
	gcp->askData();
	this->accept();
}

void NewFileDialog::setTemplate(int t)
{
	ui->widthSB->setValue(ui->templatesCB->itemData(t).toPoint().x());
	ui->heightSB->setValue(ui->templatesCB->itemData(t).toPoint().y());
}
