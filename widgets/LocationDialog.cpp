#include "LocationDialog.h"
#include "ui_LocationDialog.h"

LocationDialog::LocationDialog( domain::LocationPtr loc, QWidget* parent )
    : QDialog( parent ), ui( new Ui::LocationDialog ), loc_( loc ) {
    ui->setupUi( this );

    ui->nameEdit->setText( loc->name() );
    ui->startBox->setChecked( loc->takeOff() );
    ui->landBox->setChecked( loc->land() );

    ui->latitudeBox->setValue( loc->location().latitude() );
    ui->longitudeBox->setValue( loc->location().longitude() );
    ui->altitudeBox->setValue( static_cast< int >( loc->location().altitude() ) );
}

LocationDialog::~LocationDialog() {
    delete ui;
}

void LocationDialog::accept() {
    loc_->setName( ui->nameEdit->text() );
    loc_->setTakeOff( ui->startBox->isChecked() );
    loc_->setLand( ui->landBox->isChecked() );

    QGeoCoordinate c( ui->latitudeBox->value(), ui->longitudeBox->value(), ui->altitudeBox->value() );
    loc_->setLocation( c );

    QDialog::accept();
}
