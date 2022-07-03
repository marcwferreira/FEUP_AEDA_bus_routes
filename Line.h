/**
 * @file Line.h
 * @brief This file contains the implementation of bus lines and its methods definition
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#ifndef AEDAGRAFOS_LINE_H
#define AEDAGRAFOS_LINE_H

#include <ostream>
#include "vector"
#include "string"
#include "Stop.h"

/**
 * This class represents a bus line
 * @param code This is the code used to identify the bus line
 * @param name This is the name of the bus line
 * @param stops This is a vector with all the bus stops on the bus line
 * @param direction This is used to indicate the direction of the bus line
 */
class Line {
public:
    Line(const std::vector<std::string> stops, const std::string &code, const std::string &name, int direction);

    Line();

    friend std::ostream &operator<<(std::ostream &os, const Line &line);

    const std::vector<std::string> &getStops() const;

    bool operator<(const Line &rhs) const;

    bool operator>(const Line &rhs) const;

    bool operator<=(const Line &rhs) const;

    bool operator>=(const Line &rhs) const;

    const std::string &getCode() const;

private:
    std::vector<std::string> stops;
    std::string code;
    std::string name;
    int direction;
};


#endif //AEDAGRAFOS_LINE_H
