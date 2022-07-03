/*! \mainpage AEDA Graphs - Searching for bus paths navigating the city of Oporto
 *
 * This project is a simple way of calculating bus routes in the city and outskirts of Oporto.
 *
 * This work was done within the scope of the Algorithm and Data Structures curricular course,
 * and aimed at deepening the knowledge about graphs and their different search algorithms.
 *
 * With this simple application you can select a place of origin and a place of destination,
 * after that you make select the preferences for the travel:
 *
 * If we the algorithm can find a path for you journey it will display for you, otherwise it will say so.
 *
 * This project was made by:
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 29/1/2022
 *
 */

#include <iostream>
#include "Reader.h"
#include "Stop.h"
#include "Coordinate.h"
#include "Graph.h"
#include "Menu.h"

int main() {

    Menu menu;
    menu.display();
    return 0;

}
