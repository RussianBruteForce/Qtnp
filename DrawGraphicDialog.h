#ifndef DRAWGRAPHICDIALOG_H
#define DRAWGRAPHICDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QMessageBox>

#include "Settings.h"
#include "ColorWidget.h"

namespace Ui {
class DrawGraphicDialog;
}

class DrawGraphicDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit DrawGraphicDialog(Settings &_s, QWidget *parent = 0);
	~DrawGraphicDialog();
	
private slots:
	void on_zero_clicked();
	void on_one_clicked();
	void on_two_clicked();
	void on_three_clicked();
	void on_four_clicked();
	void on_five_clicked();
	void on_six_clicked();
	void on_seven_clicked();
	void on_eight_clicked();
	void on_nine_clicked();
	void on_div_clicked();
	void on_mult_clicked();
	void on_minus_clicked();
	void on_plus_clicked();
	void on_pi_clicked();
	void on_pi_3_clicked();
	void on_pi_4_clicked();
	void on_pi_6_clicked();
	void on_sin_clicked();
	void on_cos_clicked();
	void on_tan_clicked();
	void on_ctg_clicked();
	void on_asin_clicked();
	void on_acos_clicked();
	void on_atan_clicked();
	void on_sqrt_clicked();
	void on_min_clicked();
	void on_max_clicked();
	void on_sum_clicked();
	void on_abs_clicked();
	void on_and__clicked();
	void on_or__clicked();
	void on_if_else_clicked();
	void on_assign__clicked();
	void on_greater_clicked();
	void on_less_clicked();
	void on_notEqual_clicked();
	void on_pow_clicked();
	void on_cursorLeft_clicked();
	void on_cursorRight_clicked();
	void on_delRight_clicked();
	void on_delLeft_clicked();
	void on_komma_clicked();
	void on_dot_clicked();
	void on_bracketLeft_clicked();
	void on_bracketRight_clicked();
	void on_X_clicked();
	void on_undo_clicked();
	void on_redo_clicked();
	void on_clear_clicked();
	void on_draw_clicked();
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	Ui::DrawGraphicDialog *ui;
	Settings *s;
	ColorWidget *graphicColor;
	QSpinBox *graphicThickness;
	void insert(QString t);
	void insertF(QString t);

signals:
	void drawGraphic(QString str, QColor color, int width);
};

#endif // DRAWGRAPHICDIALOG_H
