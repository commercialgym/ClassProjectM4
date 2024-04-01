/*
* FILE : m4.cpp
* PROJECT : SENG1000 - Major Assignment #4
* PROGRAMMER : Alexia Tu 
* FIRST VERSION : 
* DESCRIPTION :
    * 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

//function to read through all files and parse info about source, destination, fare and corresponding airline
int processFlight(char[], struct FlightData[], int);
//function to display entry of each source  - destination, fare and flight name
int displayLeastFareDetails(char[]);
//function to extract info from each flight
int parseLine(char*, char*, int*, char*);
//return statuses
const int kReturnError = -1;
const int kReturnSuccess = 0;

//holds the data of the pased value of flight data
typedef struct
{
    //do i need to change the expected # of characters
    char sourceLocation[25];
    char destLocation[25];
    int farePrice;

}FlightData;

int main(int argc, char* argv[])
{
    //i assume that process flight is also called from main
    

    //displayLeastFareDetails() is called from main
}

// FUNCTION: processFlight(char[])
// DESCRIPTION: processes the flight data file 
// PARAMETERS: filename, array of struct (to hold the parse value of flight data), 
// reference to total count (i.e. total lines read)
// RETURNS: int (a status of success or fail for processing the file) ** display in main
int processFlight(char[], struct FlightData individualFlight[], int)
{
    //need to call parseLine function in order to process flights

}

// FUNCTION: displayLeastFareDetails(char[])
// DESCRIPTION: displays the entry of each source-destination and corresponding fare and
// flight name where lowest priced fare is found. If only one entry of source-destination is found
// then it displays that data in proper format. Displays results in user friendly way.
// Only displays one single entry for source-destination
// PARAMETERS: 
// RETURNS: 
int displayLeastFareDetails(char[])
{

}

// FUNCTION: parseLine(char*, char*, int*, char*)
// DESCRIPTION: parses / extracts info from each flight result line. is called from
// the processFlight() function. does not have screen output. errors handled by 
// calling processFlight function, status is returned from parseLine().
// PARAMETERS: pointer to source variable (char*), pointer to destination variable(char*),
// pointer to fare variable (int*), pointer to line data read from the file (char*)
// RETURNS: int (status indicating if parsing of airline was success or fail)
int parseLine(char* startLocation, char* endLocation, int* priceOfFare, char* fileLineRead)
{

    //does this need to be declared somewhere else
    FlightData singleFlight = { 0 };
    //look into using ->
    *singleFlight.destLocation = *endLocation;
    *singleFlight.sourceLocation = *startLocation;
    //why doesn't the fareprice need a *?
    singleFlight.farePrice = *priceOfFare;

}