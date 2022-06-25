//
// Created by shoham on 6/19/22.
//

#include "geometries/GeoPoint.h"

GeoPoint::GeoPoint(Geometry *geometry, Point point) : point(point) {
    this->geometry = geometry;
}

GeoPoint::GeoPoint() : point() {

}

bool GeoPoint::operator==(GeoPoint &other) const {
    return this->geometry == other.geometry && this->point == other.point;
}

bool GeoPoint::operator!() const {
    return geometry == nullptr;
}


