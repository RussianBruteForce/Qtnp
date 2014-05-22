#include "DrawGraphicDialog.h"
#include "ui_DrawGraphicDialog.h"

DrawGraphicDialog::DrawGraphicDialog(Settings &_s, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DrawGraphicDialog)
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":/resources/graphic.png"));
	s = &_s;

	graphicColor = new ColorWidget(s->graphicColor());
	ui->propLayout->addWidget(graphicColor);
	graphicThickness = new QSpinBox(this);
	graphicThickness->setRange(1, 9999);
	graphicThickness->setValue(s->graphicThickness());
	ui->propLayout->addWidget(graphicThickness);

}

DrawGraphicDialog::~DrawGraphicDialog()
{
	delete ui;
	delete graphicColor;
}

void DrawGraphicDialog::insert(QString t)
{
	auto p = ui->formula->cursorPosition();
	ui->formula->insert(t);
	ui->formula->setCursorPosition(p+t.size());
}

void DrawGraphicDialog::insertF(QString t)
{
	auto p = ui->formula->cursorPosition();
	ui->formula->insert(t + QString("()"));
	ui->formula->setCursorPosition(p+t.size()+1);
}

void DrawGraphicDialog::on_zero_clicked()
{
	insert("0");
}

void DrawGraphicDialog::on_one_clicked()
{
	insert("1");
}

void DrawGraphicDialog::on_two_clicked()
{
	insert("2");
}

void DrawGraphicDialog::on_three_clicked()
{
	insert("3");
}

void DrawGraphicDialog::on_four_clicked()
{
	insert("4");
}

void DrawGraphicDialog::on_five_clicked()
{
	insert("5");
}

void DrawGraphicDialog::on_six_clicked()
{
	insert("6");
}

void DrawGraphicDialog::on_seven_clicked()
{
	insert("7");
}

void DrawGraphicDialog::on_eight_clicked()
{
	insert("8");
}

void DrawGraphicDialog::on_nine_clicked()
{
	insert("9");
}

void DrawGraphicDialog::on_div_clicked()
{
	insert("/");
}

void DrawGraphicDialog::on_mult_clicked()
{
	insert("*");
}

void DrawGraphicDialog::on_minus_clicked()
{
	insert("-");
}

void DrawGraphicDialog::on_plus_clicked()
{
	insert("+");
}

void DrawGraphicDialog::on_pi_clicked()
{
	insert("_pi");
}

void DrawGraphicDialog::on_pi_3_clicked()
{
	insert("_pi/3");
}

void DrawGraphicDialog::on_pi_4_clicked()
{
	insert("_pi/4");
}

void DrawGraphicDialog::on_pi_6_clicked()
{
	insert("_pi/6");
}

void DrawGraphicDialog::on_sin_clicked()
{
	insertF("sin");
}

void DrawGraphicDialog::on_cos_clicked()
{
	insertF("cos");
}

void DrawGraphicDialog::on_tan_clicked()
{
	insertF("tan");
}

void DrawGraphicDialog::on_ctg_clicked()
{
	insertF("(1/tan");
	insert(")");
	ui->formula->setCursorPosition(ui->formula->cursorPosition()-1);
}

void DrawGraphicDialog::on_asin_clicked()
{
	insertF("asin");
}

void DrawGraphicDialog::on_acos_clicked()
{
	insertF("acos");
}

void DrawGraphicDialog::on_atan_clicked()
{
	insertF("atan");
}

void DrawGraphicDialog::on_sqrt_clicked()
{
	insertF("sqrt");
}

void DrawGraphicDialog::on_min_clicked()
{
	insertF("min");
}

void DrawGraphicDialog::on_max_clicked()
{
	insertF("max");
}

void DrawGraphicDialog::on_sum_clicked()
{
	insertF("sum");
}

void DrawGraphicDialog::on_abs_clicked()
{
	insertF("abs");
}

void DrawGraphicDialog::on_and__clicked()
{
	insert(" && ");
}

void DrawGraphicDialog::on_or__clicked()
{
	insert(" || ");
}

void DrawGraphicDialog::on_if_else_clicked()
{
	insert(" ? : ");
}

void DrawGraphicDialog::on_assign__clicked()
{
	insert("=");
}

void DrawGraphicDialog::on_greater_clicked()
{
	insert(">");
}

void DrawGraphicDialog::on_less_clicked()
{
	insert("<");
}

void DrawGraphicDialog::on_notEqual_clicked()
{
	insert("!=");
}

void DrawGraphicDialog::on_pow_clicked()
{
	insert("^");
}

void DrawGraphicDialog::on_cursorLeft_clicked()
{
	ui->formula->setCursorPosition(ui->formula->cursorPosition()-1);
}

void DrawGraphicDialog::on_cursorRight_clicked()
{
	ui->formula->setCursorPosition(ui->formula->cursorPosition()+1);
}

void DrawGraphicDialog::on_delRight_clicked()
{
	ui->formula->del();
}

void DrawGraphicDialog::on_delLeft_clicked()
{
	ui->formula->backspace();
}

void DrawGraphicDialog::on_komma_clicked()
{
	insert(", ");
}

void DrawGraphicDialog::on_dot_clicked()
{
	insert(".");
}

void DrawGraphicDialog::on_bracketLeft_clicked()
{
	insert("(");
}

void DrawGraphicDialog::on_bracketRight_clicked()
{
	insert(")");
}

void DrawGraphicDialog::on_X_clicked()
{
	insert("x");
}

void DrawGraphicDialog::on_undo_clicked()
{
	ui->formula->undo();
}

void DrawGraphicDialog::on_redo_clicked()
{
	ui->formula->redo();
}

void DrawGraphicDialog::on_clear_clicked()
{
	ui->formula->clear();
}

void DrawGraphicDialog::on_draw_clicked()
{
	if (!ui->formula->text().isEmpty()) {
		emit drawGraphic(ui->formula->text(),
		                 graphicColor->color(),
		                 graphicThickness->value());
	} else {
		this->setDisabled(true);
		QMessageBox::warning(this, tr("Graphic"),
		                     tr("The formula is empty!\n"
		                        "Write it or click CANCEL."),
		                     QMessageBox::Ok | QMessageBox::Default);
		this->setEnabled(true);
	}
}

void DrawGraphicDialog::on_buttonBox_accepted()
{
	if (!ui->formula->text().isEmpty()) {
		emit drawGraphic(ui->formula->text(),
		                 graphicColor->color(),
		                 graphicThickness->value());
		this->accept();
	} else {
		this->setDisabled(true);
		QMessageBox::warning(this, tr("Graphic"),
		                     tr("The formula is empty!\n"
		                        "Write it or click CANCEL."),
		                     QMessageBox::Ok | QMessageBox::Default);
		this->setEnabled(true);
	}
}

void DrawGraphicDialog::on_buttonBox_rejected()
{
	this->reject();
}
