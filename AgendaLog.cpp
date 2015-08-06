/* Copyright [2014] <linyting> */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctime>
#include <cstdio>

using std::string;
using std::ios;
using std::list;
using std::endl;

#include "AgendaLog.h"

AgendaLog* AgendaLog::instance_ = 0;

AgendaLog::AgendaLog() {}

AgendaLog* AgendaLog::getInstance() {
    if (instance_ != 0) {
        delete AgendaLog::instance_;
    }
    AgendaLog::instance_ = new AgendaLog;
    return AgendaLog::instance_;
}

AgendaLog::~AgendaLog() {
    AgendaLog::instance_ = 0;
}

bool AgendaLog::writeToFile(const char* fpath) {
    std::ofstream ofs;
    ofs.open(fpath, ios::app);
    if (ofs.fail()) {
        return false;
    }
    list<string>::iterator its;
    for (its = listLog.begin(); its != listLog.end(); its++) {
        ofs << (*its) << endl;
    }
}

void AgendaLog::addString(string as) {
    string time = "[time]:";
    time += getNowTime();
    listLog.push_back(time);
    listLog.push_back(as);
}

string AgendaLog::getNowTime() {
    time_t t = time(0); 
    char tmp[64]; 
    strftime(tmp, sizeof(tmp), "%Y-%m-%d/%X",localtime(&t)); 
    string time = tmp; 
    return time; 
}

bool AgendaLog::sync() {
    return writeToFile("agendaLog.data");
}

void AgendaLog::startAgenda() {
    string add = "start agenda\n";
    addString(add);
}

void AgendaLog::userLogInSucceed(string na) {
    string add = "User "+na+" : ";
    add += "log in succeed\n";
    addString(add);
}

void AgendaLog::userLogInFail(string na) {
    string add = "User "+na+" : ";
    add += "log in fail\n";
    addString(add);
}

void AgendaLog::userRegisterSucceed(string na, string pw, string em, string ph) {
    string add = "User "+na+" : ";
    add += "register succeed\n";
    add += "password:";
    add += pw;
    add += ", email:";
    add += em;
    add += ", phone:";
    add += ph;
    add += "\n";
    addString(add);
}

void AgendaLog::userRegisterFail(string na, string pw, string em, string ph) {
    string add = "User "+na+" : ";
    add += "register fail\n";
    add += "password:";
    add += pw;
    add += ", email:";
    add += em;
    add += ", phone:";
    add += ph;
    add += "\n";
    addString(add);
}

void AgendaLog::quitAgenda() {
    string add = "quit agenda\n";
    addString(add);
    sync();
}

void AgendaLog::userLogOut(string userName_) {
    string add = "User "+userName_;
    add += " : log out\n";
    addString(add);
}

void AgendaLog::deleteUserSucceed(string userName_) {
    string add = "User "+userName_+" : ";
    add += "delete itself succeed!\n";
    addString(add);
}

void AgendaLog::deleteUserFail(string userName_) {
    string add = "User "+userName_+" : ";
    add += "delete itself fail\n";
    addString(add);
}

void AgendaLog::listAllUsers(string userName_) {
    string add = "User "+userName_+" : ";
    add += "list all user\n";
    addString(add);
}

void AgendaLog::createMeetingSucceed(string userName_, string title, string pa, string sd, string ed) {
    string add = "User "+userName_+" : ";
    add += " create a meeting succeed:\n";
    add += "    participator: ";
    add += pa;
    add += ", title: ";
    add += title;
    add += ", start date: ";
    add += sd;
    add += ", end date: ";
    add += ed;
    add += "\n";
    addString(add);
}

void AgendaLog::createMeetingFail(string userName_){
    string add = "User "+userName_+" : ";
    add += " create a meeting fail\n";
    addString(add);
}

void AgendaLog::listAllMeetings(string userName_) {
    string add = "User "+userName_+" : ";
    add += "list all meetings\n";
    addString(add);
}

void AgendaLog::listAllSponsorMeetings(string userName_) {
    string add = "User "+userName_+" : ";
    add += "list all sponsor meetings\n";
    addString(add);
}

void AgendaLog::listAllParticipateMeetings(string userName_) {
    string add = "User "+userName_+" : ";
    add += "list all participator meetings\n";
    addString(add);
}

void AgendaLog::queryMeetingByTitle(string userName_, string title) {
    string add = "User "+userName_+" : ";
    add += "query meetings by title: ";
    add += title;
    add += "\n";
    addString(add);
}

void AgendaLog::queryMeetingByTimeInterval(string userName_, string startDate, string endDate) {
    string add = "User "+userName_+" : ";
    add += "query meetings by time:\n";
    add += "start time: ";
    add += startDate;
    add += " end time: ";
    add += endDate;
    add += "\n";
    addString(add);
}

void AgendaLog::deleteMeetingByTitleSucceed(string userName_, string title) {
    string add = "User "+userName_+" : ";
    add += "delete meetings succeed by title : ";
    add += title;
    add += "\n";
    addString(add);
}

void AgendaLog::deleteMeetingByTitleFail(string userName_, string title) {
    string add = "User "+userName_+" : ";
    add += "delete meetings fail by title : ";
    add += title;
    add += "\n";
    addString(add);
}

void AgendaLog::deleteAllMeetingsSucceed(string userName_) {
    string add = "User "+userName_+" : ";
    add += "delete all meetings succeed\n";
    addString(add);
}

void AgendaLog::deleteAllMeetingsFail(string userName_) {
    string add = "User "+userName_+" : ";
    add += "delete all meetings fail\n";
    addString(add);
}
