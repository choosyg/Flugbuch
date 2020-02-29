#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "FlightDialog.h"
#include "LocationDialog.h"
#include "PlaneDialog.h"

#include <core/persistence/sqlite/SqLiteStore.h>

#include <QFileDialog>
#include <QQuickItem>
#include <QSettings>

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    ui->flightList->setModel( &flm_ );
    ui->planeList->setModel( &plm_ );
    ui->locationList->setModel( &llm_ );
    ui->tabWidget->setCurrentIndex( 0 );

    ui->mapWidget->setSource( QUrl::fromLocalFile( "map.qml" ) );

    ui->toolBar->addAction( ui->actionCreateFlight );

    updateActions();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    auto filename = QFileDialog::getSaveFileName( this, tr( "Speichern" ), "", "*.log" );

    QFile file( filename );
    if( file.exists() ) {
        file.remove();
    }

    store_ = std::make_shared< persistence::sql::SqLiteStore >( filename, persistence::sql::SqLiteStore::Mode::Create );
    updateActions();
}

void MainWindow::on_actionOpen_triggered() {
    QSettings settings( "config.ini", QSettings::IniFormat );
    auto lastDir = settings.value( "LastDir", "" ).toString();

    auto filename = QFileDialog::getOpenFileName( this, tr( "Öffnen" ), lastDir, "*.log" );
    store_ = std::make_shared< persistence::sql::SqLiteStore >( filename );
    flm_.set( store_->flights() );
    plm_.set( store_->planes() );
    llm_.set( store_->locations() );
    updateActions();

    settings.setValue( "LastDir", QFileInfo( filename ).path() );
}

void MainWindow::on_actionSave_triggered() {
    store_->save();
}

void MainWindow::on_actionCreateFlight_triggered() {
    auto flight = std::make_shared< domain::Flight >();
    flight->setStartTime( QDateTime::currentDateTime() );
    flight->setEndTime( QDateTime::currentDateTime() );

    FlightDialog dlg( store_, flight, this );
    if( dlg.exec() == QDialog::Accepted ) {
        store_->upsert( flight );
        flm_.add( flight );
        plm_.set( store_->planes() );
        llm_.set( store_->locations() );
    }
}

void MainWindow::on_actionCreatePlane_triggered() {
    auto plane = std::make_shared< domain::Plane >();
    PlaneDialog dlg( plane, this );
    if( dlg.exec() == QDialog::Accepted ) {
        if( store_->upsert( plane ) ) {
            plm_.add( plane );
        }
    }
}

void MainWindow::on_actionCreateLocation_triggered() {
    auto loc = std::make_shared< domain::Location >();
    LocationDialog dlg( loc, this );
    if( dlg.exec() == QDialog::Accepted ) {
        if( store_->upsert( loc ) ) {
            llm_.add( loc );
        }
    }
}

void MainWindow::on_flightList_doubleClicked( const QModelIndex& index ) {
    auto flight = flm_.flight( index );
    FlightDialog dlg( store_, flight, this );
    dlg.exec();
    plm_.set( store_->planes() );
    llm_.set( store_->locations() );
}

void MainWindow::on_planeList_doubleClicked( const QModelIndex& index ) {
    auto plane = plm_.plane( index );
    PlaneDialog dlg( plane, this );
    dlg.exec();
}

void MainWindow::on_locationList_doubleClicked( const QModelIndex& index ) {
    auto loc = llm_.location( index );
    LocationDialog dlg( loc, this );
    dlg.exec();
}

void MainWindow::updateActions() {
    ui->actionSave->setEnabled( store_ != nullptr );
    ui->actionSaveAs->setEnabled( store_ != nullptr );

    ui->actionCreateFlight->setEnabled( store_ != nullptr );
    ui->actionCreatePlane->setEnabled( store_ != nullptr );
    ui->actionCreateLocation->setEnabled( store_ != nullptr );
}

void MainWindow::on_planeList_clicked( const QModelIndex& index ) {
}

void MainWindow::on_locationList_clicked( const QModelIndex& index ) {
    auto loc = llm_.location( index );
    auto c = loc->location();

    QVariant returnedValue;
    QMetaObject::invokeMethod( ui->mapWidget->rootObject(),
                               "setMapCenter",
                               Q_RETURN_ARG( QVariant, returnedValue ),
                               Q_ARG( QVariant, c.latitude() ),
                               Q_ARG( QVariant, c.longitude() ) );
}

void MainWindow::on_flightList_clicked( const QModelIndex& index ) {
    auto flight = flm_.flight( index );
    auto c1 = flight->startLocation()->location();
    auto c2 = flight->endLocation()->location();

    QVariant returnedValue;
    QMetaObject::invokeMethod( ui->mapWidget->rootObject(),
                               "showRoute",
                               Q_RETURN_ARG( QVariant, returnedValue ),
                               Q_ARG( QVariant, c1.latitude() ),
                               Q_ARG( QVariant, c1.longitude() ),
                               Q_ARG( QVariant, c2.latitude() ),
                               Q_ARG( QVariant, c2.longitude() ) );
}

void MainWindow::on_actionMapOsm_triggered() {
    ui->mapWidget->rootObject()->setProperty( "map", "osm" );
}

void MainWindow::on_actionMapEsri_triggered() {
    ui->mapWidget->rootObject()->setProperty( "map", "esri" );
}
