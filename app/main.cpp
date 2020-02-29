#include <qglobal.h>

#include <widgets/MainWindow.h>

#include <QApplication>

int main( int argc, char* argv[] ) {
    Q_INIT_RESOURCE( resources );

    QApplication a( argc, argv );
    QApplication::setAttribute( Qt::AA_DisableWindowContextHelpButton );

    MainWindow w;
    w.show();

    return a.exec();
}
