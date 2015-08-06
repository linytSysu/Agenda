All: User.o Meeting.o Date.o Storage.o AgendaService.o AgendaUI.o Agenda.o AgendaLog.o
	g++ -std=c++0x -o All User.o Meeting.o Date.o Storage.o AgendaService.o AgendaUI.o Agenda.o AgendaLog.o
User.o: User.h User.cpp
	g++ -std=c++0x -c User.cpp
Meeting.o: Meeting.h Meeting.cpp
	g++ -std=c++0x -c Meeting.cpp
Date.o: Date.h Date.cpp
	g++ -std=c++0x -c Date.cpp
Storage.o: Storage.h Storage.cpp
	g++ -std=c++0x -c Storage.cpp
AgendaService.o:
	g++ -std=c++0x -c AgendaService.cpp
AgendaUI.o: AgendaUI.h AgendaUI.cpp
	g++ -std=c++0x -c AgendaUI.cpp
AgendaLog.o: AgendaLog.h AgendaLog.cpp
	g++ -std=c++0x -c AgendaLog.cpp
Agenda.o: Agenda.cpp
	g++ -std=c++0x -c Agenda.cpp
clean:
	rm User.o Meeting.o Date.o Storage.o AgendaService.o All AgendaUI.o Agenda.o AgendaLog.o

