/**
 * @file Stop.cpp
 * @brief This file contains the implementation of the functions in stop.h (functions of a bus stop)
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#include "Stop.h"

/**
 * Constructor
 * @param code This is the code of the bus stop
 * @param name This is the name of the bus stop
 * @param zone This is the zone the bus stop is located
 * @param coordinate This is the coordinates of the bus stop
 */
Stop::Stop(const std::string &code, const std::string &name, const std::string &zone, Coordinate coordinate)
        : Code(code), Name(name), Zone(zone), coordinate(coordinate), isVisited(false), walkNeighbours({}), lineNeighbours({}){}

/**
 * Constructor
 * @param stopCords This is the coordinates of the bus stop
 */
Stop::Stop(std::string code, Coordinate stopCords): Code(code), Name(""), Zone("walk"), coordinate(stopCords), isVisited(false), walkNeighbours({}), lineNeighbours({}){}

/**
 * Constructor
 */
Stop::Stop() {}

/**
 * This method returns the code of the bus stop
 * @return This returns a string that is the code of the bus stop
 */
const std::string &Stop::getCode() const {
    return Code;
}

/**
 * This method return the name of the bus stop
 * @return This returns a string that is the name of the bus stop
 */
const std::string &Stop::getName() const {
    return Name;
}

/**
 * This method return the zone the bus stop is located at
 * @return This returns a string that is the zone of the bus stop
 */
const std::string Stop::getZone() const {
    return Zone;
}

/**
 * This method return the coordinates the bus stop is located at
 * @return This returns the coordinate (coordinate is an object) of the bus stop
 */
Coordinate Stop::getCoordinate() const {
    return coordinate;
}

std::ostream &operator<<(std::ostream &os, const Stop &stop) {
    os << "Stop code: " << stop.Code << " Name: " << stop.Name << " Zone: " << stop.Zone << " latitude: " << stop.coordinate.getLat()
       << " longitude: " << stop.coordinate.getLon();
    return os;
}

/**
 * This method calculates the distance between the bus stop we call it from and another bus stop using haversine function
 * @param stop2 This is the second bus stop to calculate te distance
 * @return The return is a double with the distance between the two stops in meters
 */
double Stop::distance(Stop stop2) {
    return coordinate.haversine(stop2.coordinate);
}

/**
 * This method adds a new neighbour to the bus stop, where we can get to by taking a bus
 * @param myNewNeighbours This is the bus stop we are going to add as neighbour
 */
void Stop::addLineNeighbour(std::tuple<double, Stop &, std::string> myNewNeighbours) {
    this->lineNeighbours.push_back(myNewNeighbours);
}

/**
 * This method adds a new neighbour to the bus stop, where we can get to by walking
 * @param myNewNeighbours This is the bus stop we are going to add as neighbour
 */
void Stop::addWalkNeighbour(std::tuple<double, Stop &, std::string> myNewNeighbours) {
    this->walkNeighbours.push_back(myNewNeighbours);
}

/**
 * This method clears all the walking neighbours, is used before calculating it again depending on the user preferences
 */
void Stop::clearWalkNeighbours() {
    walkNeighbours.erase(walkNeighbours.begin(), walkNeighbours.end());
}

/**
 * This method returns the neighbours we can get by taking a bus
 * @return The return is a list of the neighbour and its necessary info
 */
const std::list<std::tuple<double, Stop &, std::string>> &Stop::getLineNeighbours() const {
    return lineNeighbours;
}

/**
 * This method returns the neighbours we can get by walking
 * @return The return is a list of the neighbour and its necessary info
 */
const std::list<std::tuple<double, Stop &, std::string>> &Stop::getWalkNeighbours() const {
    return walkNeighbours;
}

/**
 * This method sets the bus stop as visited
 */
void Stop::visited() {
    isVisited = true;
}

/**
 * This method sets the bus stop as not visited
 */
void Stop::reset() {
    isVisited = false;
}

/**
 * This method checks if the bus stop was visited or not
 * @return The return is a bool where true if visited, false if otherwise
 */
bool Stop::getIsVisited() const {
    return isVisited;
}

/**
 * operator to compare a Stops to a code
 * @param rhs a code
 * @return if the *this' code is equal to the given code
 */
bool Stop::operator==(const std::string &rhs) const {
    return this->Code == rhs;
}

/**
 * operator to compare two Stops to a code
 * @param rhs a code
 * @return if the *this' code is different from the given code
 */
bool Stop::operator!=(const std::string &rhs) const {
    return rhs != this->Code;
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is lesser in alphabetic order
 */
bool Stop::operator<(const Stop &rhs) const {
    return Code < rhs.Code;
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is greater in alphabetic order
 */
bool Stop::operator>(const Stop &rhs) const {
    return rhs < *this;
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is lesser or equal in alphabetic order
 */
bool Stop::operator<=(const Stop &rhs) const {
    return !(rhs < *this);
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is greater or equal in alphabetic order
 */
bool Stop::operator>=(const Stop &rhs) const {
    return !(*this < rhs);
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is equal to the given Stop's code
 */
bool Stop::operator==(const Stop &rhs) const {
    return Code == rhs.Code;
}

/**
 * operator to compare two Stops by their code
 * @param rhs the Stop
 * @return if the *this' code is different from the given Stop's code
 */
bool Stop::operator!=(const Stop &rhs) const {
    return !(rhs == *this);
}



