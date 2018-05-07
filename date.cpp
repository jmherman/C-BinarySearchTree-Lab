/* Date class (date.h & date.cpp)
 * Author: Josh Herman
 * this file has/does things with the release date of the album
 */

#include "date.h"
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <iostream>

const int Date::MIN_MONTH = JANUARY;
const int Date::MAX_MONTH = DECEMBER;
const int Date::MIN_YEAR = 0;
const int Date::MIN_DAY = 1;

/* setYear: this function checks and make sure the year is good, and sets it
 * Parameter: y = the year to set
 * if y is correct, it sets year to y
 * otherwise it sets year to 1
 */
void Date::setYear(int y){
    if (y < MIN_YEAR) year = MIN_YEAR;
    else year = y;
}

/* setMonth: this fucntion sets the month
 * Parameter: m = the month to set
 * Sets month to m if m is correct(between 1 and 12) otherwise sets month to 1
 */
void Date::setMonth(int m){
    if(m < MIN_MONTH || m > MAX_MONTH) month = MIN_MONTH;
    else month = m;
}

/* setDay: this fucntion checks and sets the day
 * Parameter: d = the day to set
 * checks to see if the day fits the month, and if it does it will set day to d
 * otherwise it will set day to 1
 */
void Date::setDay(int d){
    int maxDays = daysInMonth();
    if(d < 1 || d > maxDays){
        day = 1;
    }
    else {
        day = d;
    }
    
}

/* setDate: calls the set functions to set the date
 */
void Date::setDate(int inputYear, int inputMonth, int inputDay){
    setYear(inputYear);
    setMonth(inputMonth);
    setDay(inputDay);
}

/* daysInMonth: this function checks to see how many days should be in said month
 * returns: the number of days that is the maximum in the Date's month
 */
int Date::daysInMonth() const {
    int max;
    switch (month){
        case JANUARY: case MARCH: case MAY: case JULY: case AUGUST: case OCTOBER: case DECEMBER:
            max = 31; break;
        case APRIL: case JUNE: case SEPTEMBER: case NOVEMEBER:
            max = 30; break;
        case FEBRUARY:
            //leap year?
            if( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
                max = 29;
            }
            else {
                max = 28;
            }
    }
    return max;
}

Date::Date(){ // default constructor sets the date to today's date
    time_t t = time(NULL);
    tm* tPtr = localtime(&t);
    month = tPtr -> tm_mon;
    day = tPtr -> tm_mday;
    year = tPtr -> tm_year + 1900;
}

Date::Date(int mm, int dd, int yyyy){ // constructor with all 3 parts to the date
    setDate(mm, dd, yyyy);
}

Date::Date(int month, int year){ // constructor with just month and year
    setDate(month, 1, year);
}

Date::Date(int year){ // constructor with just year only
   setDate(0, 1, year);
}

Date::Date(const Date& d){ // copy constructor
    month = d.month;
    day = d.day;
    year = d.year;
}

/* operator+: this function adds the days together
 * Parameters: 2 dates
 * returns the new date
 * NOT USED IN THIS LAB
 */
Date operator+(const Date& d1, const Date& d2){
    int day1 = d1.day;
    int day2 = d2.day;
    
    int temp = day1 + day2; // adds days for the dates
    Date rDate(d1.month, temp, d1.year); //makes new date with the new day
    return rDate;
}

/* operator== checks to see if the day, month, year are the same
 * Parameters: 2 dates
 * returns true if they are the same, false otherwise
 * NOT USED IN THIS LAB
 */
bool operator==(const Date& d1, const Date& d2){
    if(d1.day == d2.day && d1.month == d2.month && d1.year == d2.year){ // if all part are equal
        return true;
    }
    else return false;
}

/* operator-: this function subtracts 6 months from the month
 * returns the new dates
 * NOT USED IN THIS LAB
 */
Date Date::operator-() const{
    return Date(abs(this->month-6), this->day, this->year);
}

/* operator<<: this function prints out the date in a nice format
 * paramters:
 *      outStream: the stream to print
 *      d: the date to print
 * returns outStream when it done
 */
ostream& operator<<(ostream& outStream, const Date& d){
    outStream << setfill( '0' ) << setw(2) <<right<< d.month << '/' << d.day << '/' << setfill(' ')<< setw(4) << d.year; // prints out, sets width and stuff
    return outStream;
}

/* operator>>: this function reads in a date
 * Paramters:
 *      inStream: the read in stream
 *      d: the date to set the data read in equal to
 * returns the inStream when its done
 * NOT USED IN THIS LAB
 */
istream& operator>>(istream& inStream, Date& d){
    inStream >> d.month >> d.day >> d.year;
    d.setMonth(d.month-1); // since user enters 1 for JAN
    return inStream;
}