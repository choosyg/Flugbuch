#include "FlightDialog.h"
#include "ui_FlightDialog.h"

#include "LocationDialog.h"
#include "PlaneDialog.h"

#include <QCompleter>

FlightDialog::FlightDialog( persistence::StorePtr store, domain::FlightPtr flight, QWidget* parent )
    : QDialog( parent ), ui( new Ui::FlightDialog ), store_( store ), flight_( flight ) {
    ui->setupUi( this );

    ui->pilotEdit->setText( flight->pilot() );
    initPlanes();
    initLocations();
    ui->passengerEdit->setPlainText( flight->passenger() );
    ui->fromDate->setDateTime( flight->startTime() );
    ui->toDate->setDateTime( flight->endTime() );

    QStringList completions;
    auto flights = store_->flights();
    for( const auto& f : flights ) {
        completions.append( f->pilot() );
    }
    QCompleter* completer = new QCompleter( completions, ui->pilotEdit );
    ui->pilotEdit->setCompleter( completer );
}

FlightDialog::~FlightDialog() {
    delete ui;
}

void FlightDialog::accept() {
    flight_->setPilot( ui->pilotEdit->text() );

    auto planeId = ui->planeBox->currentData();
    auto planes = store_->planes();
    for( const auto& plane : planes ) {
        if( plane->id() == planeId ) {
            flight_->setPlane( plane );
        }
    }

    auto toId = ui->toBox->currentData().toUuid();
    auto fromId = ui->fromBox->currentData().toUuid();
    auto locs = store_->locations();
    for( const auto& loc : locs ) {
        if( loc->id() == toId ) {
            flight_->setEndLocation( loc );
        }
        if( loc->id() == fromId ) {
            flight_->setStartLocation( loc );
        }
    }

    flight_->setPassenger( ui->passengerEdit->toPlainText() );
    flight_->setStartTime( ui->fromDate->dateTime() );
    flight_->setEndTime( ui->toDate->dateTime() );
    QDialog::accept();
}

void FlightDialog::on_newPlaneButton_clicked() {
    auto plane = std::make_shared< domain::Plane >();
    PlaneDialog dlg( plane, this );
    if( dlg.exec() == QDialog::Accepted ) {
        store_->upsert( plane );
    }
    ui->planeBox->addItem( plane->manufacturer() + " " + plane->model(), plane->id() );
    ui->planeBox->setCurrentIndex( ui->planeBox->findData( plane->id() ) );
}

void FlightDialog::on_newFromButton_clicked() {
    auto loc = createLocation();
    if( loc == nullptr ) {
        return;
    }
    ui->fromBox->setCurrentIndex( ui->fromBox->findData( loc->id() ) );
}

void FlightDialog::on_newToButton_clicked() {
    auto loc = createLocation();
    if( loc == nullptr ) {
        return;
    }
    ui->toBox->setCurrentIndex( ui->toBox->findData( loc->id() ) );
}

domain::LocationPtr FlightDialog::createLocation() {
    auto loc = std::make_shared< domain::Location >();
    LocationDialog dlg( loc, this );
    if( dlg.exec() == QDialog::Accepted ) {
        store_->upsert( loc );
        if( loc->takeOff() ) {
            ui->fromBox->addItem( loc->name(), loc->id() );
        }
        if( loc->land() ) {
            ui->toBox->addItem( loc->name(), loc->id() );
        }
        return loc;
    }
    return nullptr;
}

void FlightDialog::initPlanes() {
    auto planes = store_->planes();
    for( const auto& plane : planes ) {
        ui->planeBox->addItem( plane->manufacturer() + " " + plane->model(), plane->id() );
    }
    if( flight_->plane() != nullptr ) {
        ui->planeBox->setCurrentIndex( ui->planeBox->findData( flight_->plane()->id() ) );
    }
}

void FlightDialog::initLocations() {
    auto locs = store_->locations();
    for( const auto& loc : locs ) {
        if( loc->takeOff() ) {
            ui->fromBox->addItem( loc->name(), loc->id() );
        }
        if( loc->land() ) {
            ui->toBox->addItem( loc->name(), loc->id() );
        }
    }
    if( flight_->startLocation() != nullptr ) {
        ui->fromBox->setCurrentIndex( ui->fromBox->findData( flight_->startLocation()->id() ) );
    }
    if( flight_->endLocation() != nullptr ) {
        ui->toBox->setCurrentIndex( ui->toBox->findData( flight_->endLocation()->id() ) );
    }
}
