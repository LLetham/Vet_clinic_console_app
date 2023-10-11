#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <climits> // INT_MIN, INT_MAX
#include <ctime>
#include <stdlib.h>
#include <list>
using namespace std;

#define DEBUG_initLinkedList 0
#define DEBUG_displayLinkedList 0
#define DEBUG_deleteLinkedList 0
#define DEBUG_findRecordByLastName 0
#define DEBUG_displaySingleNode 0
#define DEBUG_addNewRecord 0
#define DEBUG_deleteRecordByLastName 0


/******************************************************************/
// strings need to be defined as char pointers, as opposed to string pointers, to
// be compatible with the string class functions used to manipulate the strings.

struct petRecord {
	int recordNumber;
	char* ownerLastName;	// Since the possible length of a string is unknown, a pointer must be used
	char* ownerFirstName;	// because the size of the pointer is known. Memory is then allocated to
	char* petName;			// to store the string and a pointer to the string is stored here in the linked
	char* petType;			// list node.
	int birthMonth;		// change dates from strings to integers to be use with the date calculator.
	int birthDay;
	int birthYear;
	int apptMonth;
	int apptDay;
	int apptYear;

	struct petRecord* next;
	struct petRecord* previous;
};




// functions in LinkedListClass
// 	void initLinkedList(ifstream& infileC)
// 	void displayLinkedList()
//  void displayLastNames()
// 	void deleteLinkedList()
// 	struct petRecord* findRecordByLastName(string LastName)
// 	void displaySingleNode(struct petRecord* singleNodePtr)
// 
// 	struct petRecord* addNewRecord(string owerLastNameI, string ownerFirstNameI, string petNameI, string petTypeI, 
//	int birthMonthI, int birthDayI, int birthYearI,
//	int apptMonthI, int apptDayI, int apptYearI)
// 
// 	int deleteRecordByLastName(string LastName)
//	void WriteLinkedList(ofstream& outfileC)
// 	void newApptDate(struct petRecord* singleNodePtr, int apptMonthS, int apptDayS, int apptYearS)



class LinkedListClass
{
private:
	int recordNumber;
	string ownerLastName;
	string ownerFirstName;
	string petName;
	string petType;
	int birthMonth, birthDay, birthYear;
	int apptMonth, apptDay, apptYear;

	// marks the first node in the linked list for all functions.
	struct petRecord* headPtr;		
	// this is used to point to the present node in the linked list
	// in several functions.
	struct petRecord* currentPtr;
	// This marks the next node in the linked list for some functions.
	struct petRecord* nextPtr;
	struct petRecord* previousPtr;
	// This is used to point to a new node when creating the linked list.
	struct petRecord* newPtr;
	// This is used to point to the record that is to be deleted.
	struct petRecord* deletePtr;

	int maxRecordNumber = 0;
	bool matchFound = false;

	// STL variables
	// STL list class. Set up an object, STLLinkedList for petRecord.
	list<petRecord> STLLinkedList;
	list<petRecord> STLHeadIterator;

	int i;


public:

