#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <bitset>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <climits> // INT_MIN, INT_MAX
#include <ctime>

using namespace std;


// functions in dateCalculatorClass
// 	void dateCalculator(int endMonth, int endDay, int endYear, int* diffMonthPtr, int* diffDayPtr, int* diffYearPtr)
// 	void todayDate(int* todayMonthS, int* todayDayS, int* todayYearS)
// 	void getTodaysDate()
// 	bool isLeapYear(int year)


class dateCalculatorClass
{
	// This date calculator calculates the total number of days between the startDate
	// and the endDate then converts the number of days into the no. of days, months and years
	// between the startDate and the endDate.
	// The no. of days between startDate and endDate is stored in diffDate which is passed to
	// the class.

private:
	int i = 0;
	int	sDay = 0, sMonth = 0, sYear = 0; // start year date
	int	eDay = 0, eMonth = 0, eYear = 0; // end year date
	int durationDay = 0, durationMonth = 0, durationYear = 0; //days, months, years between start date and end date
	bool leapYear = false;
	bool outputFlag = false;

	//const int daysInMonthsNonLeap[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// Sometimes you have to look at the number of days in the prior month. If the month is jan, then
	// going back one month is outside of the array. Add dec as the month in [0] and access the 
	// array by the month number to get the number of days for the month
	// dec, jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	int daysInMonthsNonLeap[13] = { 31,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysInMonthsLeap[13] = { 31,31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int* daysInMonthPtr;
	const int monthsInYear = 12;

	char buff[26]; // an array of characters to get the date and time from now.
	time_t now = time(0); // seconds since 01/01/1970. time_t class
	// Store today's date as integer values.
	int todayMonth;
	int todayDay;
	int todayYear;

public:

	/***************************************/
	// determine if the year is a leap year.
	// return 1 if leap year.
	// return 0 if not leap year.
	// Used only in this class, so made private
	bool isLeapYear(int year) {
		if (
			(((year % 4) == 0) && ((year % 100) != 0)) ||
			(((year % 4) == 0) && ((year % 100) == 0) && ((year % 400) == 0)))
			leapYear = true;
		else leapYear = false;

		//if (leapYear) cout << year << "  Leap Year" << endl;

		return (leapYear);
	}

	/***************************************/
	// This is an overloaded version of dataCalcualator that sets the start date, sDate, to today's date
	void dateCalculator(int endMonth, int endDay, int endYear, int* diffMonthPtr, int* diffDayPtr, int* diffYearPtr) {

		sMonth = todayMonth;
		sDay = todayDay;
		sYear = todayYear;

		dateCalculator (todayMonth, todayDay, todayYear,
			endMonth, endDay, endYear,
			diffMonthPtr, diffDayPtr, diffYearPtr);
}



