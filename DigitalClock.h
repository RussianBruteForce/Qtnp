#ifndef DigitalClock_H
#define DigitalClock_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class DigitalClock : public QLCDNumber
{
	Q_OBJECT

public:
	DigitalClock(QWidget *parent = 0);

private slots:
	void showTime();
};

#endif // DigitalClock_H