	// begin!!!!!!!!!!!!!!!!!!!!!!!!!
	/************************************************/
	/************************************************/
	void initSTLLinkedList(ifstream& infileC) {

		// infileC is the pointer to the input file created in main (infile).
		// Get first line (e.g., record) from text file.
		// The string variables read strings from the text file.
		infileC >> recordNumber;
		infileC >> ownerLastName;
		infileC >> ownerFirstName;
		infileC >> petName;
		infileC >> petType;
		infileC >> birthMonth;
		infileC >> birthDay;
		infileC >> birthYear;
		infileC >> apptMonth;
		infileC >> apptDay;
		infileC >> apptYear;

#if DEBUG_initLinkedList == 1
		// Verify that the data has been read in from the file correctly.
		cout << "from infile: recordNumber: \t" << recordNumber << endl;
		cout << "from infile: ownerLastName: \t" << ownerLastName << endl;
		cout << "from infile: ownerFirstName: \t" << ownerFirstName << endl;
		cout << "from infile: petName: \t\t" << petName << endl;
		cout << "from infile: petType: \t\t" << petType << endl;
		cout << "from infile: birthMonth: \t" << birthMonth << endl;
		cout << "from infile: birthDay: \t" << birthDay << endl;
		cout << "from infile: birthYear: \t" << birthYear << endl;
		cout << "from infile: apptMonth: \t" << apptMonth << endl << endl;
		cout << "from infile: apptDay: \t" << apptDay << endl << endl;
		cout << "from infile: apptYear: \t" << apptYear << endl << endl;
#endif


		// I do not think that headPtr needs to be created in main. All of the linked list
		// functions may be done in this class, so headPtr can be stored in the class and
		// not in main. I do not think that main needs access to headPtr to provide it to 
		// another function. I'll will see.
		// create first node of linked list to store the first record from the file
		headPtr = (struct petRecord*)malloc(sizeof(struct petRecord));
		headPtr->previous = NULL;
		headPtr->next = NULL;
		currentPtr = headPtr;
		newPtr = headPtr;


		/****************************************************/
		// creat struct record and fill with data from infile
		// There has to be a better way to detect the end of the data file, but
		// I will figure that out later.
		while (recordNumber != 99999) {

			// Put the data into the node of the linked list.
			// Store the recordNumber in the linked list node.
			currentPtr->recordNumber = recordNumber;

			// track the maximum recordNumber for when it is time to add additional records
			if (recordNumber > maxRecordNumber) maxRecordNumber = recordNumber;

			// Store the ownerLastName in the linked list node.
			// The null character is not added to the string when read from the file, so it needs to be added here.
			// the length() was put into i just so I could see that the length of the string was correct.
			// The location of the allocated memory is stored in the char pointer in the node.
			// The string read from the file is then copied into the allocated memory.
			// The printf is used to verify that the char pointer in the node points to the correct string.
			ownerLastName.push_back('\0');
			//i = ownerLastName.length();
			currentPtr->ownerLastName = (char*)malloc(ownerLastName.length() + 1);
			ownerLastName.copy(currentPtr->ownerLastName, ownerLastName.length());

			ownerFirstName.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = ownerFirstName.length();
			currentPtr->ownerFirstName = (char*)malloc(ownerFirstName.length() + 1);
			ownerFirstName.copy(currentPtr->ownerFirstName, ownerFirstName.length());

			petName.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = petName.length();
			currentPtr->petName = (char*)malloc(petName.length() + 1);
			petName.copy(currentPtr->petName, petName.length());

			petType.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = petType.length();
			currentPtr->petType = (char*)malloc(petType.length() + 1);
			petType.copy(currentPtr->petType, petType.length());

			currentPtr->birthMonth = birthMonth;
			currentPtr->birthDay = birthDay;
			currentPtr->birthYear = birthYear;

			currentPtr->apptMonth = apptMonth;
			currentPtr->apptDay = apptDay;
			currentPtr->apptYear = apptYear;

#if DEBUG_initLinkedList == 1
			// Print out data from currentPtr to see that data was properly inserted into the node.
			printf("%s\t%d\n", "currentPtr->recordNumber:", currentPtr->recordNumber);
			printf("%s\t%s\n", "currentPtr->ownerLastName:", currentPtr->ownerLastName);
			printf("%s\t%s\n", "currentPtr->ownerFirstName:", currentPtr->ownerFirstName);
			printf("%s\t\t%s\n", "currentPtr->petName:", currentPtr->petName);
			printf("%s\t\t%s\n", "currentPtr->petType:", currentPtr->petType);
			printf("%s\t\t%s\n", "currentPtr->birthMonth", currentPtr->birthMonth);
			printf("%s\t\t%s\n", "currentPtr->birthDay", currentPtr->birthDay);
			printf("%s\t\t%s\n", "currentPtr->birthDay", currentPtr->birthDay);
			printf("%s\t%s\n", "currentPtr->ApptMonth:", currentPtr->ApptMonth);
			printf("%s\t%s\n", "currentPtr->ApptDay:", currentPtr->ApptDay);
			printf("%s\t%s\n", "currentPtr->ApptYear:", currentPtr->ApptYear);
#endif

			// Get next line from infile
			infileC >> recordNumber;
			infileC >> ownerLastName;
			infileC >> ownerFirstName;
			infileC >> petName;
			infileC >> petType;
			infileC >> birthMonth;
			infileC >> birthDay;
			infileC >> birthYear;
			infileC >> apptMonth;
			infileC >> apptDay;
			infileC >> apptYear;

#if DEBUG_initLinkedList == 1
			// Verify that the data has been read in from the file correctly.
			cout << "from infile: recordNumber: \t" << recordNumber << endl;
			cout << "from infile: ownerLastName: \t" << ownerLastName << endl;
			cout << "from infile: ownerFirstName: \t" << ownerFirstName << endl;
			cout << "from infile: petName: \t\t" << petName << endl;
			cout << "from infile: petType: \t\t" << petType << endl;
			cout << "from infile: birthMonth: \t" << birthMonth << endl;
			cout << "from infile: birthDay: \t" << birthDay << endl;
			cout << "from infile: birthYear: \t" << birthYear << endl;
			cout << "from infile: ApptMonth: \t" << ApptMonth << endl << endl << endl;
			cout << "from infile: ApptDay: \t" << ApptDay << endl << endl << endl;
			cout << "from infile: ApptYear: \t" << ApptYear << endl << endl << endl;
#endif

			// See if the end of the file has been reached.
			if (recordNumber != 99999) {
				// The end of the text file has not been reached, so create a new node
				// in the linked list then go back to the start of the while loop to 
				// populate the new node.

				// create next node struct to store the data from file record
				newPtr = (struct petRecord*)malloc(sizeof(struct petRecord));
				newPtr->next = NULL;
				currentPtr->next = newPtr;
				newPtr->previous = currentPtr;
				currentPtr = newPtr;
			}
			else {
				/* If the end of the test file has been reached, then the next in the current node has
				already been set to NULL, so there is nothing more to do because the end of the linked
				list has already been marked. */
				// This else statement does not need to be here, but it is here so I can catch the end of
				// the file in the debugger.

#if DEBUG_initLinkedList == 1
				printf("%s\t%d\n\n", "recordNumber:", recordNumber);
				printf("%s\t%d\n\n", "maxRecordNumber:", maxRecordNumber);
#endif

			}

		}
	}


