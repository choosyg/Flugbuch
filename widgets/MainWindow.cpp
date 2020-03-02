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
    ui->flightList->setModel( &flightListModel_ );
    ui->planeList->setModel( &planeListModel_ );
    ui->locationList->setModel( &locationListModel_ );
    ui->tabWidget->setCurrentIndex( 0 );

    ui->mapWidget->setSource( QUrl::fromLocalFile( ":/widgets/map.qml" ) );

    updateActions();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    auto filename = QFileDialog::getSaveFileName( this, tr( "Speichern" ), "", "*.log" );

    if( filename.isEmpty() ) {
        return;
    }

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
    flightListModel_.set( store_->flights() );
    planeListModel_.set( store_->planes() );
    locationListModel_.set( store_->locations() );
    updateActions();

    settings.setValue( "LastDir", QFileInfo( filename ).path() );
}

void MainWindow::on_actionSave_triggered() {
    store_->save();
}

void MainWindow::on_actionSaveAs_triggered() {
    auto oldStore = store_;
    on_actionNew_triggered();
    if( store_ == oldStore ) {
        return;
    }

    auto flights = oldStore->flights();
    for( const auto& f : flights ) {
        store_->upsert( f );
    }

    auto planes = oldStore->planes();
    for( const auto& p : planes ) {
        store_->upsert( p );
    }

    auto locs = oldStore->locations();
    for( const auto& l : locs ) {
        store_->upsert( l );
    }
    store_->save();
}

void MainWindow::on_flightList_doubleClicked( const QModelIndex& index ) {
    auto flight = flightListModel_.flight( index );
    FlightDialog dlg( store_, flight, this );
    dlg.exec();
    planeListModel_.set( store_->planes() );
    locationListModel_.set( store_->locations() );
}

void MainWindow::on_planeList_doubleClicked( const QModelIndex& index ) {
    auto plane = planeListModel_.plane( index );
    PlaneDialog dlg( plane, this );
    dlg.exec();
}

void MainWindow::on_locationList_doubleClicked( const QModelIndex& index ) {
    auto loc = locationListModel_.location( index );
    LocationDialog dlg( loc, this );
    dlg.exec();
}

void MainWindow::updateActions() {
    ui->actionSave->setEnabled( store_ != nullptr );
    ui->actionSaveAs->setEnabled( store_ != nullptr );

    ui->tabWidget->setEnabled( store_ != nullptr );
}

void MainWindow::on_planeList_clicked( const QModelIndex& index ) {
}

void MainWindow::on_locationList_clicked( const QModelIndex& index ) {
    auto loc = locationListModel_.location( index );
    auto c = loc->location();

    QVariant returnedValue;
    QMetaObject::invokeMethod( ui->mapWidget->rootObject(),
                               "setMapCenter",
                               Q_RETURN_ARG( QVariant, returnedValue ),
                               Q_ARG( QVariant, c.latitude() ),
                               Q_ARG( QVariant, c.longitude() ) );
}

void MainWindow::on_flightList_clicked( const QModelIndex& index ) {
    auto flight = flightListModel_.flight( index );
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

void MainWindow::on_newFlightButton_clicked() {
    auto flight = std::make_shared< domain::Flight >();
    flight->setStartTime( QDateTime::currentDateTime() );
    flight->setEndTime( QDateTime::currentDateTime() );

    FlightDialog dlg( store_, flight, this );
    if( dlg.exec() == QDialog::Accepted ) {
        store_->upsert( flight );
        flightListModel_.add( flight );
    }
    planeListModel_.set( store_->planes() );
    locationListModel_.set( store_->locations() );
}

void MainWindow::on_editFlightButton_clicked() {
    if( !ui->flightList->currentIndex().isValid() ) {
        return;
    }
    on_flightList_doubleClicked( ui->flightList->currentIndex() );
}

void MainWindow::on_removeFlightButton_clicked() {
}

void MainWindow::on_newLocationButton_clicked() {
    auto loc = std::make_shared< domain::Location >();
    LocationDialog dlg( loc, this );
    if( dlg.exec() == QDialog::Accepted ) {
        if( store_->upsert( loc ) ) {
            locationListModel_.add( loc );
        }
    }
}

void MainWindow::on_editLocationButton_clicked() {
    if( !ui->locationList->currentIndex().isValid() ) {
        return;
    }
    on_locationList_doubleClicked( ui->locationList->currentIndex() );
}

void MainWindow::on_removeLocationButton_clicked() {
}

void MainWindow::on_newPlaneButton_clicked() {
    auto plane = std::make_shared< domain::Plane >();
    PlaneDialog dlg( plane, this );
    if( dlg.exec() == QDialog::Accepted ) {
        if( store_->upsert( plane ) ) {
            planeListModel_.add( plane );
        }
    }
}

void MainWindow::on_editPlaneButton_clicked() {
    if( !ui->planeList->currentIndex().isValid() ) {
        return;
    }
    on_planeList_doubleClicked( ui->planeList->currentIndex() );
}

void MainWindow::on_removePlaneButton_clicked() {
}
