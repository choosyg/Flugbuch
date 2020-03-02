#include <qglobal.h>

#include <widgets/MainWindow.h>

#include <QApplication>
#include <QFile>

int main( int argc, char* argv[] ) {
    Q_INIT_RESOURCE( resources );

    QApplication a( argc, argv );
    QApplication::setAttribute( Qt::AA_DisableWindowContextHelpButton );

    QFile styleFile( ":/style.css" );
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    a.setStyleSheet( style );

    MainWindow w;
    w.show();

    return a.exec();
}