	// end!!!!!!!!!!!!!!!!!!!!!!!
	/************************************************/
	void initLinkedList(ifstream& infileC) {

		// infileC is the pointer to the input file created in main (infile).
		// Get first line (e.g., record) from text file.
		// The string variables read strings from the text file.
		infileC >> recordNumber;
		infileC >> ownerLastName;
		infileC >> ownerFirstName;
		infileC >> petName;
		infileC >> petType;
		infileC >> birthMonth;
		infileC >> birthDay;
		infileC >> birthYear;
		infileC >> apptMonth;
		infileC >> apptDay;
		infileC >> apptYear;

#if DEBUG_initLinkedList == 1
		// Verify that the data has been read in from the file correctly.
		cout << "from infile: recordNumber: \t" << recordNumber << endl;
		cout << "from infile: ownerLastName: \t" << ownerLastName << endl;
		cout << "from infile: ownerFirstName: \t" << ownerFirstName << endl;
		cout << "from infile: petName: \t\t" << petName << endl;
		cout << "from infile: petType: \t\t" << petType << endl;
		cout << "from infile: birthMonth: \t" << birthMonth << endl;
		cout << "from infile: birthDay: \t" << birthDay << endl;
		cout << "from infile: birthYear: \t" << birthYear << endl;
		cout << "from infile: apptMonth: \t" << apptMonth << endl << endl;
		cout << "from infile: apptDay: \t" << apptDay << endl << endl;
		cout << "from infile: apptYear: \t" << apptYear << endl << endl;
#endif


		// I do not think that headPtr needs to be created in main. All of the linked list
		// functions may be done in this class, so headPtr can be stored in the class and
		// not in main. I do not think that main needs access to headPtr to provide it to 
		// another function. I'll will see.
		// create first node of linked list to store the first record from the file
		headPtr = (struct petRecord*)malloc(sizeof(struct petRecord));
		headPtr->previous = NULL;
		headPtr->next = NULL;
		currentPtr = headPtr;
		newPtr = headPtr;


		/****************************************************/
		// creat struct record and fill with data from infile
		// There has to be a better way to detect the end of the data file, but
		// I will figure that out later.
		while (recordNumber != 99999) {

			// Put the data into the node of the linked list.
			// Store the recordNumber in the linked list node.
			currentPtr->recordNumber = recordNumber;
			
			// track the maximum recordNumber for when it is time to add additional records
			if (recordNumber > maxRecordNumber) maxRecordNumber = recordNumber;

			// Store the ownerLastName in the linked list node.
			// The null character is not added to the string when read from the file, so it needs to be added here.
			// the length() was put into i just so I could see that the length of the string was correct.
			// The location of the allocated memory is stored in the char pointer in the node.
			// The string read from the file is then copied into the allocated memory.
			// The printf is used to verify that the char pointer in the node points to the correct string.
			ownerLastName.push_back('\0');
			//i = ownerLastName.length();
			currentPtr->ownerLastName = (char*)malloc(ownerLastName.length() + 1);
			ownerLastName.copy(currentPtr->ownerLastName, ownerLastName.length());

			ownerFirstName.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = ownerFirstName.length();
			currentPtr->ownerFirstName = (char*)malloc(ownerFirstName.length() + 1);
			ownerFirstName.copy(currentPtr->ownerFirstName, ownerFirstName.length());

			petName.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = petName.length();
			currentPtr->petName = (char*)malloc(petName.length() + 1);
			petName.copy(currentPtr->petName, petName.length());

			petType.push_back('\0'); // You need to add null character at the end to delimited the string.
			//i = petType.length();
			currentPtr->petType = (char*)malloc(petType.length() + 1);
			petType.copy(currentPtr->petType, petType.length());

			currentPtr->birthMonth = birthMonth;
			currentPtr->birthDay = birthDay;
			currentPtr->birthYear = birthYear;

			currentPtr->apptMonth = apptMonth;
			currentPtr->apptDay = apptDay;
			currentPtr->apptYear = apptYear;

#if DEBUG_initLinkedList == 1
			// Print out data from currentPtr to see that data was properly inserted into the node.
			printf("%s\t%d\n", "currentPtr->recordNumber:", currentPtr->recordNumber);
			printf("%s\t%s\n", "currentPtr->ownerLastName:", currentPtr->ownerLastName);
			printf("%s\t%s\n", "currentPtr->ownerFirstName:", currentPtr->ownerFirstName);
			printf("%s\t\t%s\n", "currentPtr->petName:", currentPtr->petName);
			printf("%s\t\t%s\n", "currentPtr->petType:", currentPtr->petType);
			printf("%s\t\t%s\n", "currentPtr->birthMonth", currentPtr->birthMonth);
			printf("%s\t\t%s\n", "currentPtr->birthDay", currentPtr->birthDay);
			printf("%s\t\t%s\n", "currentPtr->birthDay", currentPtr->birthDay);
			printf("%s\t%s\n", "currentPtr->ApptMonth:", currentPtr->ApptMonth);
			printf("%s\t%s\n", "currentPtr->ApptDay:", currentPtr->ApptDay);
			printf("%s\t%s\n", "currentPtr->ApptYear:", currentPtr->ApptYear);
#endif

			// Get next line from infile
			infileC >> recordNumber;
			infileC >> ownerLastName;
			infileC >> ownerFirstName;
			infileC >> petName;
			infileC >> petType;
			infileC >> birthMonth;
			infileC >> birthDay;
			infileC >> birthYear;
			infileC >> apptMonth;
			infileC >> apptDay;
			infileC >> apptYear;

#if DEBUG_initLinkedList == 1
			// Verify that the data has been read in from the file correctly.
			cout << "from infile: recordNumber: \t" << recordNumber << endl;
			cout << "from infile: ownerLastName: \t" << ownerLastName << endl;
			cout << "from infile: ownerFirstName: \t" << ownerFirstName << endl;
			cout << "from infile: petName: \t\t" << petName << endl;
			cout << "from infile: petType: \t\t" << petType << endl;
			cout << "from infile: birthMonth: \t" << birthMonth << endl;
			cout << "from infile: birthDay: \t" << birthDay << endl;
			cout << "from infile: birthYear: \t" << birthYear << endl;
			cout << "from infile: ApptMonth: \t" << ApptMonth << endl << endl << endl;
			cout << "from infile: ApptDay: \t" << ApptDay << endl << endl << endl;
			cout << "from infile: ApptYear: \t" << ApptYear << endl << endl << endl;
#endif

			// See if the end of the file has been reached.
			if (recordNumber != 99999) {
				// The end of the text file has not been reached, so create a new node
				// in the linked list then go back to the start of the while loop to 
				// populate the new node.

				// create next node struct to store the data from file record
				newPtr = (struct petRecord*)malloc(sizeof(struct petRecord));
				newPtr->next = NULL;
				currentPtr->next = newPtr;
				newPtr->previous = currentPtr;
				currentPtr = newPtr;
			}
			else {
				/* If the end of the test file has been reached, then the next in the current node has
				already been set to NULL, so there is nothing more to do because the end of the linked
				list has already been marked. */
				// This else statement does not need to be here, but it is here so I can catch the end of
				// the file in the debugger.

#if DEBUG_initLinkedList == 1
				printf("%s\t%d\n\n", "recordNumber:", recordNumber);
				printf("%s\t%d\n\n", "maxRecordNumber:", maxRecordNumber);
#endif

			}

		}
	}

