/*
* FILE : m4.cpp
* PROJECT : SENG1000 - Major Assignment #4
* PROGRAMMER : Alexia Tu
* FIRST VERSION : 04/05/2024
* DESCRIPTION : Open a text file (flights.txt) for reading, the lines within this initial file are then also used to open 
* another file that contains datasets of source-destination, fare with varying names and values. The objective of this program
* is to parse properly formatted data (into a struct array) and sort through them so that only the lowest fare for 
* source-destinations with the same name are printed. There is a lot of error checking through out, not only for file i/o functions 
* but also in the formatting for the file strings and the string datasets.
	*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

//return statuses
const int kReturnError = -1;
const int kReturnSuccess = 0;
const int kBlankLine = 1;
const int kMissingDash = 2;
const int kMissingComma = 3;
const int kBeginningOfArr = 0;
//requirements state to not read over 100 datasets
const int kMaxLinesToRead = 100;
//expected not to enter more than 40 characters per dataset
const int kMaxNumChar = 40;
const int kWordSize = 25;

//holds the data of the parsed value of flight info
typedef struct
{
	char airlineName[kWordSize];
	char sourceLocation[kWordSize];
	char destLocation[kWordSize];
	int farePrice;

}FlightData;

int processFlight(char[], FlightData[], int*); //function to read through all files and parse info about source, destination, fare and corresponding airline
int displayLeastFareDetails(FlightData[], int*); //function to display entry of each source  - destination, fare and flight name
int parseLine(char*, char*, int*, char*); //function to extract info from each flight

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
	FlightData flightDataset[kMaxLinesToRead] = { 0 };
	//only runs while opening the file valid and the total lines are less than 100
	while (fgets(currentAirline, kMaxNumChar, pFlights) != NULL && totalLinesRead < kMaxLinesToRead)
	{
		size_t lenAirline = strlen(currentAirline);
		size_t newlineIndex = strcspn(currentAirline, "\n"); //will return initial length of string if there is no \n
		/*if the value of newlineIndex is less than the length of lenAirline, that means strcspn found '\n' and returned
		the index of where it was found, which logically has to be lesser than the length of the full string due to '\0'*/
		if (newlineIndex < lenAirline)
		{
			currentAirline[newlineIndex] = '\0';
		}
		int indexLength = 0;
		const int kIncrementLen = 1;
		//continue to remove spaces, before the char/text, while the first index is equal to a space
		while (currentAirline[kBeginningOfArr] == ' ')
		{
			for (indexLength = 0; indexLength < lenAirline; indexLength++)
			{
				currentAirline[indexLength] = currentAirline[indexLength + kIncrementLen]; //"shifting" characters down one by one
			}
			lenAirline--; //decrease the length of char arr as you remove elements (spaces)
		}
		//remove spaces after text, the amount of bytes to remove from string is found with while loop below
		while (lenAirline > 0 && currentAirline[lenAirline - kIncrementLen] == ' ')
		{
			lenAirline--;
		}
		currentAirline[lenAirline] = '\0'; //have to remove last space/ensure last byte is null

		if (strcmp(currentAirline, "") == kReturnSuccess) //if there is a blank like then skip
		{
			continue;
		}
		//the currentAirline will be the filename to be opened, the dataset array will have flight info
		//appended to each index until 100, the totalLinesRead will be used to keep track of this
		if (processFlight(currentAirline, flightDataset, &totalLinesRead) == kReturnError)
		{
			printf("Error Processing File: %s\n", currentAirline);
			continue;
		}
	}

	printf("\n"); //separates the error from the lowest fare ouput

	//close flights.txt and check + handle any errors
	if (ferror(pFlights))
	{
		printf("Error Reading flights.txt\n");
		return kReturnError;
	}
	if (fclose(pFlights) == EOF)
	{
		printf("Error Closing flights.txt");
		return kReturnError;
	}
	clearerr(pFlights); //clear any return errors from functions

	if (displayLeastFareDetails(flightDataset, &totalLinesRead) == kReturnError)
	{
		printf("Error Displaying Dataset: %s\n", currentAirline);
		//should the program cancel?
		return kReturnError;
	}

	return kReturnSuccess;
}

