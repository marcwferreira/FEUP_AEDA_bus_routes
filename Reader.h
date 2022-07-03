/**
 * @file Reader.h
 * @brief This file contains the reader for the dataset with the information about the bus system
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#ifndef AEDAGRAFOS_READER_H
#define AEDAGRAFOS_READER_H

#include "Stop.h"
#include "vector"
#include "string"
#include "Line.h"
#include "Coordinate.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Coordinate.h"
#include "set"
#include "algorithm"

/**
 * This class is the reader with its methods to ble able to read the files
 */
class Reader {
public:
    static std::set<Stop> readStops(std::string filename);
    static std::set<Line> readLines(std::string filename, std::set<Stop> stops);
    static Line readLine(std::set<Stop> stops, std::string filename,
                          std::string code, std::string name, int direction);

};


#endif //AEDAGRAFOS_READER_H
