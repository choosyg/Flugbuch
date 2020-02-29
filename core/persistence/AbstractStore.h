#pragma once

#include <core/domain/Flight.h>
#include <core/domain/Location.h>
#include <core/domain/Plane.h>

#include <QVector>

#include <memory>

namespace persistence {

class AbstractStore {
public:
    virtual ~AbstractStore() = default;

    virtual void save() = 0;
    virtual bool upsert( const domain::FlightPtr& ) = 0;
    virtual bool upsert( const domain::LocationPtr& ) = 0;
    virtual bool upsert( const domain::PlanePtr& ) = 0;

    virtual QVector< domain::FlightPtr > flights() = 0;
    virtual QVector< domain::LocationPtr > locations() = 0;
    virtual QVector< domain::PlanePtr > planes() = 0;
};

typedef std::shared_ptr< AbstractStore > StorePtr;

} // namespace persistence