	/*****************************************/
	void displayLinkedList() {
		// Display each node of the linked list starting at the head.
		currentPtr = headPtr;
		nextPtr = currentPtr->next;

#if DEBUG_displayLinkedList == 1
		printf("%s\t0x%x\n", "currentPtr =", currentPtr);
		printf("%s\t0x%x\n", "nextPtr =", nextPtr);
#endif

		while (currentPtr->next != NULL) {
			// For each node print all elements
			printf("%s\t%d\n", "Record Number:", currentPtr->recordNumber);
			printf("%s\t%s\n", "Owner Last Name:", currentPtr->ownerLastName);
			printf("%s\t%s\n", "Owner First Name:", currentPtr->ownerFirstName);
			printf("%s\t\t%s\n", "Pet Name:", currentPtr->petName);
			printf("%s\t\t%s\n", "Pet Type:", currentPtr->petType);
			printf("%s\t\t%d\n", "Birth Month:", currentPtr->birthMonth);
			printf("%s\t\t%d\n", "Birth Day:", currentPtr->birthDay);
			printf("%s\t\t%d\n", "Birth Year:", currentPtr->birthYear);
			printf("%s\t\t%d\n", "Appt Month:", currentPtr->apptMonth);
			printf("%s\t\t%d\n", "Appt Day:", currentPtr->apptDay);
			printf("%s\t\t%d\n\n", "Appt Year:", currentPtr->apptYear);

			currentPtr = nextPtr;
			nextPtr = currentPtr->next;
		}

		// On the last node of the linked list
		printf("%s\t%d\n", "Record Number:", currentPtr->recordNumber);
		printf("%s\t%s\n", "Owner Last Name:", currentPtr->ownerLastName);
		printf("%s\t%s\n", "Owner First Name:", currentPtr->ownerFirstName);
		printf("%s\t\t%s\n", "Pet Name:", currentPtr->petName);
		printf("%s\t\t%s\n", "Pet Type:", currentPtr->petType);
		printf("%s\t\t%d\n", "Birth Month:", currentPtr->birthMonth);
		printf("%s\t\t%d\n", "Birth Day:", currentPtr->birthDay);
		printf("%s\t\t%d\n", "Birth Year:", currentPtr->birthYear);
		printf("%s\t\t%d\n", "Appt Month:", currentPtr->apptMonth);
		printf("%s\t\t%d\n", "Appt Day:", currentPtr->apptDay);
		printf("%s\t\t%d\n\n", "Appt Year:", currentPtr->apptYear);

#if DEBUG_displayLinkedList == 1
		printf("%s\n", "Linked list printed");
#endif

	}

