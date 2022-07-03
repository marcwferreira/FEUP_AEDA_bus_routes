/**
 * @file Stop.h
 * @brief This file contains the implementation of a bus stop, its necessary info and its methods definition
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#ifndef AEDAGRAFOS_STOP_H
#define AEDAGRAFOS_STOP_H

#include <ostream>
#include <list>
#include <tuple>
#include <set>
#include "string"
#include "Coordinate.h"

/**
 * This represents a bus stop, it contains:
 * @param Code This is the identifying code of the bus stop
 * @param Name This is the name of the bus stop
 * @param Zone This is the zone of the city where the bus stop is located at
 * @param coordinate This is the coordinates that the bus stop is located at
 * @param lineNeighbours This is the neighbours (edges) of the bus stop where we can go to by taking a bus
 * @param walkNeighbours This is the neighbours (edges) of the bus stop where we can get to by walking
 * @param isVisited This is used to during processing to mark if this bus stops was already calculated (visited) in our algorithm or not
 */
class Stop {
public:
    void reset();
    //when it is a random stop
    Stop(std::string code, Coordinate stopCords);

    void visited();

    friend std::ostream &operator<<(std::ostream &os, const Stop &stop);

    double distance(Stop stop2);

    void addLineNeighbour(std::tuple<double, Stop&, std::string> myNewNeighbours);

    void addWalkNeighbour(std::tuple<double, Stop&, std::string> myNewNeighbours);

    void clearWalkNeighbours();

    const std::list<std::tuple<double, Stop &, std::string>> &getLineNeighbours() const;

    const std::list<std::tuple<double, Stop &, std::string>> &getWalkNeighbours() const;



    /////////////////////////////////////
    Stop(const std::string &code, const std::string &name, const std::string &zone, Coordinate coordinate);

    Stop();


    friend std::ostream &operator<<(std::ostream &os, const Stop &stop);

    bool operator==(const std::string &rhs) const;

    bool operator!=(const std::string &rhs) const;

    const std::string &getCode() const;

    const std::string &getName() const;

    const std::string getZone() const;

    Coordinate getCoordinate() const;

    bool operator<(const Stop &rhs) const;

    bool operator>(const Stop &rhs) const;

    bool operator<=(const Stop &rhs) const;

    bool operator>=(const Stop &rhs) const;

    bool operator==(const Stop &rhs) const;

    bool operator!=(const Stop &rhs) const;

    bool getIsVisited() const;

private:
    std::string Code;
    std::string Name;
    std::string Zone;
    Coordinate coordinate;
    //in tuple, first distance, after stop neighbours and last the line code.
    std::list<std::tuple<double, Stop&, std::string>> lineNeighbours;
    std::list<std::tuple<double, Stop&, std::string>> walkNeighbours;
    bool isVisited;

};


#endif //AEDAGRAFOS_STOP_H
