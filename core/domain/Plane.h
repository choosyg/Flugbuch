#pragma once

#include <QUuid>
#include <memory>

namespace domain {

class Plane {
public:
    Plane() = default;
    Plane( QUuid id );
    enum class Type { PG, PPG };

    Type type() const;
    void setType( const Type& type );

    QUuid id() const;

    QString manufacturer() const;
    void setManufacturer( const QString& manufacturer );

    QString model() const;
    void setModel( const QString& model );

private:
    const QUuid id_ = QUuid::createUuid();
    Type type_;
    QString manufacturer_; // Nova
    QString model_;        // Mentor 5 L
};

typedef std::shared_ptr< Plane > PlanePtr;

} // namespace domain
