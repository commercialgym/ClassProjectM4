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

//holds the data of the pased value of flight data
typedef struct
{
    //do i need to change the expected # of characters
    char airlineName[25];
    char sourceLocation[25];
    char destLocation[25];
    int farePrice;

}FlightData;

//function to read through all files and parse info about source, destination, fare and corresponding airline
int processFlight(char[], FlightData [], int*);
//function to display entry of each source  - destination, fare and flight name
int displayLeastFareDetails(char[]);
//function to extract info from each flight
int parseLine(char*, char*, int*, char*);
//my own function
char removeNewline(char[]);
//return statuses
const int kReturnError = -1;
const int kReturnSuccess = 0;
//requirements state to not read over 100 datasets
const int kMaxLinesToRead = 100;
const int kMaxNumChar = 40;


int main(int argc, char* argv[])
{
    char currentFlight[kMaxNumChar] = { 0 }; 
    //keep track of lines read, also used to not read over 100 datasets
    int totalLinesRead = 0;

    FILE* pFlights = NULL;
    if ((pFlights = fopen("flights.txt", "r")) == NULL)
    {
        printf("Cannot open to read to flights.txt\n");
        return kReturnError;
    }

    //only processing/storing 100 datasets as requested by requirements
    FlightData flightDataset[kMaxLinesToRead] = {0};

    //find out if this is the proper while statment, i want to read no more than 100 lines
    //maybe could use for loop
    while (fgets(currentFlight, kMaxNumChar, pFlights) != NULL || totalLinesRead < kMaxLinesToRead)
    {
        //can i use currentFlight[strcspn(currentFlight, "\n")] = '\0';
        removeNewline(currentFlight);

        //new draft
        if (processFlight(currentFlight, flightDataset, &totalLinesRead) == kReturnError)
        {
            printf("Error processing %s\n", currentFlight);
            //should the program cancel?
            return kReturnError;
        }

        /*
        //previous draft
        FILE* pCurrentFlight = NULL;
        if ((pCurrentFlight = fopen(currentFlight, "r")) == NULL)
        {
            printf("Cannot open to write to %s\n", currentFlight);
            return kReturnError;
        }
        */
        


    }

    if (ferror(pFlights))
    {
        printf("Error reading flights.txt\n");
        return kReturnError;
    }

    /*
    //does this for loop need to have a different stop value or can i use while loop
    for (int readFileLine = 0; readFileLine < kMaxLinesToRead; readFileLine++)
    {
        if (fgets(currentFlight, kMaxNumChar, pFlights) == NULL)
        {
            printf("Unable to get line from flights.txt\n");
            return kReturnError;
        }
        //circle back to this error check
        if (feof(pFlights))
        {
            totalLinesRead = readFileLine;
            break;
        }

        //do i need to remove newline?
        size_t length = strlen(currentFlight);
        //use the length (of string) - 1 to index the last element of the string
        if (currentFlight[length - 1] == '\n')
        {
            return currentFlight[length - 1] = '\0';
        }

        //create file pointer to open a file to a specific airline to read its datasets


    }
    */

    //i assume that process flight is also called from main
    

    //displayLeastFareDetails() is called from main

    return kReturnSuccess;
}

// FUNCTION: processFlight(char[])
// DESCRIPTION: processes the flight data file 
// PARAMETERS: filename, array of struct (to hold the parse value of flight data), 
// reference to total count (i.e. total lines read)
// RETURNS: int (a status of success or fail for processing the file) ** display in main
int processFlight(char currentFlight[], FlightData individualFlight[], int* linesRead)
{
    char rawFlightData[kMaxNumChar] = { 0 };

    FILE* pCurrentFlight = NULL;
    if ((pCurrentFlight = fopen(currentFlight, "r")) == NULL)
    {
        printf("Cannot open to write to %s\n", currentFlight);
        return kReturnError;
    }

    while (fgets(rawFlightData, kMaxNumChar, pCurrentFlight) != NULL)
    {
        removeNewline(rawFlightData);
        //processFlight(rawFlightData, flightDataset, &totalLinesRead);
        char currentSource[kMaxNumChar] = { 0 };
        char currentDestination[kMaxNumChar] = { 0 }; 
        char currentFare = 0;
        //need to call parseLine function in order to process flights
        /*if parse line success
        * strcpy individualFlight[*linesRead].source, currentSource);
        * strcpy individualFlights[*linesRead].destination, currentdestination);
        * individualFlight[*linesRead].fare = currentFare;
        * strcpy DO I NEED TO CREATE AN AIRLINE NAME FIELD
        * 
        * else
        * return print statement and kReturnError
        * error should display the line at which the error occurred
        */
        linesRead++;

        //close currentFlight file and check for error
    }

    


    return kReturnSuccess;
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

    return kReturnSuccess;
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

    //don't forget need to check for missing commas or dashes

    //use a search function maybe fgetc? 

    //unneccesary
    /*
    FlightData singleFlight = { 0 };
    //look into using ->
    *singleFlight.destLocation = *endLocation;
    *singleFlight.sourceLocation = *startLocation;
    //why doesn't the fareprice need a *?
    singleFlight.farePrice = *priceOfFare;
    */

    return kReturnSuccess;
}

char removeNewline(char nameInput[])
{
    size_t length = strlen(nameInput);

    //use the length (of string) - 1 to index the last element of the string
    if (nameInput[length - 1] == '\n')
    {
        return nameInput[length - 1] = '\0';
    }

}