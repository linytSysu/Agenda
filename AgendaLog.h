#ifndef AGENDALOG_H
#define AGENDALOG_H

#include <list>
#include <string>
#include <ctime>

using std::string;
using std::list;

class AgendaLog {
    private:
        static AgendaLog *instance_;
        AgendaLog();
        list<string> listLog;
        bool writeToFile(const char* fpath);
    public:
        static AgendaLog *getInstance();
        ~AgendaLog();
        void startAgenda();
        void userLogInSucceed(string na);
        void userLogInFail(string na);
        void userRegisterSucceed(string na, string pw, string em, string ph);
        void userRegisterFail(string na, string pw, string em, string ph);
        void quitAgenda();
        void userLogOut(string userName_);
        void deleteUserSucceed(string uerName_);
        void deleteUserFail(string uerName_);
        void listAllUsers(string uerName_);
        void createMeetingSucceed(string userName_, string title, string pa, string sd, string ed);
        void createMeetingFail(string userName_);
        void listAllMeetings(string uerName_);
        void listAllSponsorMeetings(string uerName_);
        void listAllParticipateMeetings(string uerName_);
        void queryMeetingByTitle(string userName_, string title);
        void queryMeetingByTimeInterval(string userName_, string startDate, string endDAte);
        void deleteMeetingByTitleSucceed(string userName_, string title);
        void deleteMeetingByTitleFail(string userName_, string title);
        void deleteAllMeetingsSucceed(string userName_);
        void deleteAllMeetingsFail(string userName_);
        void addString(string as);
        string getNowTime();
        bool sync();
};

#endif

