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
int displayLeastFareDetails(FlightData [], int*);
//function to extract info from each flight
int parseLine(char*, char*, int*, char*);
//return statuses
const int kReturnError = -1;
const int kReturnSuccess = 0;
//requirements state to not read over 100 datasets
const int kMaxLinesToRead = 100;
const int kMaxNumChar = 40;

int main(void)
{
    char currentAirline[kMaxNumChar] = { 0 }; 
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
    while (fgets(currentAirline, kMaxNumChar, pFlights) != NULL || totalLinesRead < kMaxLinesToRead)
    {
        //removeNewline
        //should i use strcspn or strrchr
        currentAirline[strcspn(currentAirline, "\n")] = '\0';

        //the currentAirline will be the filename to be opened, the dataset array will have flight info
        //appended to each index until 100, the totalLinesRead will be used to keep track of this
        if (processFlight(currentAirline, flightDataset, &totalLinesRead) == kReturnError)
        {
            printf("Error processing file: %s\n", currentAirline);
            //should the program cancel?
            return kReturnError;
        }

    }

    if (displayLeastFareDetails(flightDataset, &totalLinesRead) == kReturnError)
    {
        printf("Error Displaying Dataset: %s\n", currentAirline);
        //should the program cancel?
        return kReturnError;
    }

    if (ferror(pFlights))
    {
        printf("Error Reading flights.txt\n");
        return kReturnError;
    }


    //dont forget to close flights.txt

return kReturnSuccess;
}

// FUNCTION: processFlight(char[])
// DESCRIPTION: processes the flight data file 
// PARAMETERS: filename, array of struct (to hold the parse value of flight data), 
// reference to total count (i.e. total lines read)
// RETURNS: int (a status of success or fail for processing the file) ** display in main
int processFlight(char airlineFile[], FlightData individualFlight[], int* linesRead)
{
    //takes in the raw dataset before parsing
    char rawFlightData[kMaxNumChar] = { 0 };

    FILE* pCurrentFlight = NULL;
    if ((pCurrentFlight = fopen(airlineFile, "r")) == NULL)
    {
        printf("Error Processing File %s\n", airlineFile);
        return kReturnError;
    }

    while (fgets(rawFlightData, kMaxNumChar, pCurrentFlight) != NULL && *linesRead < kMaxLinesToRead)
    {
        //remove newline
        rawFlightData[strcspn(rawFlightData, "\n")] = '\0';
        //processFlight(rawFlightData, flightDataset, &totalLinesRead);
        char currentSource[kMaxNumChar] = { 0 };
        char currentDestination[kMaxNumChar] = { 0 };
        int currentFare = 0;
        //return value of parseline() to be used in case switch
        int returnValue = 0;

        //getting the airline name to put into the struct
        char airlineName[25] = { 0 };
        if (sscanf(airlineFile, "%[a-zA-Z ]", airlineName) == NULL)
        {
            //should this be the error?
            return kReturnError;
        }
        //should this be how i check for blank line?
        if (strcmp(airlineName, " ") == kReturnSuccess)
        {
            //skip blank lines
            continue;
        }


        //check for return value from parseline(), will either be a specific error or success (will be able to 
        // send parsed data to the struct
        switch (returnValue = (parseLine(currentSource, currentDestination, &currentFare, rawFlightData))) {
            //see later if can use kreturnerror and ksuccesserror for case switch
        case -1:
            printf("Error Processing File %s line: %s\n", airlineFile, rawFlightData);
            continue;
        case 0:
            strcpy(individualFlight[*linesRead].airlineName, airlineName);
            strcpy(individualFlight[*linesRead].sourceLocation, currentSource);
            strcpy(individualFlight[*linesRead].destLocation, currentDestination);
            individualFlight[*linesRead].farePrice = currentFare;
            continue;
        case 1:
            //blank line
            continue;
        case 2:
            printf("Missing Dash in %s\n", rawFlightData);
            continue;
        case 3:
            printf("Missing Comma in %s\n", rawFlightData);
            continue;
        }
        //increment the value that's being pointed to
        (*linesRead)++;
    }

    if (fclose(pCurrentFlight) == EOF)
    {
        printf("Error Closing File %s\n", airlineFile);
        //i don't think the whole program should end
    }

    return kReturnSuccess;
}

// FUNCTION: displayLeastFareDetails()
// DESCRIPTION: displays the entry of each source-destination and corresponding fare and
// flight name where lowest priced fare is found. If only one entry of source-destination is found
// then it displays that data in proper format. Displays results in user friendly way.
// Only displays one single entry for source-destination
// PARAMETERS: 
// RETURNS: 
int displayLeastFareDetails(FlightData individualFlight[], int* linesRead)
{
    //maybe use strcmpi()


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
    //return values for process flights to print
    const int kBlankLine = 1;
    //could even have a return value for if both comma and dash were missing
    const int kMissingDash = 2;
    const int kMissingComma = 3;
    //should i change max char to read to maybe 25
    char currentLineRead[kMaxNumChar] = { 0 };
    strcpy(currentLineRead, fileLineRead);
    //used to ensure that the file is properly formatted
    const char kDash = '-';
    const char kComma = ',';

    //if the file line is blank then it will be skipped in processFlight()
    if (strcmp(currentLineRead, " ") == NULL)
    {
        return kBlankLine;
    }
    //check for missing dash
    if ((strchr(currentLineRead, kDash)) == NULL)
    {
        return kMissingDash;
    }
    //check for missing comma
    if ((strchr(currentLineRead, kComma)) == NULL)
    {
        return kMissingComma;
    }
    
    //Now parse
    //should i try to use fscanf? also a-zA-Z[space] for this flag stuff
    if (sscanf(currentLineRead, "%[^-], %[^,], %d", startLocation, endLocation, priceOfFare) == NULL)
    {
        return kReturnError;
    }

    return kReturnSuccess;
}