	/*****************************************/
	void displayLastNames() {
		// Display the last name from each record of the linked list starting at the head.
		currentPtr = headPtr;
		nextPtr = currentPtr->next;

		i = 0;

		while (currentPtr->next != NULL) {
			// For each node print the last name only
			ownerLastName = currentPtr->ownerLastName;
			cout << currentPtr->ownerLastName;
			if (ownerLastName.length() >= 8)
				cout << "\t";
			else
				cout << "\t\t";
			i++;
			if (i == 3) {
				cout << endl;
				i = 0;
			}

			// move to next record
			currentPtr = nextPtr;
			nextPtr = currentPtr->next;
		}

		// On the last node of the linked list
		cout << currentPtr->ownerLastName;
		cout << endl;

	}

	/*****************************************/
	void deleteLinkedList() {
		// Delete the linked list starting at the head.
		// Free the memory use for each element of a node then free the node.
		// If there is only one node in the linked list, nextPtr will be NULL as will
		// be currentPtr->next.
		currentPtr = headPtr;
		nextPtr = currentPtr->next;

#if DEBUG_deleteLinkedList == 1
		printf("%s\t0x%x\n", "currentPtr =", currentPtr);
		printf("%s\t0x%x\n\n", "nextPtr =", nextPtr);
#endif


		while (currentPtr->next != NULL) {
			// For each node in the lnked list, the following need to be freed:
			// Need to free the memory allocated to store the strings.
			// Free allocated memory for each element of the node then free the node
			// the integer portions of the struct petRecord are free when the struct is freed.
			free(currentPtr->petType);
			free(currentPtr->petName);
			free(currentPtr->ownerFirstName);
			free(currentPtr->ownerLastName);
			free(currentPtr);

#if DEBUG_deleteLinkedList == 1
			printf("%s\t0x%x\n", "Memory freed: currentPtr =", currentPtr);
#endif

			currentPtr = nextPtr;
			nextPtr = currentPtr->next;

#if DEBUG_deleteLinkedList == 1
			printf("%s\t\t0x%x\n", "Next node: currentPtr =", currentPtr);
			printf("%s\t0x%x\n", "nextPtr: currentPtr->next =", currentPtr->next);
			printf("%s\t\t\t0x%x\n\n", "nextPtr =", nextPtr);
#endif

		}

		// On the last node of the linked list
		free(currentPtr->petType);
		free(currentPtr->petName);
		free(currentPtr->ownerFirstName);
		free(currentPtr->ownerLastName);
		free(currentPtr);

#if DEBUG_deleteLinkedList == 1
		printf("%s\n", "Linked list deleted");
#endif

	}

