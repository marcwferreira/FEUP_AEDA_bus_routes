/**
 * @file Coordinate.h
 * @brief This file contains the implementation of a coordinate system and its methods definition
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 22/1/2022
 */

#ifndef AEDAGRAFOS_COORDINATE_H
#define AEDAGRAFOS_COORDINATE_H


#include <ostream>

/**
 * This is a simple coordinate system that stores latitude and longitude
 * @param lat This is the latitude
 * @param lon This is the longitude
 */
class Coordinate {
    double lat{};
    double lon{};
public:

    Coordinate(double lat, double lon);

    Coordinate();

    double getLat() const;
    double getLon() const;

    double haversine(Coordinate cord2);

    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

};


#endif //AEDAGRAFOS_COORDINATE_H
