/**
 * @file Coordinate.cpp
 * @brief This file contains the implementation the function in coordinate.h
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 22/1/2022
 */

#include <cmath>
#include "Coordinate.h"

/**
 * Constructor
 * @param lat This is the latitude of the coordinate
 * @param lon This is the longitude of the coordinate
 */
Coordinate::Coordinate(double lat, double lon) {
    this->lat = lat;
    this->lon = lon;
}

/**
 * Constructor
 */
Coordinate::Coordinate() {}

/**
 * This method returns the latitude
 * @return The return is a double that represents the latitude of the coordinate
 */
double Coordinate::getLat() const {
    return lat;
}

/**
 * This method returns the longitude
 * @return The return is a double that represents the longitude of the coordinate
 */
double Coordinate::getLon() const {
    return lon;
}

/**
 * This method calculates the distance between two coordinates on the earth
 * @param cord2 This is the second coordinate used to calculate the distance
 * @return The return is a double with the distance between the two coordinates in meters
 */
double Coordinate::haversine(Coordinate cord2 ){

    const double earthRadius = 6371000; //radius of Earth in maters

    //get latitude and longitude
    double Lat1 = this->lat * M_PI / 180.0;
    double Lat2 = cord2.getLat() * M_PI / 180.0;


    //convert to radians
    double distLatRad = (cord2.getLat()* M_PI / 180.0 - this->lat* M_PI / 180.0) ;
    double distLonRad = (cord2.getLon()* M_PI / 180.0 - this->lon* M_PI / 180.0) ;

    //formula
    double a = pow(sin(distLatRad  / 2), 2) + pow(sin(distLonRad / 2), 2) * cos(Lat1) * cos(Lat2);
    double c = 2 * asin(sqrt(a));

    return c*earthRadius;
}

/**
 * This method adds the coordinate attributes to a ostream
 * @param os the ostream the coordinate is going to be added
 * @param coordinate the coordinate to be added
 * @return the stream updated
 */
std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    os << "lat: " << coordinate.lat << " lon: " << coordinate.lon;
    return os;
}
