#include "LocationListModel.h"


void LocationListModel::set( QVector< domain::LocationPtr > locs ) {
    beginResetModel();
    locs_ = locs;
    endResetModel();
}

void LocationListModel::add( domain::LocationPtr loc ) {
    emit beginInsertRows( QModelIndex(), locs_.count(), locs_.count() );
    locs_.append( loc );
    emit endInsertRows();
}

domain::LocationPtr LocationListModel::location( const QModelIndex& index ) {
    if( index.isValid() && index.row() < locs_.size() ) {
        return locs_[index.row()];
    }
    return nullptr;
}

int LocationListModel::rowCount( const QModelIndex& ) const {
    return locs_.count();
}

QVariant LocationListModel::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() || index.row() >= locs_.size() ) {
        return QVariant();
    }

    if( role == Qt::DisplayRole ) {
        return locs_[index.row()]->name();
    }

    return QVariant();
}
