CXX=g++
CXX_FLAGS=
LD=g++
LDFLAGS=
RMRF=rm -rf

ICE_HOME=/usr
SLICE2CPP=${ICE_HOME}/bin/slice2cpp
ICE_INC=${ICE_HOME}/include
ICE_LIB=${ICE_HOME}/lib

OBJS=labrestapi.o \
     session_impl.o \
     entry_impl.o \
     labrest_client.o \
     labrest_server.o

all: labrest_server labrest_client

labrestapi.h labrestapi.cpp: labrestapi.ice
	$(SLICE2CPP) $^

%.o: %.cpp
	$(CXX) -c -I. -I$(ICE_INC) $<

labrest_client.cpp: labrestapi.h
labrest_server.cpp: labrestapi.h entry_impl.h session_impl.h

labrest_server: labrest_server.o labrestapi.o entry_impl.o session_impl.o
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -o $@

labrest_client: labrest_client.o labrestapi.o
	$(LD) $^ -Wl,-rpath=$(ICE_LIB) -L$(ICE_LIB) -lIce -lIceUtil -o $@

clean:
	$(RMRF) $(OBJS) labrest_server labrest_client labrestapi.h labrestapi.cpp
