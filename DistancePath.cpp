/**
 * @file DistancePath.cpp
 * @brief This file contains the implementation of system to store information while performing a search of a path on the graph
 * and its info
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 27/1/2022
 */

#include "DistancePath.h"

/**
 * Constructor
 * @param code This is the code if the bus stop it is going to store information from
 * @param distance This is the distance between this bus stop and the start of the path
 * @param lineCode TThis is the lines we used to get from the start (user selected) to this bus stop
 */
DistancePath::DistancePath(const std::string &code, double distance, std::string lineCode) : code(code), distance(distance), visit(false), lineCode(lineCode), linesChanged(0) {
    for (int i = 0; i < 100; ++i) {
        linesChanged.push_back("0");
    }
}

/**
 * Constructor
 */
DistancePath::DistancePath() {}

/**
 * This function is used to change the code that is stored if necessary
 * @param code This is the code we are changing to
 */
void DistancePath::setCode(const std::string &code) {
    DistancePath::code = code;
}

/**
 * This function is used to change the distance (from this bus stop to the origin) that is stored
 * @param distance This is the new distance to be stored
 */
void DistancePath::setDistance(double distance) {
    DistancePath::distance = distance;
}

/**
 * This function gets the code that is stored
 * @return The return is a string with the code of the bus stop
 */
const std::string &DistancePath::getCode() const {
    return code;
}

/**
 * This function gets the distance that is stored
 * @return The return id a double with the distance between this stop and the start in meters
 */
double DistancePath::getDistance() const {
    return distance;
}

/**
 * This function gets the previous stop before we get on this one on the path calculate
 * @return The return is a string with the code of the previous bus stop
 */
const std::string &DistancePath::getPrevious() const {
    return previous;
}

/**
 * This function is used to change the previous bus stop in case the path needs to be changed
 * @param previous This is the new code to store the previous bus stop
 */
void DistancePath::setPrevious(const std::string &previous) {
    DistancePath::previous = previous;
}

/**
 * This function is used to check if the bus stop related to this distancePath was visited or not
 * @return This returns true if it has been visited, false if otherwise
 */
bool DistancePath::isVisited() const {
    return visit;
}

/**
 * This function is used to set the bus stop as been visited by the algorithm
 */
void DistancePath::visited() {
    DistancePath::visit = true;
}

/**
 * This function is used to get the bus line we used in this bus stop
 * @return The return is a string with the code of the bus line we used in this bus stop
 */
const std::string &DistancePath::getLineCode() const {
    return lineCode;
}

/**
 * This function is used to change the stored lines used from start to this bus stop, in case the path changed
 * @param linesChanged This is the vector with the new lines used to get to this bus stop
 */
void DistancePath::setLinesChanged(std::vector<std::string> linesChanged) {
    DistancePath::linesChanged = linesChanged;
}

/**
 * This function is used to get the bus lines used from start to this bus stop
 * @return This returns a vector with all the bus lines used to get from the start to this bus stop
 */
std::vector<std::string> DistancePath::getLinesChanged() const {
    return linesChanged;
}

/**
 * This function is used to change the stored zoned used from start to this bus stop, in case the path changed
 * @param zones This is the vector with the new zones used to get to this bus stop
 */
void DistancePath::setZones(std::set<std::string> zones) {
    this->zones = zones;

}

/**
 * This function is used to get the zones used from start to this bus stop
 * @return This returns a vector with all the zones used to get from the start to this bus stop
 */
std::set<std::string> DistancePath::getZones() const {
    return zones;
}

/**
 * operator to compare two DistancePaths by their code
 * @param rhs the DistancePath
 * @return if the *this' code is lesser in alphabetic order
 */
bool DistancePath::operator<(const DistancePath &rhs) const {
    return code < rhs.code;
}

/**
 * operator to compare two DistancePaths by their code
 * @param rhs the DistancePath
 * @return if the *this' code is greater in alphabetic order
 */
bool DistancePath::operator>(const DistancePath &rhs) const {
    return rhs < *this;
}

/**
 * operator to compare two DistancePaths by their code
 * @param rhs the DistancePath
 * @return if the *this' code is lesser or equal in alphabetic order
 */
bool DistancePath::operator<=(const DistancePath &rhs) const {
    return !(rhs < *this);
}

/**
 * operator to compare two DistancePaths by their code
 * @param rhs the DistancePath
 * @return if the *this' code is greater or equal in alphabetic order
 */
bool DistancePath::operator>=(const DistancePath &rhs) const {
    return !(*this < rhs);
}

/**
 * operator to compare a Distance Path to a code
 * @param rhs a string
 * @return if the *this' code is equal to the string given
 */
bool DistancePath::operator==(const std::string &rhs) const {
    return code == rhs;
}

/**
 * operator to compare a Distance Path to a code
 * @param rhs a string
 * @return if the *this' code is different from the string given
 */
bool DistancePath::operator!=(const std::string &rhs) const {
    return !(rhs == this->code);
}

/**
 *
 * @return the attribute nLinesChanged
 */
int DistancePath::getNLinesChanged() const {
    return nLinesChanged;
}

/**
 * sets a new value to the attribute nLinesChanged
 * @param nLinesChanged the new value
 */
void DistancePath::setNLinesChanged(int nLinesChanged) {
    DistancePath::nLinesChanged = nLinesChanged;
}

/**
 * resets the object, emptying the vector representing the lines used to get to the current stop, setting the accumulated distance to zero and the bool attribute visit to 'true'
 */
void DistancePath::setForInit() {
    this->distance = 0;
    this->visit = true;
    this->linesChanged = {};

}
