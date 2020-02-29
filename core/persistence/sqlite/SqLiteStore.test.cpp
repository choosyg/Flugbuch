#pragma once

#include <domain/Plane.h>
#include <domain/Flight.h>
#include <domain/Location.h>

#include <vector>

namespace persistence{

class AbstractStore {
public:
    virtual ~AbstractStore() = default;

    virtual void persist( const domain::Flight& ) = 0;
    virtual void persist( const domain::Location& ) = 0;
    virtual void persist( const domain::Plane& ) = 0;

    virtual domain::Flight getFlight( const QUuid& id ) = 0;
    virtual domain::Location getLocation( const QUuid& id ) = 0;
    virtual domain::Plane getPlane( const QUuid& id ) = 0;

    virtual std::vector< domain::Flight > flights() = 0;
    virtual std::vector< domain::Location > locations() = 0;
    virtual std::vector< domain::Plane > planes() = 0;
};

}
