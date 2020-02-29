#include "SqLiteStore.h"

#include <QDebug>
#include <QGeoCoordinate>
#include <QSqlError>
#include <QSqlQuery>

namespace persistence {
namespace sql {

/**
 * Tables:
 *  Master - Version of file and of tables
 *  Planes
 *  Flights
 *  Persons
 *  Locations
 */

SqLiteStore::SqLiteStore( const QString& Filename, Mode mode ) : db_( QSqlDatabase::addDatabase( "QSQLITE" ) ) {
    db_.setDatabaseName( Filename );
    openDatabase();
    if( mode == Mode::Create ) {
        createDatabase();
    }
    readDatabase();
}

void SqLiteStore::save() {
    savePlanes();
    saveLocations();
    saveFlights();
}

bool SqLiteStore::upsert( const domain::FlightPtr& flight ) {
    if( !flights_.contains( flight ) ) {
        flights_.append( flight );
        upsert( flight->startLocation() );
        upsert( flight->endLocation() );
        upsert( flight->plane() );
        return true;
    }
    return false;
}

bool SqLiteStore::upsert( const domain::LocationPtr& loc ) {
    if( !locations_.contains( loc ) ) {
        locations_.append( loc );
        return true;
    }
    return false;
}

bool SqLiteStore::upsert( const domain::PlanePtr& plane ) {
    if( !planes_.contains( plane ) ) {
        planes_.append( plane );
        return true;
    }
    return false;
}

QVector< domain::FlightPtr > SqLiteStore::flights() {
    return flights_;
}

QVector< domain::LocationPtr > SqLiteStore::locations() {
    return locations_;
}

QVector< domain::PlanePtr > SqLiteStore::planes() {
    return planes_;
}


void SqLiteStore::openDatabase() {
    if( !db_.open() ) {
        QString msg = "Unable to open \"" + db_.databaseName() + "\": " + db_.lastError().text();
        qWarning() << "ERROR: " << msg;
        throw std::runtime_error( msg.toStdString() );
    }
}

void SqLiteStore::createDatabase() {
    createFlightTable();
    createLocationTable();
    createPlaneTable();
}

void SqLiteStore::readDatabase() {
    readPlanes();
    readLocations();
    readFlights();
}

void SqLiteStore::createPlaneTable() {
    QSqlQuery planeTableQuery( "CREATE TABLE planes ("
                               "Id TEXT NOT NULL UNIQUE,"
                               "Type INTEGER NOT NULL,"
                               "Manufactuer TEXT NOT NULL,"
                               "Model TEXT NOT NULL"
                               ")" );
    if( !planeTableQuery.isActive() ) {
        qWarning() << "ERROR creating plane table: " << planeTableQuery.lastError().text();
    }
}

void SqLiteStore::savePlanes() {
    for( const auto& plane : planes_ ) {
        QSqlQuery q;
        q.prepare( "REPLACE INTO planes VALUES (?,?,?,?)" );
        q.addBindValue( plane->id() );
        q.addBindValue( static_cast< int >( plane->type() ) );
        q.addBindValue( plane->manufacturer() );
        q.addBindValue( plane->model() );
        if( !q.exec() ) {
            qWarning() << "ERROR saving planes: " << q.lastError().text();
        }
    }
}

void SqLiteStore::readPlanes() {
    QSqlQuery q( "SELECT * FROM planes" );
    if( !q.isActive() ) {
        qWarning() << "ERROR reading plane table: " << q.lastError().text();
    }
    while( q.next() ) {
        auto plane = std::make_shared< domain::Plane >( q.value( "Id" ).toUuid() );
        plane->setType( static_cast< domain::Plane::Type >( q.value( "Type" ).toInt() ) );
        plane->setModel( q.value( "Model" ).toString() );
        plane->setManufacturer( q.value( "Manufactuer" ).toString() );
        planes_.append( plane );
        qDebug() << "SqLiteStore::readPlanes(): Added plane \"" << plane->id() << plane->manufacturer()
                 << plane->model() << "\"";
    }
}

void SqLiteStore::createLocationTable() {
    QSqlQuery locationTableQuery( "CREATE TABLE locations ("
                                  "Id TEXT NOT NULL UNIQUE,"
                                  "Name TEXT NOT NULL,"
                                  "Lat REAL NOT NULL,"
                                  "Lon REAL NOT NULL,"
                                  "Alt REAL NOT NULL,"
                                  "TakeOff INTEGER,"
                                  "Land INTEGER"
                                  ")" );
    if( !locationTableQuery.isActive() ) {
        qWarning() << "ERROR creating locations table: " << locationTableQuery.lastError().text();
    }
}

void SqLiteStore::saveLocations() {
    for( const auto& loc : locations_ ) {
        QSqlQuery q;
        q.prepare( "REPLACE INTO locations VALUES (?,?,?,?,?,?,?)" );
        q.addBindValue( loc->id() );
        q.addBindValue( loc->name() );
        q.addBindValue( loc->location().latitude() );
        q.addBindValue( loc->location().longitude() );
        q.addBindValue( loc->location().altitude() );
        q.addBindValue( loc->takeOff() );
        q.addBindValue( loc->land() );
        if( !q.exec() ) {
            qWarning() << "ERROR saving locations: " << q.lastError().text();
        }
    }
}

void SqLiteStore::readLocations() {
    QSqlQuery q( "SELECT * FROM locations" );
    if( !q.isActive() ) {
        qWarning() << "ERROR reading location table: " << q.lastError().text();
    }
    while( q.next() ) {
        auto loc = std::make_shared< domain::Location >( q.value( "Id" ).toUuid() );
        loc->setName( q.value( "Name" ).toString() );
        loc->setLocation(
            QGeoCoordinate( q.value( "Lat" ).toDouble(), q.value( "Lon" ).toDouble(), q.value( "Alt" ).toDouble() ) );
        loc->setTakeOff( q.value( "TakeOff" ).toBool() );
        loc->setLand( q.value( "Land" ).toBool() );
        locations_.append( loc );
    }
}

void SqLiteStore::createFlightTable() {
    QSqlQuery flightTableQuery( "CREATE TABLE flights ("
                                "Id TEXT NOT NULL UNIQUE,"
                                "StartTime INTEGER NOT NULL,"
                                "EndTime INTEGER NOT NULL,"
                                "PlaneId TEXT NOT NULL,"
                                "StartLocationId TEXT NOT NULL,"
                                "EndLocationId TEXT NOT NULL,"
                                "Pilot TEXT NOT NULL,"
                                "Passenger TEXT,"
                                "Track TEXT"
                                ")" );
    if( !flightTableQuery.isActive() ) {
        qWarning() << "ERROR creating flight table: " << flightTableQuery.lastError().text();
    }
}

void SqLiteStore::saveFlights() {
    for( const auto& flight : flights_ ) {
        QSqlQuery q;
        q.prepare( "REPLACE INTO flights VALUES (?,?,?,?,?,?,?,?,?)" );
        q.addBindValue( flight->id() );
        q.addBindValue( flight->startTime().toTime_t() );
        q.addBindValue( flight->endTime().toTime_t() );
        q.addBindValue( flight->plane()->id() );
        q.addBindValue( flight->startLocation()->id() );
        q.addBindValue( flight->endLocation()->id() );
        q.addBindValue( flight->pilot() );
        q.addBindValue( flight->passenger() );
        q.addBindValue( "" ); // track
        if( !q.exec() ) {
            qWarning() << "ERROR saving locations: " << q.lastError().text();
        }
    }
}

void SqLiteStore::readFlights() {
    std::map< QUuid, domain::LocationPtr > locamap;
    for( const auto& loc : locations_ ) {
        locamap[loc->id()] = loc;
    }
    std::map< QUuid, domain::PlanePtr > planemap;
    for( const auto& plane : planes_ ) {
        planemap[plane->id()] = plane;
    }

    QSqlQuery q( "SELECT * FROM flights" );
    if( !q.isActive() ) {
        qWarning() << "ERROR reading flight table: " << q.lastError().text();
    }
    while( q.next() ) {
        auto f = std::make_shared< domain::Flight >( q.value( "Id" ).toUuid() );
        f->setStartTime( QDateTime::fromTime_t( q.value( "StartTime" ).toUInt() ) );
        f->setEndTime( QDateTime::fromTime_t( q.value( "EndTime" ).toUInt() ) );
        f->setPlane( planemap[q.value( "PlaneId" ).toUuid()] );
        f->setStartLocation( locamap[q.value( "StartLocationId" ).toUuid()] );
        f->setEndLocation( locamap[q.value( "EndLocationId" ).toUuid()] );
        f->setPilot( q.value( "Pilot" ).toString() );
        f->setPassenger( q.value( "Passenger" ).toString() );
        flights_.append( f );
    }
}

} // namespace sql
} // namespace persistence
