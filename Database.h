/**
 * @file Database.cpp
 * @brief This file contains a class to store all the info we need while the program is running
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 24/1/2022
 */

#ifndef AEDAGRAFOS_DATABASE_H
#define AEDAGRAFOS_DATABASE_H
#include "Graph.h"
#include "Reader.h"


    /**
    * This creates an object that stores all the info necessary while the program is running
    */
class Database {
public:

    Stop partida;
    Stop chegada;
    double maxwalk;
    int searchtype;
    int maxlines;
    int maxzones;
    bool dayShift;
    Graph mapNight;
    Graph mapDay;
    Database() {
        Reader myReader;
        std::set<Stop> myStops =myReader.readStops("./dataset/stops.csv");
        std::set<Line> myLines =myReader.readLines("./dataset/lines.csv", myStops);
        mapDay = Graph(myStops, myLines, false);
        mapNight = Graph(myStops, myLines, true);
    };
};




#endif //AEDAGRAFOS_DATABASE_H
