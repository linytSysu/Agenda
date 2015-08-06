/* Copyright [2014] <linyiting> */

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <fstream>

#include "Storage.h"

using std::endl;
using std::string;
using std::list;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::function;

Storage* Storage::instance_ = 0;

Storage::Storage() {}

Storage* Storage::getInstance(void) {
    if (instance_ != 0) {
        delete Storage::instance_;
    }
    Storage::instance_ = new Storage;
    instance_->readFromFile("agenda.data");
    return Storage::instance_;
}

Storage::~Storage() {
    sync();
    Storage::instance_ = 0;
}

bool Storage::readFromFile(const char *fpath) {
    ifstream ifs;
    ifs.open(fpath);
    if (ifs.peek() == EOF) {
        ifs.close();
        return true;
    }
    if (ifs.fail())
        return false;
    string head1, head2;
    ifs >> head1;
    if (head1.find("User") != string::npos) {
        int count = 0;
        for (int i = 25; head1[i] >= '0' && head1[i] <= '9'; i++)
            count = count*10+(head1[i]-'0');
        string s, na, pw, em, ph;
        getline(ifs, s);
        while (count) {
             getline(ifs, s);
             stringstream ss(s);
             int tmp = 0;
             string item;
             while (getline(ss, item, '"')) {
                 tmp++;
                 if (tmp == 2)
                     na = item;
                 if (tmp == 4)
                     pw = item;
                 if (tmp == 6)
                     em = item;
                 if (tmp == 8)
                     ph = item;
             }
             count--;
             User u(na, pw, em, ph);
             userList_.push_back(u);
        }
    }
    ifs >> head2;
    if (head2.find("Meeting") != string::npos) {
        int count = 0;
        for (int i = 28; head2[i] >= '0' && head2[i] <= '9'; i++)
            count = count*10+(head2[i]-'0');
        string s, sp, pa, sd, ed, ti;
        getline(ifs, s);
        while (count) {
             getline(ifs, s);
             stringstream ss(s);
             int tmp = 0;
             string item;
             while (getline(ss, item, '"')) {
                 tmp++;
                 if (tmp == 2)
                     sp = item;
                 if (tmp == 4)
                     pa = item;
                 if (tmp == 6)
                     sd = item;
                 if (tmp == 8)
                     ed = item;
                 if (tmp == 10)
                     ti = item;
             }
             count--;
             Date d1 = Date::stringToDate(sd);
             Date d2 = Date::stringToDate(ed);
             Meeting m(sp, pa, d1, d2, ti);
             meetingList_.push_back(m);
        }
    }
    ifs.close();
    return true;
}

bool Storage::writeToFile(const char *fpath) {
    ofstream ofs;
    ofs.open(fpath);
    if (ofs.fail())
        return false;
    if (1) {
        ofs << "{collection:" << '"' << "User" << '"' << ',';
        ofs <<"total:" << userList_.size() << '}' << endl;
        list<User>::iterator itu;
        string na, pw, em, ph;
        for (itu = userList_.begin(); itu != userList_.end(); itu++) {
            na = (*itu).getName();
            pw = (*itu).getPassword();
            em = (*itu).getEmail();
            ph = (*itu).getPhone();
            ofs << "{name:" << '"' << na << '"' << ",password:"
                << '"' << pw << '"' << ",email:" << '"'
                << em << '"' << ",phone:" << '"' << ph
                << '"' << "}" << endl;
        }
    }
    if (1) {
        ofs << "{collection:" << '"' << "Meeting" << '"' << ",total:"
            << meetingList_.size() << "}" << endl;
        list<Meeting>::iterator itm;
        string sp, pa, sd, ed, ti;
        Date _sd, _ed;
        for (itm = meetingList_.begin(); itm != meetingList_.end(); itm++) {
            sp = (*itm).getSponsor();
            pa = (*itm).getParticipator();
            _sd = (*itm).getStartDate();
            sd = Date::dateToString(_sd);
            _ed = (*itm).getEndDate();
            ed = Date::dateToString(_ed);
            ti = (*itm).getTitle();
            ofs << "{sponsor:" << '"' << sp << '"' << ",participator:"
                << '"' << pa << '"' << ",sdate:" << '"'
                << sd << '"' << ",edate:" << '"' << ed
                << '"' << ",title:" << '"' << ti << '"' << "}" << endl;
        }
    }
    ofs.close();
    return true;
}

void Storage::createUser(const User& us) {
    userList_.push_back(us);
}

list<User> Storage::queryUser(function<bool(const User&)> filter) {
    list<User> listus;
    list<User>::iterator it;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        if (filter(*it))
            listus.push_back(*it);
    }
    return listus;
}

int Storage::updateUser(function<bool(const User&)> filter,
               function<void(User&)> switcher) {
    list<User>::iterator it;
    int count = 0;
    for (it = userList_.begin(); it != userList_.end(); it++) {
        if (filter(*it)) {
            switcher(*it);
            count++;
        }
    }
    return count++;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
    list<User>::iterator it;
    int count = 0;
    for (it = userList_.begin(); it != userList_.end();) {
        if (filter(*it)) {
            count++;
            it = userList_.erase(it);
        } else {
            it++;
        }
    }
    return count++;
}

void Storage::createMeeting(const Meeting& me) {
    meetingList_.push_back(me);
}

list<Meeting> Storage::queryMeeting(
                     function<bool(const Meeting&)> filter) {
    list<Meeting> listme;
    list<Meeting>::iterator it;
    for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
        if (filter(*it))
            listme.push_back(*it);
    }
    return listme;
}

int Storage::updateMeeting(function<bool(const Meeting&)> filter,
                           function<void(Meeting&)> switcher) {
    list<Meeting>::iterator it;
    int count = 0;
    for (it = meetingList_.begin(); it != meetingList_.end();) {
        if (filter(*it)) {
            switcher(*it);
            count++;
        } else {
            it++;
        }
    }
    return count++;
}

int Storage::deleteMeeting(function<bool(const Meeting&)> filter) {
    list<Meeting>::iterator it;
    int count = 0;
    for (it = meetingList_.begin(); it != meetingList_.end();) {
        if (filter(*it)) {
            count++;
            it = meetingList_.erase(it);
        } else {
            it++;
        }
    }
    return count++;
}

bool Storage::sync(void) {
    return writeToFile("agenda.data");
}

