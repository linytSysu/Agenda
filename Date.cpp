/* Copyright [2014] <liniting> */

#include <iostream>
#include <cstdio>
#include <string>

#include "Date.h"

using std::endl;
using std::string;

Date::Date() {
    year_ = 1000;
    month_ = 1;
    day_ = 1;
    hour_ = 0;
    minute_ = 0;
}
Date::Date(int y, int m, int d, int h, int mi) {
    year_ = y;
    month_ = m;
    day_ = d;
    hour_ = h;
    minute_ = mi;
}

int Date::getYear(void) const {
    return year_;
}
void Date::setYear(int year) {
    year_ = year;
}

int Date::getMonth(void) const {
    return month_;
}
void Date::setMonth(int month) {
    month_ = month;
}

int Date::getDay(void) const {
    return day_;
}
void Date::setDay(int day) {
    day_ = day;
}

int Date::getHour(void) const {
    return hour_;
}
void Date::setHour(int hour) {
    hour_ = hour;
}

int Date::getMinute(void) const {
    return minute_;
}
void Date::setMinute(int minute) {
    minute_ = minute;
}

bool Date::isValid(Date date) {
    int days[12] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = date.getYear();
    int month = date.getMonth();
    int day = date.getDay();
    int hour = date.getHour();
    int minute = date.getMinute();

    if (year < 1000 || year > 9999)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (month != 2 && (day > days[month-1] || day < 1))
        return false;
    if (month == 2) {
        if (year% 400 == 0 || (year% 4 == 0 && year%100 != 0)) {
            if (day < 1 || day > 29)
                return false;
        } else {
            if (day < 1 || day > 28)
                return false;
        }
    }
    if (hour < 0 || hour > 23)
        return false;
    if (minute < 0 || minute > 59)
        return false;
    return true;
}

Date Date::stringToDate(string dateString) {
    string str = dateString;
    int year, month, day, hour, minute;
    year = (str[0]-'0')*1000 + (str[1]-'0')*100;
    year += (str[2]-'0')*10 + (str[3]-'0');
    month = (str[5]-'0')*10 + (str[6]-'0');
    day = (str[8]-'0')*10 + (str[9]-'0');
    hour = (str[11]-'0')*10 + (str[12]-'0');
    minute = (str[14]-'0')*10 + (str[15]-'0');
    return Date(year, month, day, hour, minute);
}

string Date::dateToString(Date date) {
    char s[20];
    int year = date.getYear();
    int month = date.getMonth();
    int day = date.getDay();
    int hour = date.getHour();
    int minute = date.getMinute();
    snprintf(s, sizeof(s), "%d-%02d-%02d/%02d:%02d", year, month,
             day, hour, minute);
    string str = s;
    return str;
}

Date& Date::operator=(const Date& date) {
    year_ = date.getYear();
    month_ = date.getMonth();
    day_ = date.getDay();
    hour_ = date.getHour();
    minute_ = date.getMinute();
    return *this;
}

bool Date::operator==(const Date& date) const {
    string str1 = dateToString(*this);
    string str2 = dateToString(date);
    if (str1 == str2)
        return true;
    else
        return false;
}

bool Date::operator>(const Date& date) const {
    string str1 = dateToString(*this);
    string str2 = dateToString(date);
    if (str1 > str2)
        return true;
    else
        return false;
}

bool Date::operator<(const Date& date) const {
    string str1 = dateToString(*this);
    string str2 = dateToString(date);
    if (str1 < str2)
        return true;
    else
        return false;
}

bool Date::operator>=(const Date& date) const {
    string str1 = dateToString(*this);
    string str2 = dateToString(date);
    if (str1 >= str2)
        return true;
    else
        return false;
}

bool Date::operator<=(const Date& date) const {
    string str1 = dateToString(*this);
    string str2 = dateToString(date);
    if (str1 <= str2)
        return true;
    else
        return false;
}

