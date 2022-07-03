/**
 * @file Menu.cpp
 * @brief This file contains the implementation of the functions in Menu.h (the functions that control the
 * interaction with the user)
 *
 * @author Marcos William Ferreira Pinto, Matias Freitas Guimarães, Tiago Ribeiro
 *
 * @date 22/1/2022
 */

#include "Menu.h"


/**
 * This function controls the display and flow of the menu, it outputs to the screen and asks player for the input (redirect
 * to correct function) whenever necessary.
 */
void Menu::display()  {
    int menuPage = 0;
    int choice;
    while(true) {
        switch (menuPage) {

            case 0: //this is the main menu
                std::cout << "Welcome to the STCP system 1.0 ALPHA" << std::endl
                          << "(Please choose an option)" << std::endl << std::endl
                          << "1. Search For Route" << std::endl
                          << "0. Exit" << std::endl;
                choice = -1; //set it to invalid
                do {
                    choice = getInt();
                    if (choice != 0 && choice != 1) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Search For Route"
                                  << std::endl << "0. Exit" << std::endl;
                    }
                } while (choice != 0 && choice != 1);
                if (choice) { menuPage = 1; } else { return; }
                break;

            case 1: //this is the menu to select the origin
                std::cout << "Introduce departure location" << std::endl
                          << "(Please choose an option)" << std::endl << std::endl
                          << "1. Coordinates" << std::endl
                          << "2. Bus Stop Code" << std::endl
                          << "0. Back to main menu" << std::endl;
                choice = -1; //set it to invalid
                do {
                    choice = getInt();
                    if (choice < 0 || choice > 2) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Coordinates"
                                  << std::endl << "2. Bus Stop Code" << std::endl << "0. Back to main menu" << std::endl;
                    }
                } while (choice < 0 || choice > 2);
                if (choice == 0) {
                    menuPage = 0;
                    break;
                }
                else if (choice == 1) {
                    Coordinate coord = displayCoord();
                    database.partida = Stop("ORIGIN", coord);
                    database.mapDay.addStops({database.partida});
                }
                else if (choice == 2) {
                    Stop code = displayCode();
                    database.partida = code;
                }
                menuPage = 2;
                break;

            case 2: //this is the menu to select the destination
                std::cout << "Introduce the destination" << std::endl
                          << "(Please choose an option)" << std::endl << std::endl
                          << "1. Coordinate" << std::endl
                          << "2. Bus Stop Code" << std::endl
                          << "0. Back to main menu" << std::endl;
                choice = -1; //set it to invalid
                do {
                    choice = getInt();
                    if (choice < 0 || choice > 2) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Coordinates"
                                  << std::endl << "2. Bus Stop Code" << std::endl << "0. Back to main menu" << std::endl;
                    }
                } while (choice < 0 || choice > 2);
                if (choice == 0) {
                    menuPage = 0;
                    break;
                }
                else if (choice == 1) {
                    Coordinate coord = displayCoord();
                    database.chegada = Stop("DESTINATION",coord);
                    database.mapDay.addStops({database.chegada});
                }
                else if (choice == 2) {
                    Stop code = displayCode();
                    database.chegada = code;
                }
                menuPage = 3;
                break;

            case 3: //this is the menu to select the search and its configs
                std::cout << "Which time are you searching:" << std::endl << std::endl
                          << "1. Day time" << std::endl << "2. Night time" << std::endl;
                int timeSearch;
                do{
                    timeSearch = getInt();
                    if (choice != 1 && choice != 2 ) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Day time"
                                  << std::endl << "2. Night time" << std::endl;
                    }
                } while (choice != 1 && choice != 2 );
                std::cout << "Introduce how much distance would you be" << std::endl
                          << "open to walk between stops (in meters):" << std::endl;
                double dist;
                cin >> dist;
                std::cout << "Introduce the maximum amount of " << std::endl
                          << "line changes you would allow:" << std::endl;
                int lineChanges;
                cin >> lineChanges;
                std::cout << "Introduce the maximum number of zones" << std::endl
                          << "you would want to pass:" << std::endl;
                int zones;
                cin >> zones;
                std::cout << "What's your preference?" << std::endl
                          << "(Please choose an option)" << std::endl << std::endl
                          << "1. Lesser distance" << std::endl
                          << "2. Lesser number of stops" << std::endl
                          << "0. Back to main menu" << std::endl;
                choice = -1; //set it to invalid
                do {
                    choice = getInt();
                    if (choice < 0 || choice > 2) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Lesser distance"
                                  << std::endl << "2. Lesser number of stops" << std::endl << "0. Back to main menu" << std::endl;
                    }
                } while (choice < 0 || choice > 2);
                if (choice == 0) {
                    menuPage = 0;
                    break;
                }
                else{

                    if (timeSearch == 1) {database.dayShift = true;}
                    else {database.dayShift = false;}

                    database.searchtype = choice;
                    database.maxwalk = dist;
                    database.maxlines = lineChanges;
                    database.maxzones = zones;
                    displayResults();
                }
                menuPage = 4;
                break;

            case 4:
                std::cout << "Search more?" << std::endl
                          << "(Please choose an option)" << std::endl << std::endl
                          << "1. Search For Another Route" << std::endl
                          << "0. Exit" << std::endl;
                choice = -1; //set it to invalid
                do {
                    choice = getInt();
                    if (choice != 0 && choice != 1) {
                        std::cout << "Please choose a valid option!" << std::endl << std::endl << "1. Search For Another Route"
                                  << std::endl << "0. Exit" << std::endl;
                    }
                } while (choice != 0 && choice != 1);
                if (choice) { menuPage = 1; } else { return; }
                break;

            default:
                std::cout << "something went wrong, select 0 to exit" << std::endl;
                choice = getInt();
                return;
        }
    }
}

