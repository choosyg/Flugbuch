#include "FlightListModel.h"


void FlightListModel::set( QVector< domain::FlightPtr > flights ) {
    beginResetModel();
    flights_ = flights;
    endResetModel();
}

void FlightListModel::add( domain::FlightPtr flight ) {
    emit beginInsertRows( QModelIndex(), flights_.count(), flights_.count() );
    flights_.append( flight );
    emit endInsertRows();
}

domain::FlightPtr FlightListModel::flight( const QModelIndex& index ) {
    if( index.isValid() && index.row() < flights_.size() ) {
        return flights_[index.row()];
    }
    return nullptr;
}

int FlightListModel::rowCount( const QModelIndex& ) const {
    return flights_.count();
}

QVariant FlightListModel::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() || index.row() >= flights_.size() ) {
        return QVariant();
    }

    if( role == Qt::DisplayRole ) {
        return flights_[index.row()]->startTime().toString( "yyyy-MM-dd hh:mm" );
    }

    return QVariant();
}
