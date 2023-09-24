// Vet_clinic_console_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
//#include <ctime>
#include <climits> // INT_MIN, INT_MAX
#include <limits>  // std::numeric_limits::streamsize::max()
#include <stdlib.h>
#include <list>
#include "LinkedListClass.h"
#include "DateCalculatorClass.h"

using namespace std;


int main()
{
	//struct petRecord* headPtr = NULL;		// Pointer to the head of the linked list.
	struct petRecord* matchPtr = NULL;	// pointer to the current node being access or addressed.
	LinkedListClass linkedList;
	dateCalculatorClass dc;
	bool ReadfileOpen = false;
	bool WritefileOpen = false;
	string searchLastName;
	//string newApptDate;

	string ownerLastNameM;
	string ownerFirstNameM;
	string petNameM;
	string petTypeM;
	int birthMonthM;
	int birthDayM;
	int birthYearM;
	int apptMonthM;
	int apptDayM;
	int apptYearM;
	string outFileName;
	string inFileName;

	int i = 0;
	int j = 0;
	int k = 0;
	//int todayDay, todayMonth, todayYear;
	int durationDay, durationMonth, durationYear;
	int mainMenuSelection = 6;

	ifstream infile;
	ofstream outfile;

	/*******************************/
	// Open the pet record data file for reading
	inFileName = "PetDataBase.txt";

	infile.open(inFileName);
	if (infile.is_open()) {
		cout << "Read file:\t" << inFileName << endl;
		ReadfileOpen = true;
	}
	else {
		cout << "Read file does NOT exit" << endl;
		ReadfileOpen = false;
	}

	/*******************************/
	// Open file for writing
	// Opening the file once and writing it at various points in the menu
	// causes it to append rather than truncate. The file must be closed
	// then reopened to truncate.
	outFileName = "PetDataBase_03.txt";
	cout << "Write file:\t" << outFileName << endl;


	// Get today's date in integer values and store in class object
	dc.getTodaysDate();

	// Read in the database from the text file.
	linkedList.initLinkedList(infile);

	/**********************************************************/
	// Stay in mian menu until the user selects exit (e.g., 5).
	while ((mainMenuSelection < 9) && (mainMenuSelection > 0)) {

		cout << endl;
		cout << "\t\tSunnyside Vet Clinic" << endl;
		cout << "1.\tFind Record" << endl;
		cout << "2.\tSet Appointment" << endl;
		cout << "3.\tEnter New Record" << endl;
		cout << "4.\tRemove Record" << endl;
		cout << "5.\tPrint Last Names" << endl;
		cout << "6.\tPrint all records" << endl;
		cout << "7.\tWrite records to file" << endl;
		cout << "8.\tExit Program" << endl << endl;
		cout << "Enter Selection (1, 2, 3, 4, 5, 6, 7 or 8):\t";
		cin >> mainMenuSelection;

		switch (mainMenuSelection) {
		case 1:
			cout << endl;
			cout << "1. Find a record" << endl;
			cout << "Enter Owner Last Name (e.g., Smith):\t";
			cin >> ownerLastNameM;
			cout << endl;
			searchLastName = ownerLastNameM;
			matchPtr = linkedList.findRecordByLastName(ownerLastNameM);
			if (matchPtr == NULL) cout << "Record not found" << endl;
			else {
				linkedList.displaySingleNode(matchPtr);
				dc.dateCalculator(matchPtr->birthMonth, matchPtr->birthDay, matchPtr->birthYear, &durationMonth, &durationDay, &durationYear);
				cout << "Age of\t" << matchPtr->petName << ":\t\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;

				dc.dateCalculator(matchPtr->apptMonth, matchPtr->apptDay, matchPtr->apptYear, &durationMonth, &durationDay, &durationYear);
				cout << "Time to next appt:\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;
			}
			break;
		case 2:
			cout << endl;
			cout << "2. Set an appointment" << endl;
			cout << "Enter Owner Last Name (e.g., Smith):\t";
			cin >> ownerLastNameM;
			cout << endl;
			searchLastName = ownerLastNameM;
			matchPtr = linkedList.findRecordByLastName(ownerLastNameM);
			if (matchPtr == NULL) cout << "Record not found" << endl;
			else {
				linkedList.displaySingleNode(matchPtr);

				dc.dateCalculator(matchPtr->birthMonth, matchPtr->birthDay, matchPtr->birthYear, &durationMonth, &durationDay, &durationYear);
				cout << "Age of\t" << matchPtr->petName << ":\t\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;

				dc.dateCalculator(matchPtr->apptMonth, matchPtr->apptDay, matchPtr->apptYear, &durationMonth, &durationDay, &durationYear);
				cout << "Time to next appt:\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;

				cout << "Enter new appointment month (1, 2, 3 . . . 12):\t";
				cin >> apptMonthM;
				cout << "Enter new appointment day (1, 2, 3 . . . 31):\t";
				cin >> apptDayM;
				cout << "Enter new appointment Year (YYYY):\t";
				cin >> apptYearM;

				linkedList.newApptDate(matchPtr, apptMonthM, apptDayM, apptYearM);
				linkedList.displaySingleNode(matchPtr);
				dc.dateCalculator(matchPtr->birthMonth, matchPtr->birthDay, matchPtr->birthYear, &durationMonth, &durationDay, &durationYear);
				cout << "Age of\t" << matchPtr->petName << ":\t\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;

				dc.dateCalculator(matchPtr->apptMonth, matchPtr->apptDay, matchPtr->apptYear, &durationMonth, &durationDay, &durationYear);
				cout << "Time to next appt:\t" <<
					durationYear << " year  " <<
					durationMonth << " month  " <<
					durationDay << " day" << endl;

				//cout << "New appointment date set" << endl;
			}

			// Write linked list to output file
			//cout << "Writing change to output file:" << outFileName << endl;
			outfile.open(outFileName, ios::trunc);
			if (outfile.is_open()) {
				//cout << "Write file:\t" << outFileName << endl;
				WritefileOpen = true;
				linkedList.WriteLinkedList(outfile);
			}
			else {
				cout << "Write file does NOT exit" << endl;
				cout << "Data not written" << endl;
				WritefileOpen = false;
			}
			outfile.close();

			break;
		case 3:
			cout << endl;
			cout << "3. Enter a new record" << endl;
			cout << "Enter owner's last name:\t";
			cin >> ownerLastNameM;
			cout << "Enter owner's first name:\t";
			cin >> ownerFirstNameM;
			cout << "Enter pet's name:\t";
			cin >> petNameM;
			cout << "Enter pet type (single word with no spaces (e.g., guineapig, dog):\t";
			cin >> petTypeM;
			cout << "Enter pet birth month (1, 2, 3 . . . 12):\t";
			cin >> birthMonthM;
			cout << "Enter pet birth day (1, 2, 3 . . . 31):\t";
			cin >> birthDayM;
			cout << "Enter pet birth year (YYYY):\t";
			cin >> birthYearM;
			cout << "Enter next appointment month (1, 2, 3 . . . 12):\t";
			cin >> apptMonthM;
			cout << "Enter next appointment day (1, 2, 3 . . . 31):\t";
			cin >> apptDayM;
			cout << "Enter next appointment year (YYYY):\t";
			cin >> apptYearM;
			matchPtr = linkedList.addNewRecord(ownerLastNameM, ownerFirstNameM, petNameM, petTypeM,
				birthMonthM, birthDayM, birthYearM, apptMonthM, apptDayM, apptYearM);
			linkedList.displaySingleNode(matchPtr);
			dc.dateCalculator(matchPtr->birthMonth, matchPtr->birthDay, matchPtr->birthYear, &durationMonth, &durationDay, &durationYear);
			cout << "Age of\t" << matchPtr->petName << ":\t\t" <<
				durationYear << " year  " <<
				durationMonth << " month  " <<
				durationDay << " day" << endl;

			dc.dateCalculator(matchPtr->apptMonth, matchPtr->apptDay, matchPtr->apptYear, &durationMonth, &durationDay, &durationYear);
			cout << "Time to next appt:\t" <<
				durationYear << " year  " <<
				durationMonth << " month  " <<
				durationDay << " day" << endl;

			// Write linked list to output file
			//cout << "Writing change to output file:" << outFileName << endl;
			outfile.open(outFileName, ios::trunc);
			if (outfile.is_open()) {
				//cout << "Write file:\t" << outFileName << endl;
				WritefileOpen = true;
				linkedList.WriteLinkedList(outfile);
			}
			else {
				cout << "Write file does NOT exit" << endl;
				cout << "Data not written" << endl;
				WritefileOpen = false;
			}
			outfile.close();

			break;
		case 4:
			cout << endl;
			cout << "4. Remove record" << endl;
			cout << "Enter owner's last name:\t";
			cin >> ownerLastNameM;
			i = linkedList.deleteRecordByLastName(ownerLastNameM);
			if (i == 1) cout << ownerLastNameM << "\trecord deleted" << endl;
			else cout << ownerLastNameM << "\trecord not found" << endl;

			// Write linked list to output file
			//cout << "Writing change to output file:" << outFileName << endl;
			outfile.open(outFileName, ios::trunc);
			if (outfile.is_open()) {
				//cout << "Write file:\t" << outFileName << endl;
				WritefileOpen = true;
				linkedList.WriteLinkedList(outfile);
			}
			else {
				cout << "Write file does NOT exit" << endl;
				cout << "Data not written" << endl;
				WritefileOpen = false;
			}
			outfile.close();

			break;
		case 5:
			cout << endl;
			cout << "5. Print last names" << endl;
			linkedList.displayLastNames();
			break;
		case 6:
			cout << endl;
			cout << "6. Print all records" << endl;
			linkedList.displayLinkedList();
			break;
		case 7:
			cout << endl;
			cout << "7. Write records to file" << endl;

			// Write linked list to output file
			//cout << "Writing all data to output file:" << outFileName << endl;
			outfile.open(outFileName, ios::trunc);
			if (outfile.is_open()) {
				cout << "Write file:\t" << outFileName << endl;
				WritefileOpen = true;
				linkedList.WriteLinkedList(outfile);
			}
			else {
				cout << "Write file does NOT exit" << endl;
				cout << "Data not written" << endl;
				WritefileOpen = false;
			}
			outfile.close();

			break;
		case 8:
			cout << endl;
			cout << "8. Exit" << endl;
			mainMenuSelection = 9;
			break;
		default:
			cout << "Entry not valid" << endl;
			cout << "Clearing input buffer" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//cout << "Enter new selection:\t";
			//cin >> mainMenuSelection; // program does not allow reentry when "a" is entered
			mainMenuSelection = 8;
			//cout << "Program exiting" << endl;
		}

	}

	// close the file.
	infile.close();


}
