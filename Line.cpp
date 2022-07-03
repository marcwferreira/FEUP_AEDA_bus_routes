/**
 * @file Line.cpp
 * @brief This file contains the implementation of the methods in Line.h
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#include "Line.h"

/**
 * Constructor
 * @param stops This is the stops to be added to the new bus line
 * @param code This is the code of the bus line
 * @param name This is the name of the bus line
 * @param direction This is the direction the bus line is going to
 */
Line::Line(const std::vector<std::string> stops, const std::string &code, const std::string &name, int direction) : stops(stops),
                                                                                                 code(code),
                                                                                                 name(name),
                                                                                                 direction(direction){}

/**
 * Constructor
 */
Line::Line() {}

/**
 * This function is used to get the code of a bus line
 * @return The return is a string with the code of the bus line
 */
const std::string &Line::getCode() const {
    return code;
}

/**
 * This function is used to get the stops of a bus line
 * @return The return is a vector with the stops of the bus line
 */
const std::vector<std::string> &Line::getStops() const {
    return stops;
}

/**
 * This method adds the line's attributes to a ostream
 * @param os the ostream the line is going to be added
 * @param line the line to be added
 * @return the stream updated
 */
std::ostream &operator<<(std::ostream &os, const Line &line) {
    os << "LINE INFORMATION:\n";
    os << "Line code: " << line.code << " name: " << line.name << " direction: "
       << line.direction << " stops:\n";
    int i = 0;
    for (auto stop: line.stops) {
        os << "    " << std::to_string(i) << ". " << stop << "\n";
        i++;
    }
    return os;
}

/**
 * operator to compare two Lines by their code
 * @param rhs the Line
 * @return if the *this' code is lesser in alphabetic order
 */
bool Line::operator<(const Line &rhs) const {
    return code < rhs.code;
}

/**
 * operator to compare two Lines by their code
 * @param rhs the Line
 * @return if the *this' code is greater in alphabetic order
 */
bool Line::operator>(const Line &rhs) const {
    return rhs < *this;
}

/**
 * operator to compare two Lines by their code
 * @param rhs the Line
 * @return if the *this' code is lesser or equal in alphabetic order
 */
bool Line::operator<=(const Line &rhs) const {
    return !(rhs < *this);
}

/**
 * operator to compare two Lines by their code
 * @param rhs the Line
 * @return if the *this' code is greater or equal in alphabetic order
 */
bool Line::operator>=(const Line &rhs) const {
    return !(*this < rhs);
}
