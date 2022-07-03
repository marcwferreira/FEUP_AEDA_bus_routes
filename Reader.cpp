/**
 * @file Reader.cpp
 * @brief This file contains the implementation of the method of Reader.h
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 20/1/2022
 */

#include "Reader.h"

/**
 * This methods reads and organize the information about the bus stops
 * @param filename This is the file to read
 * @return This returns a set of the stops the function read
 */
std::set<Stop> Reader::readStops(std::string filename) {
    std::set<Stop> myStops;
    std::ifstream my_file;
    my_file.open(filename, std::ios::in);
    if (!my_file) {
        std::cout << "File not exists!";
    }
    else {
        Stop myStop;
        std::string code;
        std::string name;
        std::string zone;
        std::string latitude;
        std::string longitude;

        std::string header;
        std::getline (my_file,header, ',');
        std::getline (my_file,header, ',');
        std::getline (my_file,header, ',');
        std::getline (my_file,header, ',');
        std::getline (my_file,header, '\n');

        while(!my_file.eof()){

            std::getline(my_file,code, ',');
            std::getline (my_file,name, ',');
            std::getline (my_file,zone, ',');
            std::getline (my_file,latitude, ',');
            std::getline (my_file,longitude, '\n');

            myStop = Stop(code,name, zone, Coordinate(std::stod(latitude), std::stod(longitude)));
            myStops.insert(myStop);
        }
    }
    return myStops;
}

/**
 * This methods reads and organize the information about the bus lines
 * @param filename This is the file to read
 * @return This returns a set of the lines the function read
 */
std::set<Line> Reader::readLines(std::string filename, std::set<Stop> stops) {
    std::set<Line> myLines;
    std::ifstream my_file;

    my_file.open(filename, std::ios::in);
    if (!my_file) {
        std::cout << "File not exists!";
    }
    else {
        Stop stop;
        std::string code;
        std::string name;
        std::string stopCode;
        std::ifstream my_fileLine;
        std::string filenameLine;
        Line line;
        std::getline (my_file,code, ',');
        std::getline (my_file,name, '\n');
        while(!my_file.eof()) {
            std::getline (my_file,code, ',');
            std::getline (my_file,name, '\n');
            for (int i = 0; i < 2; ++i) {
                filenameLine = "dataset/line_" + code + "_" + std::to_string(i) + ".csv";
                line = readLine(stops, filenameLine, code, name, i);
                myLines.insert(line);

            }
        }
    }
    return myLines;
}

/**
 * This function is used to read the lines for the files that contains the different bus lines
 * @param stops This is the set of stops in the bus line
 * @param filename This is the file to read
 * @param code This is the code of the bus line
 * @param name This is the name of the bus line
 * @param direction This is the direction the bus line is going to
 * @return The return is a line with the information read added to it
 */
Line Reader::readLine(std::set<Stop> stops, std::string filename,
                      std::string code, std::string name, int direction){
    Stop stop;
    int nStops;
    std::string strNStops;
    std::vector<std::string> stopsCodeLine;
    std::string stopCode;
    std::ifstream my_fileLine;
    my_fileLine.open(filename, std::ios::in);
    if (!my_fileLine) {
        std::cout << "File not exists!";
        return Line();
    }
    else {
        std::getline(my_fileLine,strNStops, '\n');
        nStops = std::stoi(strNStops);
        stopsCodeLine = {};
        for (int j = 0; j < nStops; ++j) {
            getline(my_fileLine, stopCode, '\n');
            stop = *std::find(stops.begin(), stops.end(), stopCode);
            stopsCodeLine.push_back(stop.getCode());
        }
        my_fileLine.close();
    }

    return Line(stopsCodeLine, code, name, direction);
}
