#pragma once

#include <core/persistence/AbstractStore.h>

#include <QSqlDatabase>

namespace persistence {
namespace sql {

class SqLiteStore : public AbstractStore {
public:
    enum class Mode { Open, Create };
    SqLiteStore( const QString& Filename, Mode mode = Mode::Open );
    ~SqLiteStore() override = default;

    void save() override;

    bool upsert( const domain::FlightPtr& flight ) override;
    bool upsert( const domain::LocationPtr& loc ) override;
    bool upsert( const domain::PlanePtr& plane ) override;

    QVector< domain::FlightPtr > flights() override;
    QVector< domain::LocationPtr > locations() override;
    QVector< domain::PlanePtr > planes() override;

private:
    QSqlDatabase db_;

    QVector< domain::FlightPtr > flights_;
    QVector< domain::LocationPtr > locations_;
    QVector< domain::PlanePtr > planes_;

    void openDatabase();
    void createDatabase();
    void readDatabase();

    void createPlaneTable();
    void savePlanes();
    void readPlanes();

    void createLocationTable();
    void saveLocations();
    void readLocations();

    void createFlightTable();
    void saveFlights();
    void readFlights();
};

} // namespace sql
} // namespace persistence
