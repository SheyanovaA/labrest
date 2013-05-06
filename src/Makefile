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
     ResourceTypeI.o \
     ResourceI.o \
     ResourceManagerI.o \
     UserI.o\
     UserManagerI.o \
     SessionI.o \
     EntryI.o \
     LabrestClient.o \
     LabrestDB.o \
     LabrestServer.o

all: labrest_server labrest_client

LabrestAPI.h LabrestAPI.cpp: LabrestAPI.ice
	$(SLICE2CPP) $^

%.o: %.cpp
	$(CXX) -c -I. -I$(ICE_INC) $<

LabrestClient.cpp: LabrestAPI.h
LabrestServer.cpp: LabrestAPI.h LabrestDB.h EntryI.h SessionI.h ResourceTypeI.h ResourceI.h ResourceManagerI.h UserManagerI.h UserI.h 

labrest_server: LabrestServer.o LabrestAPI.o UserI.o LabrestDB.o EntryI.o SessionI.o ResourceTypeI.o ResourceI.o ResourceManagerI.o UserManagerI.o 
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lsqlite3 -o $@

labrest_client: LabrestClient.o LabrestAPI.o
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -lsqlite3 -o $@

clean:
	$(RMRF) $(OBJS) *~ labrest_server labrest_client LabrestAPI.h LabrestAPI.cpp