	/*****************************************/
	// Return a pointer to a node that matches the LastName that is passed or
	// return NULL of no ownerLastName in the linked list matches the LastName. 
	struct petRecord* findRecordByLastName(string LastName) {
		// Search linked list for a specific last name
		currentPtr = headPtr;
		nextPtr = currentPtr->next;
		matchFound = false;

		// Compare name of first record. If not a match, then start march through the
		// linked list to find if there is a match.
		// The push_back function puts a null character at the end of the string. I cannot get
		LastName.push_back('\0');

		// Put the name from the linked list into the string ownerLastName to be able 
		// to use the string class compare function.
		ownerLastName = currentPtr->ownerLastName;
		ownerLastName.push_back('\0');

		// compare for the first node of the linked list.
		if (LastName.compare(0, LastName.length(), ownerLastName) == 0) matchFound = true;
		else matchFound = false;

		// if the first node does not match, then start moving through the nodes of the linked
		// list until either a match is found or all nodes of the linked list are inspected.
		while ((currentPtr->next != NULL) && (matchFound == false)) {
			// Get the next node for comparison
			currentPtr = nextPtr;
			nextPtr = currentPtr->next;

			// Put the ownerLastName from the node into the string variable ownerLastName
			ownerLastName = currentPtr->ownerLastName;
			ownerLastName.push_back('\0');

			// compare the searchLastName to the ownerLastName from the current node of
			// the linked list. Compare only the letters provided in the searchLastName.
			if (LastName.compare(0, LastName.length(), ownerLastName) == 0) matchFound = true;
			else matchFound = false;
		}

		// On the last node of the linked list or a match has been found
#if DEBUG_findRecordByLastName == 1
		printf("%s\t%d\n", "Record Number:", currentPtr->recordNumber);
		printf("%s\t%s\n", "Owner Last Name:", currentPtr->ownerLastName);
		printf("%s\t%s\n", "Owner First Name:", currentPtr->ownerFirstName);
		printf("%s\t\t%s\n", "Pet Name:", currentPtr->petName);
		printf("%s\t\t%s\n", "Pet Type:", currentPtr->petType);
		printf("%s\t\t%d\n", "Birth Date:", currentPtr->birthMonth);
		printf("%s\t\t%d\n", "Birth Date:", currentPtr->birthDay);
		printf("%s\t\t%d\n", "Birth Date:", currentPtr->birthYear);
		printf("%s\t\t%d\n", "Next Appt Date:", currentPtr->ApptMonth);
		printf("%s\t\t%d\n", "Next Appt Date:", currentPtr->ApptDay);
		printf("%s\t\t%d\n\n", "Next Appt Date:", currentPtr->ApptYear);

		printf("%s\n", "Search for match done");
#endif
		if (matchFound == true) return(currentPtr);
		else return(NULL);

	}

	/*****************************************/
	// print out the information of a specific node.
	void displaySingleNode(struct petRecord* singleNodePtr) {
		// Search linked list for a specific last name
		currentPtr = singleNodePtr;

		printf("%s\t%d\n", "Record Number:", currentPtr->recordNumber);
		printf("%s\t%s\n", "Owner Last Name:", currentPtr->ownerLastName);
		printf("%s\t%s\n", "Owner First Name:", currentPtr->ownerFirstName);
		printf("%s\t\t%s\n", "Pet Name:", currentPtr->petName);
		printf("%s\t\t%s\n", "Pet Type:", currentPtr->petType);
		printf("%s\t\t%d\n", "Birth Month:", currentPtr->birthMonth);
		printf("%s\t\t%d\n", "Birth Day:", currentPtr->birthDay);
		printf("%s\t\t%d\n", "Birth Year:", currentPtr->birthYear);
		printf("%s\t%d\n", "Next Appt Month:", currentPtr->apptMonth);
		printf("%s\t\t%d\n", "Next Appt Day:", currentPtr->apptDay);
		printf("%s\t\t%d\n\n", "Next Appt Year:", currentPtr->apptYear);

#if DEBUG_displaySingleNode == 1
		printf("%s\n", "display single node done");
#endif
	}

