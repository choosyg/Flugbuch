#include "PlaneDialog.h"
#include "ui_PlaneDialog.h"

PlaneDialog::PlaneDialog( domain::PlanePtr plane, QWidget* parent )
    : QDialog( parent ), ui( new Ui::PlaneDialog ), plane_( plane ) {
    ui->setupUi( this );

    ui->manufacturerEdit->setText( plane->manufacturer() );
    ui->modelEdit->setText( plane->model() );
    if( plane->type() == domain::Plane::Type::PG ) {
        ui->pgRadio->setChecked( true );
    } else {
        ui->ppgRadio->setChecked( true );
    }
}

PlaneDialog::~PlaneDialog() {
    delete ui;
}

void PlaneDialog::accept() {
    plane_->setManufacturer( ui->manufacturerEdit->text() );
    plane_->setModel( ui->modelEdit->text() );
    plane_->setType( ui->pgRadio->isChecked() ? domain::Plane::Type::PG : domain::Plane::Type::PPG );
    QDialog::accept();
}
