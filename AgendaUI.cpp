/* Copyright [2014] <linyiting> */

#include "AgendaUI.h"

#include <iostream>
#include <list>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;
using std::list;

AgendaUI::AgendaUI() {
    userName_ = "";
    userPassword_ = "";
    agendaLog_ = AgendaLog::getInstance();
}

void show1(void) {
    cout << endl;
    cout << "------------------------ Agenda ------------------------" << endl;
    cout << "Actions :" << endl;
    cout << "l - log in Agenda by user name and password" << endl;
    cout << "r - register an Agenda count" << endl;
    cout << "q - quit Agenda" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;
    cout << "Agenda : ~$  ";
}

void show2(void) {
    cout << endl;
    cout << "------------------------ Agenda ------------------------" << endl;
    cout << "Actions :" << endl;
    cout << "o   - log out Agenda" << endl;
    cout << "dc  - delete Agenda account" << endl;
    cout << "lu  - list all Agenda user" << endl;
    cout << "cm  - create a meeting" << endl;
    cout << "la  - list all meetings" << endl;
    cout << "las - list all sponsor meetings" << endl;
    cout << "lap - list all participator meetings" << endl;
    cout << "qm  - query meeting by title" << endl;
    cout << "qt  - query meeting bu time interval" << endl;
    cout << "dm  - delete meeting by title" << endl;
    cout << "da  - delete all meetings" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;
}

void AgendaUI::OperationLoop(void) {
    startAgenda();
    show1();
    string op = getOperation();
    while (op != "q") {
        executeOperation(op);
        if (userName_ == "") {
            show1();
        }
        if (userName_ != "") {
            show2();
            cout << "Agenda@" << userName_ << " #  ";
        } else {
            op = getOperation();
        }
        while (userName_ != "" && op != "o") {
            op = getOperation();
            if (op == "o") {
                agendaLog_->userLogOut(userName_);
                userName_ = "";
                userPassword_ = "";
                show1();
                op = getOperation();
                break;
            }
            executeOperation(op);
            if (userName_ != "") {
                show2();
                cout << "Agenda@" << userName_ << " #  ";
            }
        }
    }
    quitAgenda();
}

