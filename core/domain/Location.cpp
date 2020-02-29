#include "Location.h"

namespace domain {

Location::Location( QUuid id ) : id_( id ) {
}

QUuid Location::id() const {
    return id_;
}

QString Location::name() const {
    return name_;
}

void Location::setName( const QString& name ) {
    name_ = name;
}

QGeoCoordinate Location::location() const {
    return location_;
}

void Location::setLocation( const QGeoCoordinate& location ) {
    location_ = location;
}

bool Location::takeOff() const {
    return takeOff_;
}

void Location::setTakeOff( bool takeOff ) {
    takeOff_ = takeOff;
}

bool Location::land() const {
    return land_;
}

void Location::setLand( bool land ) {
    land_ = land;
}

} // namespace domain
