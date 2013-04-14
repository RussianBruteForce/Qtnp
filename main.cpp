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

#include <QApplication>
#include <QSplashScreen>
#include <QTranslator>
#include <ostream>

#include "Qtnp.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QString argOpen;
	QStringList args = a.arguments();
	for (int i = 0; i < args.size(); i++) {
		if (args.at(i) == "-v" || args.at(i) == "--version" ) {
			std::cout << "Qtnp version: " << VERSION << std::endl;
			return 0;
		} else if (i > 0) {
			argOpen = args.at(i);
		}
	}

	QPixmap pixmap(":/resources/splash.png");
	QSplashScreen *splash = new QSplashScreen(pixmap);
	splash->show();
	Qt::Alignment bottomLeft = Qt::AlignBottom | Qt::AlignLeft;
	splash->showMessage(QObject::tr("Setting up the main window..."),
	                    bottomLeft, Qt::black);

	QCoreApplication::setOrganizationName("qtnp"); // FOR
	QCoreApplication::setApplicationName("qtnp");  //     CONFIG

	QTranslator translator;
	Settings *s = new Settings;
	if (s->language() == "ru") {
		translator.load(":/resources/ru_RU.qm"); // русский/russian
		qApp->installTranslator(&translator);
	}

	Qtnp w(*s);

	splash->showMessage(QObject::tr("Making UI..."),
	                    bottomLeft, Qt::black);
	w.makeUI();

	splash->showMessage(QObject::tr("Prepare presentation..."),
	                    bottomLeft, Qt::black);
	w.preparePresentation();

	splash->showMessage(QObject::tr("Making SIGNAL->SLOT connections..."),
	                    bottomLeft, Qt::black);
	w.makeConnections();

	splash->showMessage(QObject::tr("Loading Toolbar..."),
	                    bottomLeft, Qt::black);
	w.loadToolbar(w.s->reverseToolBar());

	if (!argOpen.isNull()) w.image->loadImage(argOpen);
	w.show();
	splash->finish(&w);
	delete splash;
	return a.exec();
}
