#pragma once

#include <core/domain/Plane.h>

#include <QAbstractListModel>
#include <QVector>

class PlaneListModel : public QAbstractListModel {
    Q_OBJECT

public:
    void set( QVector< domain::PlanePtr > planes );
    void add( domain::PlanePtr plane );
    domain::PlanePtr plane( const QModelIndex& index );

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

private:
    QVector< domain::PlanePtr > planes_;
};
