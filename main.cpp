#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDir>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QApplication a(argc, argv);

    QTranslator *qtTrans = new QTranslator;
    qtTrans->load("qt_"+QLocale::system().name(),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(qtTrans);

    QTranslator *translator = new QTranslator;
    QString fileTr = QApplication::applicationDirPath()+
            QDir::separator()+"translations"+QDir::separator()+QLocale::system().name();
    if(!translator->load(fileTr))
        qApp->exit();
    else
        qApp->installTranslator(translator);

#ifdef Q_OS_WIN32
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM866"));
#endif

    MainWindow w;

    if(argc > 1){
        if(argv[1] == (char*)"MINIMIZE") w.hide();
    } else {
        w.show();
    }

    return a.exec();
}
