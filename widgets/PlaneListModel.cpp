#include "PlaneListModel.h"


void PlaneListModel::set( QVector< domain::PlanePtr > planes ) {
    beginResetModel();
    planes_ = planes;
    endResetModel();
}

void PlaneListModel::add( domain::PlanePtr plane ) {
    emit beginInsertRows( QModelIndex(), planes_.count(), planes_.count() );
    planes_.append( plane );
    emit endInsertRows();
}

domain::PlanePtr PlaneListModel::plane( const QModelIndex& index ) {
    if( index.isValid() && index.row() < planes_.size() ) {
        return planes_[index.row()];
    }
    return nullptr;
}

int PlaneListModel::rowCount( const QModelIndex& ) const {
    return planes_.count();
}

QVariant PlaneListModel::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() || index.row() >= planes_.size() ) {
        return QVariant();
    }

    if( role == Qt::DisplayRole ) {
        const auto& p = planes_[index.row()];
        return p->manufacturer() + " " + p->model();
    }

    return QVariant();
}