void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
    agendaLog_->startAgenda();
}
string AgendaUI::getOperation() {
    string op;
    cin >> op;
    return op;
}
bool AgendaUI::executeOperation(string op) {
    if (userName_ == "" && op == "l") {
        userLogIn();
        return true;
    }
    if (userName_ == "" && op == "r") {
        userRegister();
        return true;
    }
    if (userName_ == "" && op == "q") {
        quitAgenda();
        return true;
    }
    if (userName_ != "" && op == "o") {
        userLogOut();
        return true;
    }
    if (userName_ != "" && op == "dc") {
        deleteUser();
        return true;
    }
    if (userName_ != "" && op == "lu") {
        listAllUsers();
        return true;
    }
    if (userName_ != "" && op == "cm") {
        createMeeting();
        return true;
    }
    if (userName_ != "" && op == "la") {
        listAllMeetings();
        return true;
    }
    if (userName_ != "" && op == "las") {
        listAllSponsorMeetings();
        return true;
    }
    if (userName_ != "" && op == "lap") {
        listAllParticipateMeetings();
        return true;
    }
    if (userName_ != "" && op == "qm") {
        queryMeetingByTitle();
        return true;
    }
    if (userName_ != "" && op == "qt") {
        queryMeetingByTimeInterval();
        return true;
    }
    if (userName_ != "" && op == "dm") {
        deleteMeetingByTitle();
        return true;
    }
    if (userName_ != "" && op == "da") {
        deleteAllMeetings();
        return true;
    }
    return false;
}
void AgendaUI::userLogIn(void) {
    cout << endl;
    cout << "[log in] [user name] [password]" << endl;
    cout << "[log in] ";
    string na, pw;
    cin >> na >> pw;
    if (!agendaService_.userLogIn(na, pw)) {
        cout << "[error] log in fail!" << endl;
        agendaLog_->userLogInFail(na);
    } else {
        userName_ = na;
        userPassword_ = pw;
        cout << "[log in] succeed!" << endl; 
        agendaLog_->userLogInSucceed(na);
    }
}
void AgendaUI::userRegister(void) {
    string na, pw, em, ph;
    cout << "[register] [username] [password] [email] [phone]" << endl;
    cout << "[register] ";
    cin >> na >> pw >> em >> ph;
    if (agendaService_.userRegister(na, pw, em, ph)) {
        cout << "[register] succeed!" << endl;
        agendaLog_->userRegisterSucceed(na, pw, em, ph);
    } else {
        cout << "[error] register fail!" << endl;
        agendaLog_->userRegisterFail(na, pw, em, ph);
    }
}
void AgendaUI::quitAgenda(void) {
    agendaLog_->quitAgenda();
    agendaService_.quitAgenda();
    delete agendaLog_;
    agendaLog_ = 0;
}
void AgendaUI::userLogOut(void) {
}
void AgendaUI::deleteUser(void) {
    cout << "[delete agenda account] ";
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        agendaLog_->deleteUserSucceed(userName_);
        cout << " succeed!" << endl;
        userName_ = "";
        userPassword_ = "";
    } else {
        agendaLog_->deleteUserFail(userName_);
        cout << " delete user fail!" << endl;
    }
}
void AgendaUI::listAllUsers(void) {
    agendaLog_->listAllUsers(userName_);
    cout << "[list all users]" << endl;
    cout << endl;
    cout << left;
    cout << setw(12) << "name" << setw(15) << "email" << "phone" << endl;
    list<User> lu = agendaService_.listAllUsers();
    list<User>::iterator it;
    for (it = lu.begin(); it != lu.end(); it++) {
        cout << setw(12) << (*it).getName()
             << setw(15) << (*it).getEmail()
             << (*it).getPhone() << endl;
    }
}
void AgendaUI::createMeeting(void) {
    cout << "[create meeting] [title] [participator] "
         << "[start time(yyyy-mm-dd/hh:mm)] "
         << "[end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] ";
    string ti, pa, sd, ed;
    cin >> ti >> pa >> sd >> ed;
    if (agendaService_.createMeeting(userName_, ti, pa, sd, ed)) {
        agendaLog_->createMeetingSucceed(userName_, ti, pa, sd, ed);
        cout << "[create meeting] succeed!" << endl;
    } else {
        agendaLog_->createMeetingFail(userName_);
        cout << "[create meeting] create meeting fail!" << endl;
    }
}
void AgendaUI::listAllMeetings(void) {
    cout << "[list all meetings]" << endl;
    list<Meeting> lm = agendaService_.listAllMeetings(userName_);
    printMeetings(lm);
    agendaLog_->listAllMeetings(userName_);
}
void AgendaUI::listAllSponsorMeetings(void) {
    cout << "[list all sponsor meetings]" << endl;
    list<Meeting> lm = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(lm);
    agendaLog_->listAllSponsorMeetings(userName_);
}
void AgendaUI::listAllParticipateMeetings(void) {
    cout << "[list all participator meetings]" << endl;
    list<Meeting> lm = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(lm);
    agendaLog_->listAllParticipateMeetings(userName_);
}
void AgendaUI::queryMeetingByTitle(void) {
    cout << "[query meeting] [title]:" << endl;
    cout << "[query meeting] ";
    string ti;
    cin >> ti; 
    list<Meeting> lm = agendaService_.meetingQuery(userName_, ti);
    printMeetings(lm);
    agendaLog_->queryMeetingByTitle(userName_, ti);
}
void AgendaUI::queryMeetingByTimeInterval(void) {
    cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] "
         << "[end time(yyyy-mm-dd/hh:mm)]:"<< endl;
    cout << "[query meeting] ";
    string sd, ed;
    cin >> sd >> ed;
    list<Meeting> lm = agendaService_.meetingQuery(userName_, sd, ed);
    printMeetings(lm);
    agendaLog_->queryMeetingByTimeInterval(userName_, sd, ed);
}
void AgendaUI::deleteMeetingByTitle(void) {
    cout << "[delete meeting] [title]:" << endl;
    cout << "[delete meeting] ";
    string ti;
    cin >> ti;
    if (agendaService_.deleteMeeting(userName_, ti)) {
        agendaLog_->deleteMeetingByTitleSucceed(userName_, ti);
        cout << "[delete meeting by title] succeed!" << endl;
    } else {
        agendaLog_->deleteMeetingByTitleFail(userName_, ti);
        cout << "[error] delete meeting fail!" << endl;
    }
}
void AgendaUI::deleteAllMeetings(void) {
    if (agendaService_.deleteAllMeetings(userName_)) {
        agendaLog_->deleteAllMeetingsSucceed(userName_);
        cout << "[delete all meeting] succeed!" << endl;
    } else {
        agendaLog_->deleteAllMeetingsFail(userName_);
        cout << "[error] delete meeting fail!" << endl;
    }
}
void AgendaUI::printMeetings(list<Meeting> meetings) {
    list<Meeting>::iterator it;
    cout << endl;
    cout << left;
    cout << setw(12) << "title" << setw(12) << "sponsor"
         << setw(15) << "participator" << setw(20) << "start time"
         << setw(20) << "end time" << endl;
    for (it = meetings.begin(); it != meetings.end(); it++) {
        cout << setw(12) << (*it).getTitle()
             << setw(12) << (*it).getSponsor()
             << setw(15) << (*it).getParticipator();
             Date d1 = (*it).getStartDate(), d2 = (*it).getEndDate();
        cout << setw(20) << Date::dateToString(d1)
             << setw(20) << Date::dateToString(d2) << endl;
    }
}
