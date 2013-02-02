#include "DrawGCPDialog.h"
#include "ui_DrawGCPDialog.h"

DrawGCPDialog::DrawGCPDialog(Settings &_s, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DrawGCPDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/resources/grid.png"));

	gcp = new GCPWidget(_s, this);
	ui->layout->addWidget(gcp);

	connect(ui->buttonBox, &QDialogButtonBox::accepted,
	        gcp, &GCPWidget::askData);
}

DrawGCPDialog::~DrawGCPDialog()
{
	delete ui;
}
