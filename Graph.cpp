/**
 * @file Graph.cpp
 * @brief This file contains the implementation of the functions in Graph.h (the graph that stores the bus stops)
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 22/1/2022
 */

#include "Graph.h"

/**
 * Constructor
 * @param num This is the number of stops of the graph
 * @param dir This is true if the graph is directional, otherwise it is false
 */
Graph::Graph(std::set<Stop> myStops, std::set<Line> myLines, bool isNight): walkingDistance(0){
    for (auto stop:myStops) {
        stops.push_back(stop);
    }
    double distance;

    std::string lastStop;
    for (auto line: myLines) {
        lastStop = "";
        for(auto stop:line.getStops()) {
            if (line.getCode().at(line.getCode().size()-1) != 'M' && isNight){
                continue;
            }
            else if(line.getCode().at(line.getCode().size()-1) == 'M' && !isNight){
                continue;
            }
            if (!lastStop.empty()){
                Stop& origin= *std::find(stops.begin(), stops.end(), stop);
                Stop& destiny = *std::find(stops.begin(), stops.end(), lastStop);
                distance = origin.distance(destiny);
                origin.addLineNeighbour({distance, destiny, line.getCode()});
                destiny.addLineNeighbour({distance, origin, line.getCode()});
            }
            lastStop = stop;
        }
    }
}

/**
 * This method connects (mark as edges) the Stops (nodes) that closer than a set distance
 * @param walkingDistance This is the distance in meter to connect the edges as walking edges
 */
void Graph::connectWalkStop(double walkingDistance) {
    this->walkingDistance = walkingDistance;
    clearWalkNeighbours();
    double distance;
    for (auto &node: stops) {
        for (auto &maybeNeighbour: stops) {
            distance = node.distance(maybeNeighbour);
            if(distance<=walkingDistance && node.getCode() != maybeNeighbour.getCode()){
                node.addWalkNeighbour({distance, maybeNeighbour, "walk"});
            }
        }
    }
}

/**
 * This method gets the closer distance in meters between to stops (places) that also have a max number of zones and
 * a max number of line changes (bus changes)
 * @param startCode This is the place (stop) where the graph will start searching
 * @param destCode This is the destination place, where we are trying to get to
 * @param nLinesToChange This is the maximum number of lines change allowed
 * @param nZones This is the maximum number of zones allowed
 * @return It returns a list of stops (a path) that best match the description, if there is no path it return an empty list
 */
std::list<Stop> Graph::dijkstra(const Stop& start, const Stop& dest, const int nLinesToChange = INT32_MAX, const int nZones = INT32_MAX) {

    std::vector<DistancePath> visitedStopsInfo; //visitedStopsInfo vector

    std::priority_queue<std::tuple<double, Stop, std::string>, std::vector<std::tuple<double, Stop, std::string>>, std::greater<>> stopsToVisit;

    //initialize the dist & visited vectors
    for (const auto& stop: stops) {
        visitedStopsInfo.emplace_back(stop.getCode(), INT32_MAX, "walk");
    }

    std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(), start.getCode())->setForInit();
    stopsToVisit.push({0, *std::find(stops.begin(), stops.end(), start.getCode()), "walk"});

    while (!stopsToVisit.empty()) {
        std::tuple<double, Stop, std::string> currentStopQueueInfo = stopsToVisit.top(); //get top currentStop
        Stop currentStop = std::get<1>(currentStopQueueInfo); //get the node of iteratorNeighbours
        stopsToVisit.pop(); //remove from queue
        std::string currentStopLineCode = std::get<2>(currentStopQueueInfo);
        DistancePath &currentStopPathInfo = *std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(), currentStop.getCode());
        std::vector<std::string> currentStopLines = currentStopPathInfo.getLinesChanged();
        if(currentStopLines.empty() || currentStopLines.back() != std::get<2>(currentStopQueueInfo)){
            currentStopLines.push_back(std::get<2>(currentStopQueueInfo));
        }
        std::string neighbourLineCode;
        currentStopPathInfo.visited();
        currentStopPathInfo.getZones().insert(currentStop.getZone());
        std::set<std::string> neighbourZones = currentStopPathInfo.getZones();
        neighbourZones.insert(currentStop.getZone());

        for (auto neighbour: combineAllNeighbours(currentStop.getLineNeighbours(),
                                                  currentStop.getWalkNeighbours()) ) {

            //get neighbour and dist from iteratorNeighbours
            double distCurrentToNeighbour = std::get<0>(neighbour);
            Stop &neighbourStop = std::get<1>(neighbour);
            DistancePath &neighbourPath = *std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(),
                                                     neighbourStop.getCode());
            //absolute min visitedStopsInfo
            neighbourLineCode = std::get<2>(neighbour);

            if (!neighbourPath.isVisited() &&
                (currentStopPathInfo.getDistance() + distCurrentToNeighbour) < neighbourPath.getDistance() &&
                currentStopLines.size() <= nLinesToChange && neighbourZones.size() < nZones) {

                neighbourPath.setDistance(currentStopPathInfo.getDistance() + distCurrentToNeighbour);
                neighbourPath.setPrevious(currentStop.getCode());
                stopsToVisit.push({neighbourPath.getDistance(), neighbourStop, neighbourLineCode});
                neighbourPath.setLinesChanged(currentStopLines);
                neighbourPath.setZones(neighbourZones);
            }
        }
    }

    return currentPath(visitedStopsInfo, start, dest);
}

