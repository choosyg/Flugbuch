#pragma once

#include <core/domain/Flight.h>

#include <QAbstractListModel>
#include <QVector>

class FlightListModel : public QAbstractListModel {
    Q_OBJECT

public:
    void set( QVector< domain::FlightPtr > flights );
    void add( domain::FlightPtr flight );
    domain::FlightPtr flight( const QModelIndex& index );

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

private:
    QVector< domain::FlightPtr > flights_;
};
