import QtQuick 2.14
import QtLocation 5.14
import QtPositioning 5.14

Item {
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "esri" // "osm", "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate( 53.073635, 8.806422 )
        zoomLevel: 14
    }

    function addMarker( lat, lon ){

        var image = Qt.createQmlObject('import QtQuick 2.14; Image {   }', map, "dynamic")
        image.source = "qrc:///icons/mapPin.svg"

        var pin = Qt.createQmlObject('import QtLocation 5.14; MapQuickItem {   }', map, "dynamic")
        pin.coordinate  = QtPositioning.coordinate(lat, lon)
        pin.anchorPoint.x = image.width/2
        pin.anchorPoint.y = image.height
        pin.sourceItem = image

        map.addMapItem(pin)
    }

    function setMapCenter( lat, lon ) {
        map.clearMapItems()
        addMarker( lat, lon )
        map.center = QtPositioning.coordinate(lat, lon)
    }

    function showRoute( lat1, lon1, lat2, lon2 ){
        map.clearMapItems()
        addMarker( lat1, lon1 )
        addMarker( lat2, lon2 )

        var poly = Qt.createQmlObject('import QtLocation 5.14; MapPolyline  {   }', map, "dynamic")
        poly.line.width = 2
        poly.line.color = 'blue'
        poly.path = [
                    map.center = QtPositioning.coordinate(lat1, lon1),
                    map.center = QtPositioning.coordinate(lat2, lon2)
                ]
        map.addMapItem(poly)
        map.fitViewportToMapItems()
    }
}
