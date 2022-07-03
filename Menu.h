/**
 * @file Menu.h
 * @brief This file contains the implementation of the menu and its methods definitions
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 28/1/2022
 */

#pragma once

#ifndef MENU_H
#define MENU_H

#include <limits>
#include <iostream>
#include <string>
#include <stack>
#include "Database.h"

using namespace std;


class Menu {

public:

    Database database;

    static int getInt();
    static double getDouble();
    static string getString();

    void display();
    void displayResults() ;

    static Coordinate displayCoord() ;
    Stop displayCode() const;

};


#endif // MENU_H