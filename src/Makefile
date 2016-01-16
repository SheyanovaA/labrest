CXX=g++
CXX_FLAGS=
LD=g++
LDFLAGS=
RMRF=rm -rf
MD=mkdir

ICE_HOME=/usr
SLICE2CPP=${ICE_HOME}/bin/slice2cpp
ICE_INC=${ICE_HOME}/include
ICE_LIB=${ICE_HOME}/lib

TG_DIR=../target
SRC_DIR=../src
OBJECTS_DIR=$(TG_DIR)/objects
FINAL_DIR=$(TG_DIR)/final

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
     LabrestServer.o \
     ResourceFinder.o

all: dirs labrest_server labrest_client final

final:
	mv -f $(OBJS) $(OBJECTS_DIR)
	cp -rf ../res/* $(FINAL_DIR)

dirs: 
	$(MD) -p $(TG_DIR) $(OBJECTS_DIR) $(FINAL_DIR)
	
LabrestAPI.h LabrestAPI.cpp: LabrestAPI.ice
	$(SLICE2CPP) -I/usr/share/Ice-3.4.2/slice $^
	slice2py  -I/usr/share/Ice-3.4.2/slice $^ --output-dir $(FINAL_DIR)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c -o $@ -I. -I$(ICE_INC) $<


LabrestClient.cpp: LabrestAPI.h UserCommand.h CallbackI.h CallbackThreadCl.h
LabrestServer.cpp: LabrestAPI.h CallbackManagerI.h CallbackThreadSrv.h MonitorThread.h EventsQueue.h LabrestDB.h EntryI.h SessionI.h ResourceManagerI.h UserManagerI.h ReapTask.h ResourceFinder.h

labrest_server: LabrestServer.o LabrestAPI.o LabrestDB.o CallbackManagerI.o CallbackThreadSrv.o MonitorThread.o EventsQueue.o EntryI.o SessionI.o ReapTask.o ResourceManagerI.o UserManagerI.o ResourceFinder.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB)  -lIce -lIceUtil -lsqlite3 -o $(FINAL_DIR)/$@ 

labrest_client: LabrestClient.o LabrestAPI.o UserCommand.o CallbackI.o CallbackThreadCl.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB)  -lIce -lIceUtil -lsqlite3 -o $(FINAL_DIR)/$@

clean:
	$(RMRF) $(OBJS) $(TG_DIR) $(OBJECTS_DIR) $(FINAL_DIR) *~ labrest_server labrest_client LabrestAPII.h LabrestAPII.cpp LabrestAPI.h LabrestAPI.cpp sessions LabrestAPI LabrestAPI_ice.py LabrestAPI_ice.pyc */*~
