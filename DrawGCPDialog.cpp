#include "DrawGCPDialog.h"
#include "ui_DrawGCPDialog.h"

DrawGCPDialog::DrawGCPDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DrawGCPDialog)
{
	ui->setupUi(this);

	gcp = new GCPWidget(this);
	ui->layout->addWidget(gcp);

	connect(ui->buttonBox, &QDialogButtonBox::accepted,
	        gcp, &GCPWidget::askData);
}

DrawGCPDialog::~DrawGCPDialog()
{
	delete ui;
}
