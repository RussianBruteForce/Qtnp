#include "Qtnp.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/resources/splash.png"));
	splash->show();

	Qt::Alignment bottomLeft = Qt::AlignBottom | Qt::AlignLeft;

	splash->showMessage(QObject::tr("Setting up the main window..."),
	                    bottomLeft, Qt::black);


//	QTranslator translator;
//	if (QLocale::system().name().left(2) == "ru") {
//		translator.load(":/res/qtnp_ru"); // русский/russian
//		qApp->installTranslator(&translator);
//	}

	Qtnp w; // main window

	splash->showMessage(QObject::tr("Making SIGNAL->SLOT connections..."),
	                    bottomLeft, Qt::black);
	w.makeConnections();

	w.show();

	splash->deleteLater();

	return a.exec();
}
