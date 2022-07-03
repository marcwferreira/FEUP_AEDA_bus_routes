/**
 * @file Graph.h
 * @brief This file contains the implementation of the graph and its methods definition
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 22/1/2022
 */

#ifndef AEDAGRAFOS_GRAPH_H
#define AEDAGRAFOS_GRAPH_H


#include <vector>
#include <string>
#include <list>
#include <limits>
#include "Coordinate.h"
#include "Line.h"
#include "Stop.h"
#include "iostream"
#include "algorithm"
#include "set"
#include <queue>
#include "DistancePath.h"
#include <tuple>

/**
 * This is the graph that stores the different bus stops
 * @param stops is the list of the bus stops on the graph
 * @param walkingDistance the maximum distance that connects two stops by foot
 */
class Graph {
    std::vector<Stop> stops; // The list of stops being represented

    std::list<Stop> currentPath(const std::vector<DistancePath>& distPath, const Stop& start, const Stop& dest);
    static std::list<std::tuple<double, Stop&, std::string>> combineAllNeighbours(const std::list<std::tuple<double, Stop&, std::string>>& lineNeighbours,
                                                                           const std::list<std::tuple<double, Stop&, std::string>>& walkNeighbours);
    double walkingDistance;
public:
    Graph(std::set<Stop> myStops, std::set<Line> myLines, bool isNight);

    Graph();

    void connectWalkStop(double walkingDistance);
    std::list<Stop> dijkstra(const Stop& start, const Stop& dest, const int nLinesToChange, const int nZones);
    std::list<Stop> BFS(const Stop& start, const Stop& dest);
    const std::vector<Stop> &getStops() const;
    void addStops(std::vector<Stop> newStop);
    void removeStop(std::vector<std::string> code);
    void clearWalkNeighbours();

    double getWalkingDistance() const;

    void setWalkingDistance(int walkingDistance);
};


#endif //AEDAGRAFOS_GRAPH_H
