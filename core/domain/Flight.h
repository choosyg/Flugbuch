#pragma once

#include "Location.h"
#include "Plane.h"

#include <QDateTime>
#include <QUuid>

#include <memory>

namespace domain {

class Flight {
public:
    Flight() = default;
    Flight( QUuid id );
    QUuid id() const;

    PlanePtr plane() const;
    void setPlane( PlanePtr plane );

    LocationPtr startLocation() const;
    void setStartLocation( LocationPtr startLocation );

    LocationPtr endLocation() const;
    void setEndLocation( LocationPtr endLocation );

    const QDateTime& startTime() const;
    void setStartTime( const QDateTime& startTime );

    const QDateTime& endTime() const;
    void setEndTime( const QDateTime& endTime );

    const QString& pilot() const;
    void setPilot( const QString& pilot );

    const QString& passenger() const;
    void setPassenger( const QString& passenger );

private:
    const QUuid id_ = QUuid::createUuid();
    PlanePtr plane_;

    LocationPtr startLocation_;
    LocationPtr endLocation_;
    // QGeoJson track_; Ab Qt 5.13

    QString pilot_;
    QString passenger_;

    QDateTime startTime_;
    QDateTime endTime_;
};

typedef std::shared_ptr< Flight > FlightPtr;

} // namespace domain
