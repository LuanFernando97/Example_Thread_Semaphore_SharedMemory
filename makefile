CC=g++
CFLAGS = -c -Wall -DRAPIDJON_HAS_STDSTRING=1
LINKER_FLAGS = -lpthread -lrt
INCLUDES = -I..

CONTAINERS = Containers
	READMEM = ${CONTAINERS}/ReadMem
	WRITEMEM = ${CONTAINERS}/WriteMem

UTILS = Utils
	POSIXSHMEM = $(UTILS)/PosixShMem
	THREADBASE = $(UTILS)/ThreadBase
all: main

main: ReadMem.o WriteMem.o PosixShMem.o ThreadBase.o main.o
	$(CC) ReadMem.o WriteMem.o PosixShMem.o ThreadBase.o main.o -o TesteThread $(LINKER_FLAGS)
	rm -rf *.o

ThreadBase.o: $(THREADBASE)/ThreadBase.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(THREADBASE)/ThreadBase.cpp

PosixShMem.o: $(POSIXSHMEM)/PosixShMem.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(POSIXSHMEM)/PosixShMem.cpp

ReadMem.o: $(READMEM)/ReadMem.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(READMEM)/ReadMem.cpp

WriteMem.o: $(WRITEMEM)/WriteMem.cpp
	$(CC) $(INCLUDES) $(CFLAGS) $(WRITEMEM)/WriteMem.cpp