/**
 * This method calculates the path with the least number of stops between two stops (node) in the graph
 * @param startCode This is the place (stop) where the graph will start searching
 * @param destCode This is the destination place, where we are trying to get to
 * @return It returns a list of stops (a path) that best match the description, if there is no path it return an empty list
 */
std::list<Stop> Graph::BFS(const Stop& start, const Stop& dest) {

    std::vector<DistancePath> visitedStopsInfo; //distance vector

    //queue for stops to visit
    std::queue<Stop> stopsToVisit;

    //initialize the dist & visited vectors
    for (const auto& stop: stops) {
        visitedStopsInfo.emplace_back(stop.getCode(), INT32_MAX, "walk");
    }

    std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(), start.getCode())->visited();
    std::string currentCode = start.getCode();

    do{
        const Stop& currentStop = *std::find(stops.begin(), stops.end(), currentCode);

        //iterate line neighbours
        for(auto neighbour: combineAllNeighbours(currentStop.getLineNeighbours(),
                                                 currentStop.getWalkNeighbours()) ){
            //get neighbour node itself
            Stop& neighbourStopCode = std::get<1>(neighbour);
            //get neighbour code
            DistancePath& neighbourStop = *std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(), neighbourStopCode.getCode());

            //if iteratorNeighbours was not visited, visit iteratorNeighbours
            if(!neighbourStop.isVisited()){
                neighbourStop.visited();
                stopsToVisit.push(*std::find(stops.begin(), stops.end(), neighbourStop.getCode()));
                neighbourStop.setPrevious(currentStop.getCode());
            }
        }

        //if queue is not empty visit the next stop
        if(!stopsToVisit.empty()){
            currentCode = find(stops.begin(), stops.end(), stopsToVisit.front())->getCode();
            stopsToVisit.pop();
        } else break; //else break from loop

    } while(!stopsToVisit.empty() ||
            !std::find(visitedStopsInfo.begin(), visitedStopsInfo.end(), dest.getCode())->isVisited());


    return currentPath(visitedStopsInfo, start, dest);
}

/**
 * This method is used to get the stops that exists in the graph
 * @return THe return is a vector with all of the known stops to the graph
 */
const std::vector<Stop> &Graph::getStops() const {
    return stops;
}

/**
 * This method constructs the path by starting at the destination and building the path backwards until it reaches the
 * the start (by following its predecessor)
 * @param distPath  This is a vector where the information the stop we are currently looking and the its predecessor is located
 * @param start This is the start of the path we are trying to find (found last)
 * @param dest This is the destination of the path, (where we start rebuilding the path)
 * @return The return is  a list of the stop (the path) from start to dest, if there is not path ir returns am empty list
 */
std::list<Stop> Graph::currentPath(const std::vector<DistancePath>& distPath, const Stop& start, const Stop& dest){
    std::list<Stop> path;
    std::string addedPath;
    if( std::find(distPath.begin(), distPath.end(), dest.getCode())->isVisited() ) {
        path.push_back(dest);
        addedPath = std::find(distPath.begin(), distPath.end(), dest.getCode())->getPrevious();
        while (path.front() != start) {
            auto it = std::find(stops.begin(), stops.end(), addedPath);
            Stop test = *it;
            path.push_front( test );
            addedPath = std::find(distPath.begin(), distPath.end(), addedPath)->getPrevious();
        }
    }
    return path;
}

/**
 * This method combines two lists of neighbours into one
 * @param lineNeighbours This is the first list of neighbour to be combined
 * @param walkNeighbours This is the second list of neighbour to be combined
 * @return This returns a list of neighbours that is the combination the the two received lists
 */
std::list<std::tuple<double, Stop&, std::string>> Graph::combineAllNeighbours(const std::list<std::tuple<double, Stop&, std::string>>& lineNeighbours,
                                                                              const std::list<std::tuple<double, Stop&, std::string>>& walkNeighbours){
    std::list<std::tuple<double, Stop&, std::string>> combinedList;
    copy(lineNeighbours.rbegin(), lineNeighbours.rend(), front_inserter(combinedList));
    copy(walkNeighbours.rbegin(), walkNeighbours.rend(), front_inserter(combinedList));
    return combinedList;
}

/**
 * adds a vector of stops to the graph
 * @param newStop the vector of stops to be added
 */
void Graph::addStops(std::vector<Stop> newStop) {
    for (const auto& newStop : newStop) {
        stops.push_back(newStop);
    }
    connectWalkStop(walkingDistance);
}

/**
 * removes all the stops from the graph whose the code is in the vector given
 * @param codes a vector of strings that represent codes
 */
void Graph::removeStop(std::vector<std::string> codes) {
    for (const auto& code: codes) {
        for (const auto& currstop : stops){
            if (currstop.getCode() == code)
            {
                std::remove(stops.begin(), stops.end(), currstop);
                break;
            }
        }
    }
    connectWalkStop(walkingDistance);
}

/**
 * deletes connections between stops that represent a path done by foot
 */
void Graph::clearWalkNeighbours() {
    for (auto &node : stops) {
        node.clearWalkNeighbours();
    }
}

/**
 * Constructor
 */
Graph::Graph() {}

/**
 * gets the maximum lenght of paths by foot that connect stops
 * @return the attribute walkingDistance
 */
double Graph::getWalkingDistance() const {
    return walkingDistance;
}

/**
 * sets a new maximum lenght for paths by foot that connect stops
 * @param walkingDistance the new walkingDistance
 */
void Graph::setWalkingDistance(int walkingDistance) {
    Graph::walkingDistance = walkingDistance;
}