	/***************************************/
	// function to calculate duration between between startDate and endDate.
	// calculation is done in Years, Months and Days. Days are not counted between
	// the start date sdate and the end date eDate.
	// Make start Date (e.g., sDate) always equal to today's date. if the eDate that is pass is before the
	// sDate, the dates will be swapped before the calculation is performed.
	void dateCalculator(int startMonth, int startDay, int startYear, 
		int endMonth, int endDay, int endYear, 
		int* diffMonthPtr, int* diffDayPtr, int* diffYearPtr) {

		// Transfer dates passed to subroutine to local variables
		sMonth = startMonth;
		sDay = startDay;
		sYear = startYear;

		eMonth = endMonth;
		eDay = endDay;
		eYear = endYear;

		outputFlag = false;

		// check limits on days in months and numver of months
		// Fix some of the possible errors in dates
		if (sYear < 0) {
			sYear = 0;
			outputFlag = true;
		}

		if (eYear < 0) {
			eYear = 0;
			outputFlag = true;
		}

		if (sMonth < 1) {
			sMonth = 1;
			outputFlag = true;
		}
		else if (sMonth > monthsInYear) {
			sMonth = 12;
			outputFlag = true;
		}

		if (eMonth < 1) {
			eMonth = 1;
			outputFlag = true;
		}
		else if (eMonth > monthsInYear) {
			eMonth = 12;
			outputFlag = true;
		}

		// If end date is before the start date, swap the dates and calculate
		// the years, months and days in between.
		if ((sYear > eYear) ||
			((sYear == eYear) && (sMonth > eMonth)) ||
			((sYear == eYear) && (sMonth == eMonth)) && (sDay > eDay)) {
			//cout << "End date occurs before Start date: switching dates" << endl;
			sMonth = endMonth;
			sDay = endDay;
			sYear = endYear;

			eMonth = startMonth;
			eDay = startDay;
			eYear = startYear;

			outputFlag = true;
		}

		//if (outputFlag) {
		//	cout << "Now from\t" << sMonth << "/" << sDay << "/" << sYear;
		//	cout << "\tto\t" << eMonth << "/" << eDay << "/" << eYear << endl;
		//}

		// Note: 03/31/1987 to 05/05/1987 is counted as follows:
		// 03/31/1987 - 04/30/1987 = 1 month even though there are not 31 days in April because a month past.
		// 04/30/1987 - 05/05/1987 is counted as 5 days.
		// total: 0 years, 1 month 5 days.
		// 01/31/1987 to 03/05/1987 is counted as follows:
		// 01/31/1987 - 02/28/1987 = 1 month even though there are not 31 days in February because a month past.
		// 02/28/1987 - 03/05/1987 is counted as 5 days.
		// total: 0 years, 1 month 5 days.


		durationYear = 0;
		durationMonth = 0;
		durationDay = 0;

		///////////////////////////////////////////////
		// Start counting years, months and days between sDate and eDate.
		// cases: 0x000, 10, 12
		if ((sYear <= eYear) && (sMonth <= eMonth) && (sDay <= eDay)) {
			durationYear = eYear - sYear;
			durationMonth = eMonth - sMonth;
			durationDay = eDay - sDay;
		}

		// case 0x001
		//else if ((sYear <= eYear) && (sMonth < eMonth) && (sDay > eDay)) { // may need this
		//else if ((sYear <= eYear) && (sMonth <= eMonth) && (sDay > eDay)) {

		else if ((sYear <= eYear) && (sMonth < eMonth) && (sDay > eDay)) {
			durationYear = eYear - sYear;
			durationMonth = (eMonth - 1) - sMonth;
			if (isLeapYear(eYear) && ((eMonth - 1) == 2)) {
				daysInMonthPtr = daysInMonthsLeap;
			}
			else {
				daysInMonthPtr = daysInMonthsNonLeap;
			}

			// if sDays > the no. of days in the month before sMonth, skip the whole month and just
			// count the days of eMonth.
			if (sDay > *(daysInMonthPtr + (eMonth - 1))) {
				durationDay = eDay;
			}
			else {
				durationDay = (*(daysInMonthPtr + (eMonth - 1)) - sDay) + eDay;
			}
		}

		// case 0x010
		else if ((sYear < eYear) && (sMonth > eMonth) && (sDay <= eDay)) {
			durationYear = (eYear - 1) - sYear;
			durationMonth = (monthsInYear - sMonth) + eMonth;
			durationDay = eDay - sDay;
		}

		// case 0x011
		else if ((sYear < eYear) && (sMonth >= eMonth) && (sDay > eDay)) {
			durationYear = (eYear - 1) - sYear;
			durationMonth = (monthsInYear - sMonth) + (eMonth - 1);
			if (isLeapYear(eYear) && ((eMonth - 1) == 2)) {
				daysInMonthPtr = daysInMonthsLeap;
			}
			else {
				daysInMonthPtr = daysInMonthsNonLeap;
			}

			// if sDays > the no. of days in the month before sMonth, skip the whole month and just
			// count the days of eMonth.
			if (sDay > *(daysInMonthPtr + (eMonth - 1))) {
				durationDay = eDay;
			}
			else {
				durationDay = (*(daysInMonthPtr + (eMonth - 1)) - sDay) + eDay;
			}
		}

		// unknown case
		else {
			cout << "Unknown Case" << endl;
		}

		*diffYearPtr = durationYear;
		*diffMonthPtr = durationMonth;
		*diffDayPtr = durationDay;
	}

