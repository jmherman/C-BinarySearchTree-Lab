/* Date class (date.h & date.cpp)
 * Author: Josh Herman
 * this file has/does things with the release date of the album
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

enum month_t {JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMEBER, DECEMBER };

class Date {
public:
    static const int MIN_MONTH;
    static const int MAX_MONTH;
    static const int MIN_YEAR;
    static const int MIN_DAY;
    
    int getYear() const {return year;}
    void setYear(int y);
    void setMonth(int m);
    int getMonth() const {return month;}
    void setDay(int d);
    int getDay() const {return day;}
    void setDate(int inputYear, int inputMonth, int inputDay);
    Date operator-() const;
    
    //friends
    friend Date operator+(const Date& d1, const Date& d2);
    friend bool operator==(const Date& d1, const Date& d2);
    friend ostream& operator<<(ostream& outStream, const Date& d);
    friend istream& operator>>(istream& inStream, Date& d);
    
    //constructors
    Date();//default
    Date(int, int, int);//month, day, year
    Date(int, int);//month, year 
    Date(int); //year
    virtual ~Date() {}
    Date(const Date& d);
    
    template<class T> friend class BinarySearchTree;
    friend class Album;

private:
    int month; // 0 = january
    int day;
    int year;
    int daysInMonth() const ;
};

Date operator+(const Date& d1, const Date& d2);
bool operator==(const Date& d1, const Date& d2);
ostream& operator<<(ostream& outStream, const Date& d);
istream& operator>>(istream& inStream, Date& d);
#endif