	/*****************************************/
	// Update the apptDate of a single node with a new appointment date.
	void newApptDate(struct petRecord* singleNodePtr, int apptMonthS, int apptDayS, int apptYearS) {
		// Search linked list for a specific last name
		currentPtr = singleNodePtr;

		currentPtr->apptMonth = apptMonthS;
		currentPtr->apptDay = apptDayS;
		currentPtr->apptYear = apptYearS;

#if DEBUG_displayLinkedList == 1
		printf("%s\n", "newApptDate done");
#endif
	}

	/*****************************************/
	// Update add a new record to the linked list.
	struct petRecord* addNewRecord(string owerLastNameI, string ownerFirstNameI, string petNameI, string petTypeI, 
		int birthMonthI, int birthDayI, int birthYearI,
		int apptMonthI, int apptDayI, int apptYearI) {
		currentPtr = headPtr;
		nextPtr = headPtr->next;

		// Prepare data to go into a new node of the linked list.
		maxRecordNumber++;
		recordNumber = maxRecordNumber;
		ownerLastName = owerLastNameI;
		ownerFirstName = ownerFirstNameI;
		petName = petNameI;
		petType = petTypeI;
		birthMonth = birthMonthI;
		birthDay = birthDayI;
		birthYear = birthYearI;
		apptMonth = apptMonthI;
		apptDay = apptDayI;
		apptYear = apptYearI;

		// create and populate a new node.
		newPtr = (struct petRecord*)malloc(sizeof(struct petRecord));
		newPtr->recordNumber = recordNumber;

		ownerLastName.push_back('\0');
		newPtr->ownerLastName = (char*)malloc(ownerLastName.length() + 1);
		ownerLastName.copy(newPtr->ownerLastName, ownerLastName.length());

		ownerFirstName.push_back('\0');
		newPtr->ownerFirstName = (char*)malloc(ownerFirstName.length() + 1);
		ownerFirstName.copy(newPtr->ownerFirstName, ownerFirstName.length());

		petName.push_back('\0');
		newPtr->petName = (char*)malloc(petName.length() + 1);
		petName.copy(newPtr->petName, petName.length());

		petType.push_back('\0'); 
		newPtr->petType = (char*)malloc(petType.length() + 1);
		petType.copy(newPtr->petType, petType.length());

		newPtr->birthMonth = birthMonthI;
		newPtr->birthDay = birthDayI;
		newPtr->birthYear = birthYearI;

		newPtr->apptMonth = apptMonthI;
		newPtr->apptDay = apptDayI;
		newPtr->apptYear = apptYearI;

		// Now insert the new record into the linked list after headPtr, but before nextPtr
		currentPtr->next = newPtr;
		nextPtr->previous = newPtr;
		newPtr->previous = currentPtr;
		newPtr->next = nextPtr;

#if DEBUG_addNewRecord == 1
		printf("%s\n", "addNewRecord done");
#endif

		return(newPtr);

	}

