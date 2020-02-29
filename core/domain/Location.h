#pragma once

#include <QGeoCoordinate>
#include <QUuid>

#include <memory>

namespace domain {

class Location {
public:
    Location() = default;
    Location( QUuid id );
    QUuid id() const;

    QString name() const;
    void setName( const QString& name );

    QGeoCoordinate location() const;
    void setLocation( const QGeoCoordinate& location );

    bool takeOff() const;
    void setTakeOff( bool takeOff );

    bool land() const;
    void setLand( bool land );

private:
    const QUuid id_ = QUuid::createUuid();
    QString name_; // Bassano
    QGeoCoordinate location_ = QGeoCoordinate( 0.0, 0.0, 0.0 );

    bool takeOff_ = false;
    bool land_ = false;
};

typedef std::shared_ptr< Location > LocationPtr;

} // namespace domain
