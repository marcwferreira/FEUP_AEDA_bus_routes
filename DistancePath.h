/**
 * @file DistancePath.h
 * @brief This file contains the implementation of system to store information while performing a search of a path on the graph
 * and its info
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 27/1/2022
 */

#ifndef AEDAGRAFOS_DISTANCEPATH_H
#define AEDAGRAFOS_DISTANCEPATH_H


#include <string>
#include <vector>
#include <set>

/**
 * This class is a system to store information while performing a search of a path on the graph
 * @param code This is the code of the bus stop it stores information from
 * @param lineCode This is the code of the bus line we are using in this stop
 * @param distance This is the distance from this bus top to the start the user selected
 * @param previous This is the bus stop previous to getting to this one of the path
 * @param visit This stores if this bus stop was already visited or not
 * @param linesChanged This stores the lines we used to get from the start (user selected) to this bus stop
 * @param nlinesChanged The number of lines we used to get from the start (user selected) to this bus stop
 * @param zones This is the zones we used to get from the start (user selected) to this bus stop
 */
class DistancePath {
public:
    DistancePath(const std::string &code, double distance, std::string lineCode);

    DistancePath();


    bool operator<(const DistancePath &rhs) const;

    bool operator>(const DistancePath &rhs) const;

    bool operator<=(const DistancePath &rhs) const;

    bool operator>=(const DistancePath &rhs) const;

    bool operator==(const std::string &rhs) const;

    bool operator!=(const std::string &rhs) const;

    void setCode(const std::string &code);

    void setDistance(double distance);

    const std::string &getCode() const;

    double getDistance() const;

    const std::string &getPrevious() const;

    void setPrevious(const std::string &previous);

    bool isVisited() const;

    void visited();

    const std::string &getLineCode() const;

    void setLinesChanged(std::vector<std::string> linesChanged);

    std::vector<std::string> getLinesChanged() const;

    void setZones(std::set<std::string> zones);

    std::set<std::string> getZones() const;

    int getNLinesChanged() const;

    void setNLinesChanged(int nLinesChanged);

    void setForInit();

private:
   std::string code;
   std::string lineCode;
   double distance;
   std::string previous;
   bool visit;
   std::vector<std::string> linesChanged;
   std::set<std::string> zones;
   int nLinesChanged;
};


#endif //AEDAGRAFOS_DISTANCEPATH_H