	/***************************************/
	// Use a class function to get the current data a time.
	// Extract the date and convert to interger values.
	void todayDate(int* todayMonthS, int* todayDayS, int* todayYearS) {

		//time_t now = time(0); // seconds since 01/01/1970
		//cout << "now: " << now << endl;
		//now = now - 28 * (31536000) - 8 * (2592000) - 3 * (86400); // for changing date to see changes in buff.
		//cout << "now: " << now << endl;
		//char buff[26]; // an array of characters to get the date and time from now.
		ctime_s(buff, sizeof buff, &now); // convert now to data and time
		cout << "Local date and time: " << buff << endl;

		// convert month to int number
		// buff [4][5][6] = Jan, Feb, Mar, Apr, so forth
		switch (buff[4]) {
		case 'F':
			*todayMonthS = 2;
			break;
		case 'S':
			*todayMonthS = 9;
			break;
		case 'O':
			*todayMonthS = 10;
			break;
		case 'N':
			*todayMonthS = 11;
			break;
		case 'D':
			*todayMonthS = 12;
			break;
		case 'M':
			if (buff[6] == 'r') *todayMonthS = 3;
			else *todayMonthS = 5;
			break;
		case 'A':
			if (buff[5] == 'p') *todayMonthS = 4;
			else *todayMonthS = 8;
			break;
		case 'J':
			if ((buff[5] == 'u') && (buff[6] == 'n')) *todayMonthS = 6;
			else if ((buff[5] == 'a') && (buff[6] == 'n')) *todayMonthS = 1;
			else *todayMonthS = 7;
			break;
		default:
			cout << "Problem finding Month of current date" << endl;
		}

		// convert day to int number
		// refer to ascii table.
		// buffer above has: [8] [9]: ' ' '1' - '9'
		//                   [8] [9]: '1' '0' - '9'
		//                   [8] [9]: '2' '0' - '9'
		//                   [8] [9]: '3' '0' - '1'
		if (buff[8] == ' ') {
			*todayDayS = buff[9] - 0x30;
		}
		else if ((buff[8] == '1') || (buff[8] == '2') || (buff[8] == '3')) {
			*todayDayS = ((buff[8] - 0x30) * 10) + (buff[9] - 0x30);
		}

		// convert year to int number
		// refer to ascii table.
		// buffer above has: [20] [21] [22] [23]: '1 - 9' '0 - 9' '0 - 9' '0 - 9'
		// 1970 - 9999
		*todayYearS = ((buff[20] - 0x30) * 1000) + ((buff[21] - 0x30) * 100) + ((buff[22] - 0x30) * 10) + ((buff[23] - 0x30) * 1);

		cout << "Today's date M/D/YYYY = " << *todayMonthS << "/" << *todayDayS << "/" << *todayYearS << endl;


	}

	/***************************************/
	// Use a class function to get the current data a time.
	// Extract the date and convert to interger values.
	// Use the standard library time function to get today's date then
	// convert into interger values that are stored in the class object.
	void getTodaysDate() {

		ctime_s(buff, sizeof buff, &now); // convert now to data and time
		cout << "Local date and time: " << buff << endl;

		// convert month to int number
		// buff [4][5][6] = Jan, Feb, Mar, Apr, so forth
		switch (buff[4]) {
		case 'F':
			todayMonth = 2;
			break;
		case 'S':
			todayMonth = 9;
			break;
		case 'O':
			todayMonth = 10;
			break;
		case 'N':
			todayMonth = 11;
			break;
		case 'D':
			todayMonth = 12;
			break;
		case 'M':
			if (buff[6] == 'r') todayMonth = 3;
			else todayMonth = 5;
			break;
		case 'A':
			if (buff[5] == 'p') todayMonth = 4;
			else todayMonth = 8;
			break;
		case 'J':
			if ((buff[5] == 'u') && (buff[6] == 'n')) todayMonth = 6;
			else if ((buff[5] == 'a') && (buff[6] == 'n')) todayMonth = 1;
			else todayMonth = 7;
			break;
		default:
			cout << "Problem finding Month of current date" << endl;
		}

		// convert day to int number
		// refer to ascii table.
		// buffer above has: [8] [9]: ' ' '1' - '9'
		//                   [8] [9]: '1' '0' - '9'
		//                   [8] [9]: '2' '0' - '9'
		//                   [8] [9]: '3' '0' - '1'
		if (buff[8] == ' ') {
			todayDay = buff[9] - 0x30;
		}
		else if ((buff[8] == '1') || (buff[8] == '2') || (buff[8] == '3')) {
			todayDay = ((buff[8] - 0x30) * 10) + (buff[9] - 0x30);
		}

		// convert year to int number
		// refer to ascii table.
		// buffer above has: [20] [21] [22] [23]: '1 - 9' '0 - 9' '0 - 9' '0 - 9'
		// 1970 - 9999
		todayYear = ((buff[20] - 0x30) * 1000) + ((buff[21] - 0x30) * 100) + ((buff[22] - 0x30) * 10) + ((buff[23] - 0x30) * 1);

		cout << "Today's date M/D/YYYY = " << todayMonth << "/" << todayDay << "/" << todayYear << endl;
	}



};

