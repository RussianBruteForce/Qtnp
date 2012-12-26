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

#include "DigitalClock.h"

DigitalClock::DigitalClock(QWidget *parent)
        : QLCDNumber(parent)
{
	setSegmentStyle(Filled);

	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
	timer->start(1000);

	showTime();

	setWindowTitle(tr("Digital Clock"));
	resize(100, 33);
}

void DigitalClock::showTime()
{
	QTime time = QTime::currentTime();
	QString text = time.toString("hh:mm");
	if ((time.second() % 2) == 0)
		text[2] = ' ';
	display(text);
}
