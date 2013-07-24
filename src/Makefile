CXX=g++
CXX_FLAGS=
LD=g++
LDFLAGS=
RMRF=rm -rf

ICE_HOME=/usr
SLICE2CPP=${ICE_HOME}/bin/slice2cpp
ICE_INC=${ICE_HOME}/include
ICE_LIB=${ICE_HOME}/lib

OBJS=LabrestAPI.o \
     ResourceManagerI.o \
     UserManagerI.o \
     SessionI.o \
     EntryI.o \
     ReapTask.o \
     CallbackI.o \
     CallbackManagerI.o \
     CallbackThreadSrv.o \
     CallbackThreadCl.o \
     EventsQueue.o \
     MonitorThread.o \
     UserCommand.o \
     LabrestClient.o \
     LabrestDB.o \
     LabrestServer.o

all: labrest_server labrest_client

LabrestAPI.h LabrestAPI.cpp: LabrestAPI.ice
	$(SLICE2CPP) -I/usr/share/Ice-3.4.2/slice $^
	slice2py -I/usr/share/Ice-3.4.2/slice $^

%.o: %.cpp
	$(CXX) -c -I. -I$(ICE_INC) $<


LabrestClient.cpp: LabrestAPI.h UserCommand.h CallbackI.h CallbackThreadCl.h
LabrestServer.cpp: LabrestAPI.h CallbackManagerI.h CallbackThreadSrv.h MonitorThread.h EventsQueue.h LabrestDB.h EntryI.h SessionI.h ResourceManagerI.h UserManagerI.h ReapTask.h

labrest_server: LabrestServer.o LabrestAPI.o LabrestDB.o CallbackManagerI.o CallbackThreadSrv.o MonitorThread.o EventsQueue.o EntryI.o SessionI.o ReapTask.o ResourceManagerI.o UserManagerI.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lsqlite3 -o $@

labrest_client: LabrestClient.o LabrestAPI.o UserCommand.o CallbackI.o CallbackThreadCl.o
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lsqlite3 -o $@

clean:
	$(RMRF) $(OBJS) *~ labrest_server labrest_client LabrestAPII.h LabrestAPII.cpp LabrestAPI.h LabrestAPI.cpp sessions LabrestAPI LabrestAPI_ice.py LabrestAPI_ice.pyc */*~
