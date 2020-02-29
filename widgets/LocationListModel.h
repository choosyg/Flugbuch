#pragma once

#include <core/domain/Location.h>

#include <QAbstractListModel>
#include <QVector>

class LocationListModel : public QAbstractListModel {
    Q_OBJECT

public:
    void set( QVector< domain::LocationPtr > locs );
    void add( domain::LocationPtr loc );
    domain::LocationPtr location( const QModelIndex& index );

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

private:
    QVector< domain::LocationPtr > locs_;
};
