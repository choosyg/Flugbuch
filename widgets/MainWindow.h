#pragma once

#include "FlightListModel.h"
#include "LocationListModel.h"
#include "PlaneListModel.h"

#include <core/persistence/AbstractStore.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow() override;

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();

    void on_flightList_doubleClicked( const QModelIndex& index );
    void on_planeList_doubleClicked( const QModelIndex& index );
    void on_locationList_doubleClicked( const QModelIndex& index );

    void on_planeList_clicked( const QModelIndex& index );
    void on_locationList_clicked( const QModelIndex& index );
    void on_flightList_clicked( const QModelIndex& index );

    void on_actionMapOsm_triggered();
    void on_actionMapEsri_triggered();

    void on_newFlightButton_clicked();
    void on_editFlightButton_clicked();
    void on_removeFlightButton_clicked();

    void on_newLocationButton_clicked();
    void on_editLocationButton_clicked();
    void on_removeLocationButton_clicked();

    void on_newPlaneButton_clicked();
    void on_editPlaneButton_clicked();
    void on_removePlaneButton_clicked();

private:
    void updateActions();

    Ui::MainWindow* ui;

    persistence::StorePtr store_ = nullptr;

    FlightListModel flightListModel_;
    PlaneListModel planeListModel_;
    LocationListModel locationListModel_;
};