	/*****************************************/
	// search for a record that matches the last name then delete the record.
	// Return 1 if the record was found and deleted otherwise return 0.
	int deleteRecordByLastName(string LastName) {
		// Search linked list for a specific last name
		currentPtr = headPtr;
		nextPtr = currentPtr->next;
		matchFound = false;

		// Compare name of first record. If not a match, then start march through the
		// linked list to find if there is a match.
		// The push_back function puts a null character at the end of the string. I cannot get
		LastName.push_back('\0');

		// Put the name from the linked list into the string ownerLastName to be able 
		// to use the string class compare function.
		ownerLastName = currentPtr->ownerLastName;
		ownerLastName.push_back('\0');

		// compare for the first node of the linked list.
		if (LastName.compare(0, LastName.length(), ownerLastName) == 0) matchFound = true;
		else matchFound = false;

		// if the first node does not match, then start moving through the nodes of the linked
		// list until either a match is found or all nodes of the linked list are inspected.
		while ((currentPtr->next != NULL) && (matchFound == false)) {
			// Get the next node for comparison
			currentPtr = nextPtr;
			nextPtr = currentPtr->next;

			// Put the ownerLastName from the node into the string variable ownerLastName
			ownerLastName = currentPtr->ownerLastName;
			ownerLastName.push_back('\0');

			// compare the searchLastName to the ownerLastName from the current node of
			// the linked list. Compare only the letters provided in the searchLastName.
			if (LastName.compare(0, LastName.length(), ownerLastName) == 0) matchFound = true;
			else matchFound = false;
		}

		// On the last node of the linked list or a match has been found.
		// If a match has been found, then delete that record.
		if (matchFound) {
			// Matching node is the head node.
			if (currentPtr == headPtr) {
				deletePtr = currentPtr;
				headPtr = nextPtr;
				nextPtr->previous = NULL;

			}
			// Matching node is the last node
			else if (currentPtr->next == NULL) {
				deletePtr = currentPtr;
				previousPtr = currentPtr->previous;
				previousPtr->next = NULL;
			}
			// Matching node is neither the head node or the last node.
			else {
				previousPtr = currentPtr->previous;
				nextPtr = currentPtr->next;
				deletePtr = currentPtr;

				previousPtr->next = nextPtr;
				nextPtr->previous = previousPtr;
			}

#if DEBUG_deleteRecordByLastName == 1
			printf("%s\t%d\n", "Record Number:", currentPtr->recordNumber);
			printf("%s\t%s\n", "Owner Last Name:", currentPtr->ownerLastName);
			printf("%s\t%s\n", "Owner First Name:", currentPtr->ownerFirstName);
			printf("%s\t\t%s\n", "Pet Name:", currentPtr->petName);
			printf("%s\t\t%s\n", "Pet Type:", currentPtr->petType);
			printf("%s\t\t%s\n", "Birth Month:", currentPtr->birthMonth);
			printf("%s\t\t%s\n", "Birth Day:", currentPtr->birthDay);
			printf("%s\t\t%s\n", "Birth Year:", currentPtr->birthYear);
			printf("%s\t\t%s\n", "Appt Month:", currentPtr->apptMonth);
			printf("%s\t\t%s\n", "Appt Day:", currentPtr->apptDay);
			printf("%s\t\t%s\n\n", "Appt Year:", currentPtr->apptYear);

			printf("%s\n", "Delete by last name done");
#endif

			// delete the deletePtr node by freeing the memory
			free(deletePtr->petType);
			free(deletePtr->petName);
			free(deletePtr->ownerFirstName);
			free(deletePtr->ownerLastName);
			free(deletePtr);
		}


		if (matchFound == true) return(1);
		else return(0);

	}

	/************************************************/
	// Write linked list data into a file.
	void WriteLinkedList(ofstream& outfileC) {
		currentPtr = headPtr;

		// Write out the data of the first linked list node.
		outfileC << currentPtr->recordNumber << "\t";
		outfileC << currentPtr->ownerLastName << "\t";
		outfileC << currentPtr->ownerFirstName << "\t";
		outfileC << currentPtr->petName << "\t";
		outfileC << currentPtr->petType << "\t";
		outfileC << currentPtr->birthMonth << "\t";
		outfileC << currentPtr->birthDay << "\t";
		outfileC << currentPtr->birthYear << "\t";
		outfileC << currentPtr->apptMonth << "\t";
		outfileC << currentPtr->apptDay << "\t";
		outfileC << currentPtr->apptYear << "\n";

		// Write out remaining nodes
		while (currentPtr->next != NULL) {
			currentPtr = currentPtr->next;

			// Write out the data of the first linked list node.
			outfileC << currentPtr->recordNumber << "\t";
			outfileC << currentPtr->ownerLastName << "\t";
			outfileC << currentPtr->ownerFirstName << "\t";
			outfileC << currentPtr->petName << "\t";
			outfileC << currentPtr->petType << "\t";
			outfileC << currentPtr->birthMonth << "\t";
			outfileC << currentPtr->birthDay << "\t";
			outfileC << currentPtr->birthYear << "\t";
			outfileC << currentPtr->apptMonth << "\t";
			outfileC << currentPtr->apptDay << "\t";
			outfileC << currentPtr->apptYear << "\n";
		}

		// Write data to mark end of file
		outfileC << "99999" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\t";
		outfileC << "99" << "\n";

		// At end of linked list.
	}


};

