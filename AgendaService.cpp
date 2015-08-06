/* CopyRight [2014] <linyt> */

#include "AgendaService.h"
#include <iostream>
#include <string>
#include <list>

using std::string;
using std::list;
using std::function;

AgendaService::AgendaService() {
    storage_ = 0;
}

AgendaService::~AgendaService() {
    storage_ = 0;
}

void AgendaService::startAgenda(void) {
    if (storage_ == 0)
        storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    if (storage_ != 0) {
        storage_->sync();
        delete storage_;
    }
    storage_ = 0;
}

bool AgendaService::userLogIn(string userName, string password) {
    function<bool(const User&)> filter = [userName](const User& user) {
        if (user.getName() == userName)
            return true;
        else
            return false;
    };
    list<User> lu;
    list<User>::iterator it;
    lu = storage_->queryUser(filter);
    for (it = lu.begin(); it != lu.end(); it++) {
        if ((*it).getPassword() == password) {
            return true;
        }
    }
    return false;
}

bool AgendaService::userRegister(string userName, string password,
                                 string email, string phone) {
    function<bool(const User&)> filter = [userName](const User& user) {
        if (user.getName() == userName)
            return true;
        else
            return false;
    };
    list<User> lu;
    list<User>::iterator it;
    lu = storage_->queryUser(filter);
    if (lu.size() == 0) {
        User u(userName, password, email, phone);
        storage_->createUser(u);
        return true;
    }
    return false;
}

bool AgendaService::deleteUser(string userName, string password) {
    function<bool(const User&)> filter = [userName, password](const User& user) {
        if (user.getName() == userName && user.getPassword() == password)
            return true;
        else
            return false;
    };
    if (storage_->deleteUser(filter) == 0)
        return false;
    function<bool(const Meeting&)> filterM = [userName](const Meeting& meeting) {
        if (meeting.getSponsor() == userName ||
            meeting.getParticipator() == userName)
            return true;
        else
            return false;
    };
    storage_->deleteMeeting(filterM);
    return true;
}

list<User> AgendaService::listAllUsers(void) {
    function<bool(const User&)> filter = [](const User& user) {
        return true;
    };
    list<User> lu;
    list<User>::iterator it;
    lu = storage_->queryUser(filter);
    return lu;
}

bool AgendaService::createMeeting(string userName, string title,
                                  string participator,
                                  string startDate, string endDate) {
    list<Meeting> lm;
    list<Meeting>::iterator itm;
    list<User> lu;
    
    
    Date Sd = Date::stringToDate(startDate);
    Date Ed = Date::stringToDate(endDate);
    if (!Date::isValid(Sd) || !Date::isValid(Ed))
        return false;
    if (Sd >= Ed)
        return false;

    function<bool(const Meeting&)> filter1 = [title](const Meeting& meeting) {
        if (meeting.getTitle() == title)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter1);
    for (itm = lm.begin(); itm != lm.end(); itm++) {
        if (itm->getSponsor() == userName || itm->getSponsor() == participator ||
            itm->getParticipator() == userName || itm->getParticipator() == participator)
            return false;
    }

    function<bool(const User&)> filter2 = [participator](const User& user) {
        if (user.getName() == participator)
            return true;
        else
            return false;
    };
    lu = storage_->queryUser(filter2);
    if (lu.size() == 0)
        return false;

    function<bool(const User&)> filter3 = [userName](const User& user) {
        if (user.getName() == userName)
            return true;
        else
            return false;
    };
    lu = storage_->queryUser(filter3);
    if (lu.size() == 0)
        return false;

    function<bool(const Meeting&)> filter4 = [userName, participator](const Meeting& meeting) {
        if (meeting.getSponsor() == userName ||
            meeting.getParticipator() == participator ||
            meeting.getSponsor() == participator ||
            meeting.getParticipator() == userName)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter4);
    for (itm = lm.begin(); itm != lm.end(); itm++) {
        Date sd = itm->getStartDate();
        Date ed = itm->getEndDate();
        Date Sd = Date::stringToDate(startDate);
        Date Ed = Date::stringToDate(endDate);
        if ((Sd > sd && Sd < ed) || (Ed > sd && Ed < ed) ||
            (sd > Sd && sd < Ed) || (ed > Sd && ed < Sd))
            return false;
    }

    Meeting m(userName, participator, Sd, Ed, title);
    storage_->createMeeting(m);
    return true;
}

list<Meeting> AgendaService::meetingQuery(string userName, string title) {
    list<Meeting> lm;
    list<Meeting>::iterator itm;
    
    function<bool(const Meeting&)> filter = [userName, title](const Meeting& meeting) {
        if ((meeting.getSponsor() == userName ||
             meeting.getParticipator() ==  userName) &&
            meeting.getTitle() == title)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter);
    return lm;
}

list<Meeting> AgendaService::meetingQuery(string userName, string startDate,
                                          string endDate) {
    list<Meeting> lm;
    list<Meeting>::iterator itm;

    function<bool(const Meeting&)> filter = [startDate, endDate, userName](const Meeting& meeting) {
        Date sd = meeting.getStartDate();
        Date ed = meeting.getEndDate();
        Date Sd = Date::stringToDate(startDate);
        Date Ed = Date::stringToDate(endDate);
        if ((meeting.getSponsor() == userName ||
             meeting.getParticipator() ==  userName) &&
            ((Sd >= sd && Sd <= ed) || (Ed >= sd && Ed <= ed) ||
            (sd >= Sd && sd <= Ed) || (ed >= Sd && ed <= Sd)))
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter);
    return lm;
}

list<Meeting> AgendaService::listAllMeetings(string userName) {
    list<Meeting> lm;
    function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
        if (meeting.getSponsor() == userName ||
             meeting.getParticipator() ==  userName)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter);
    return lm;
}

list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
    list<Meeting> lm;
    function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
        if (meeting.getSponsor() == userName)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter);
    return lm;
}

list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
    list<Meeting> lm;
    function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
        if (meeting.getParticipator() ==  userName)
            return true;
        else
            return false;
    };
    lm = storage_->queryMeeting(filter);
    return lm;
}

bool AgendaService::deleteMeeting(string userName, string title) {
    function<bool(const Meeting&)> filter = [userName, title](const Meeting& meeting) {
        if (meeting.getSponsor() == userName &&
            meeting.getTitle() == title)
            return true;
        else
            return false;
    };
    if (storage_->deleteMeeting(filter) == 0)
        return false;
    else
        return true;
}

bool AgendaService::deleteAllMeetings(string userName) {
    function<bool(const Meeting&)> filter = [userName](const Meeting& meeting) {
        if (meeting.getSponsor() == userName)
            return true;
        else
            return false;
    };
    if (storage_->deleteMeeting(filter) == 0)
        return false;
    else
        return true;
}

