#include "Plane.h"

namespace domain {

Plane::Plane( QUuid id ) : id_( id ) {
}

Plane::Type Plane::type() const {
    return type_;
}

void Plane::setType( const Type& type ) {
    type_ = type;
}

QUuid Plane::id() const {
    return id_;
}

QString Plane::manufacturer() const {
    return manufacturer_;
}

void Plane::setManufacturer( const QString& manufacturer ) {
    manufacturer_ = manufacturer;
}

QString Plane::model() const {
    return model_;
}

void Plane::setModel( const QString& model ) {
    model_ = model;
}

} // namespace domain
