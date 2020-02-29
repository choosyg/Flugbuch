#pragma once

#include <core/domain/Flight.h>
#include <core/persistence/AbstractStore.h>

#include <QDialog>

namespace Ui {
class FlightDialog;
}

class FlightDialog : public QDialog {
    Q_OBJECT

public:
    explicit FlightDialog( persistence::StorePtr store, domain::FlightPtr flight, QWidget* parent = nullptr );
    ~FlightDialog() override;

    void accept() override;

private slots:
    void on_newPlaneButton_clicked();
    void on_newFromButton_clicked();
    void on_newToButton_clicked();

private:
    Ui::FlightDialog* ui;

    persistence::StorePtr store_;
    domain::FlightPtr flight_;

    domain::LocationPtr createLocation();
    void initPlanes();
    void initLocations();
};
