#include "Flight.h"

namespace domain {

Flight::Flight( QUuid id ) : id_( id ) {
}

QUuid Flight::id() const {
    return id_;
}

PlanePtr Flight::plane() const {
    return plane_;
}

void Flight::setPlane( PlanePtr plane ) {
    plane_ = plane;
}

LocationPtr Flight::startLocation() const {
    return startLocation_;
}

void Flight::setStartLocation( LocationPtr start ) {
    startLocation_ = start;
}

LocationPtr Flight::endLocation() const {
    return endLocation_;
}

void Flight::setEndLocation( LocationPtr end ) {
    endLocation_ = end;
}

const QDateTime& Flight::startTime() const {
    return startTime_;
}

void Flight::setStartTime( const QDateTime& startTime ) {
    startTime_ = startTime;
}

const QDateTime& Flight::endTime() const {
    return endTime_;
}

void Flight::setEndTime( const QDateTime& endTime ) {
    endTime_ = endTime;
}

const QString& Flight::pilot() const {
    return pilot_;
}

void Flight::setPilot( const QString& pilot ) {
    pilot_ = pilot;
}

const QString& Flight::passenger() const {
    return passenger_;
}

void Flight::setPassenger( const QString& passenger ) {
    passenger_ = passenger;
}

} // namespace domain
