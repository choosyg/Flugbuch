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

    void on_actionCreateFlight_triggered();
    void on_actionCreatePlane_triggered();
    void on_actionCreateLocation_triggered();

    void on_flightList_doubleClicked( const QModelIndex& index );
    void on_planeList_doubleClicked( const QModelIndex& index );
    void on_locationList_doubleClicked( const QModelIndex& index );

    void on_planeList_clicked( const QModelIndex& index );

    void on_locationList_clicked( const QModelIndex& index );

    void on_flightList_clicked( const QModelIndex& index );

    void on_actionMapOsm_triggered();

    void on_actionMapEsri_triggered();

private:
    void updateActions();

    Ui::MainWindow* ui;

    persistence::StorePtr store_ = nullptr;

    FlightListModel flm_;
    PlaneListModel plm_;
    LocationListModel llm_;
};