/**
 * This function is used when user needs to input a coordinate, it will ask the player for the latitude then the longitude
 * after that it will create the object of class "coordinate"
 * @return This function return the coordinates (object from class coordinate) from the info the player has inputted
 */
Coordinate Menu::displayCoord() {
    std::cout << "Enter latitude:";
    double lat = getDouble();
    std::cout << "Enter longitude:";
    double log = getDouble();
    std::cout << endl;
    return {lat, log};
}

/**
 * This function asks the user to input a bus stop code, (if the user is trying to search a bus stop code), it also has
 * a system to verify if the inputted bus stop code is valid
 * @return The return is the bus stop (object stop) referent to the inputted bus stop code
 */
Stop Menu::displayCode() const {
    while (true) {
        std::cout << "Enter the stop code:";
        string code = getString();
        for (auto a: database.mapDay.getStops()) {
            if (a.getCode() == code)
                return a;
        }
        std::cout << "Invalid!" << std::endl;
    }
}

/**
 * This function is called after all the information about the the search is collected and the starting place and destination
 * place is set. It calls the search using BFS or Dijkstra (depending on the user choice) and display the route resultant
 * from the search if found any or a message saying a route was not found.
 */
void Menu::displayResults() {

    std::cout << "Searching for routes... Please wait" << std::endl;

    database.mapDay.connectWalkStop(database.maxwalk);

    list<Stop> result;
    switch (database.searchtype) {
        case 1:
            if(database.dayShift)
                result = database.mapDay.dijkstra(database.partida, database.chegada, database.maxlines, database.maxzones);
            else
                result = database.mapNight.dijkstra(database.partida, database.chegada, database.maxlines, database.maxzones);
            break;
        case 2:
            if(database.dayShift)
                result = database.mapDay.BFS(database.partida, database.chegada);
            else
                result = database.mapNight.BFS(database.partida, database.chegada);
            break;
        default:
            if(database.dayShift)
                result = database.mapDay.dijkstra(database.partida, database.chegada, database.maxlines, database.maxzones);
            else
                result = database.mapNight.dijkstra(database.partida, database.chegada, database.maxlines, database.maxzones);
            break;
    }

    if(result.empty()){
        std::cout << "Sorry, we couldn't find any routes." << std::endl;
    }
    else {
        std::cout << "This is the best route based on your specification:" << std::endl;
        for (const auto& stop: result) {
            if(stop == database.chegada) {
                std::cout << stop.getCode() << std::endl;
            }
            else{
                std::cout << stop.getCode() << " -> ";
            }
        }
    }

    database.mapDay.removeStop({"ORIGIN","DESTINATION"});

}

/**
 * this function is used to ask the user for an input that is an INT, it has a verification system to see if the input
 * is valid or not
 * @return The return is the int the user inputted to the system
 */
int Menu::getInt() {

    int userInput;
    cin >> userInput;

    if (cin.fail())
    {
        if (cin.eof())
            return 0;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid!" << endl;
        return -1;
    }

    return userInput;

}

/**
 * this function is used to ask the user for an input that is a DOUBLE, it has a verification system to see if the input
 * is valid or not
 * @return The return is the double the user inputted to the system
 */
double Menu::getDouble() {

    double userInput;
    cin >> userInput;

    while (cin.fail())
    {
        cout << "Invalid!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> userInput;
    }

    return userInput;

}

/**
 * this function is used to ask the user for an input that is a STRING
 * @return The return is the string the user inputted to the system
 */
std::string Menu::getString() {
    std::string userInput;
    cin >> userInput;

    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

    return  userInput;
}