// FUNCTION: processFlight(char[])
// DESCRIPTION: processes the flight data file 
// PARAMETERS: filename, array of struct (to hold the parse value of flight data), 
// reference to total count (i.e. total lines read)
// RETURNS: int (a status of success or fail for processing the file) ** display in main
int processFlight(char airlineFile[], FlightData individualFlight[], int* linesRead)
{
	char rawFlightData[kMaxNumChar] = { 0 }; //takes in the raw dataset before parsing

	FILE* pCurrentFlight = NULL;
	if ((pCurrentFlight = fopen(airlineFile, "r")) == NULL)
	{
		printf("Cannot Open File %s\n", airlineFile); //only printing errors twice because it does in the example
		return kReturnError; //error will also print in main
	}

	while (fgets(rawFlightData, kMaxNumChar, pCurrentFlight) != NULL && *linesRead < kMaxLinesToRead)
	{
		size_t newlineIndex = strcspn(rawFlightData, "\n");
		if (newlineIndex < strlen(rawFlightData))
		{
			rawFlightData[newlineIndex] = '\0';
		}

		char currentSource[kWordSize] = { 0 };
		char currentDestination[kWordSize] = { 0 };
		int currentFare = 0;

		//getting the airline name to put into the struct
		char airlineName[kWordSize] = { 0 };
		//use strcpsn()
		//and then maybe strncpy magic number
		if (sscanf(airlineFile, "%[a-zA-Z ]", airlineName) < 1)
		{
			return kReturnError;
		}
		//should this be how i check for blank line?
		if (strcmp(rawFlightData, "") == kReturnSuccess)
		{
			//skip blank lines
			continue;
		}

		/*check for return value from parseline(), it will either indicate a specific error or be successful
		(and will be able to send the parsed data to the struct*/
		int parseVal = 0;
		parseVal = parseLine(currentSource, currentDestination, &currentFare, rawFlightData);

		if (parseVal == kReturnError)
		{
			printf("Error Processing File %s line: %s\n", airlineFile, rawFlightData);
			continue;
		}
		else if (parseVal == kReturnSuccess)
		{
			strcpy(individualFlight[*linesRead].airlineName, airlineName);
			strcpy(individualFlight[*linesRead].sourceLocation, currentSource);
			strcpy(individualFlight[*linesRead].destLocation, currentDestination);
			individualFlight[*linesRead].farePrice = currentFare;
		}
		else if (parseVal == kBlankLine)
		{
			//blank line
			continue;
		}
		else if (parseVal == kMissingDash)
		{
			printf("Error Processing File %s line: %s\n", airlineFile, rawFlightData);
			printf("Missing Dash in %s\n", rawFlightData);
			continue;
		}
		else if (parseVal == kMissingComma)
		{
			printf("Error Processing File %s line: %s\n", airlineFile, rawFlightData);
			printf("Missing Comma in %s\n", rawFlightData);
			continue;
		}
		(*linesRead)++;
	}

	if (fclose(pCurrentFlight) == EOF)
	{
		printf("Error Closing File %s\n", airlineFile);
		//i don't think the whole program should end
	}

	clearerr(pCurrentFlight);

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
	//used to ensure that the file is properly formatted
	const char kDash = '-';
	const char kComma = ',';
	const int totalParsed = 3;

	//if the file line is blank then it will be skipped in processFlight()
	if (strcmp(fileLineRead, "") == kReturnSuccess)
	{
		return kBlankLine;
	}
	//check for missing dash
	if ((strchr(fileLineRead, kDash)) == NULL)
	{
		return kMissingDash;
	}
	//check for missing comma
	if ((strchr(fileLineRead, kComma)) == NULL)
	{
		return kMissingComma;
	}

	//should i try to use fscanf? also a-zA-Z[space] for this flag stuff
	if (sscanf(fileLineRead, "%[^-]-%[^,], %d", startLocation, endLocation, priceOfFare) < totalParsed)
	{
		return kReturnError;
	}

	return kReturnSuccess;
}


// FUNCTION: displayLeastFareDetails()
// DESCRIPTION: displays the entry of each source-destination and corresponding fare and
// flight name where lowest priced fare is found. If only one entry of source-destination is found
// then it displays that data in proper format. Displays results in user friendly way.
// Only displays one single entry for source-destination
// PARAMETERS: FlightData[], int*
// RETURNS: success once completed
int displayLeastFareDetails(FlightData individualFlight[], int* linesRead)
{
	//both for loops start at the "beginning" of the array before incrementing
	for (int currentFlightIndex = kBeginningOfArr; currentFlightIndex < *linesRead; currentFlightIndex++)
	{
		/*find the index of the lowest price of each source - destination pair by going through
		each index and comparing to the next*/
		int indexLowestPrice = currentFlightIndex;
		/*for loop needs to be incremented first in order to compare the first element of the flightData array to the next index.
		compare all indexes up until the total lines read (*linesRead) to the current index*/
		for (int nextIndex = kBeginningOfArr; nextIndex < *linesRead; ++nextIndex)
		{
			if ((strcmpi(individualFlight[currentFlightIndex].sourceLocation, individualFlight[nextIndex].sourceLocation)) == kReturnSuccess &&
				(strcmpi(individualFlight[currentFlightIndex].destLocation, individualFlight[nextIndex].destLocation)) == kReturnSuccess)
			{
				//if the value at the current lowest price index is greater than the next index, that means 
				//that the next index is the new lowest price. also equals-to eliminates duplicates
				if (individualFlight[indexLowestPrice].farePrice >= individualFlight[nextIndex].farePrice)
				{
					indexLowestPrice = nextIndex;
				}
			}
		}

		//only print the current index of source-destination if it is equal to the lowest fare
		if (currentFlightIndex == indexLowestPrice)
		{
			printf("%s : %s to %s, Fare $%d\n", individualFlight[indexLowestPrice].airlineName, individualFlight[indexLowestPrice].sourceLocation,
				individualFlight[indexLowestPrice].destLocation, individualFlight[indexLowestPrice].farePrice);
		}
	}

	return kReturnSuccess;
}