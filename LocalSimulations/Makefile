#MAKEFILE for Nonequilbirium Propogator routine
#
#Steven Large
#JApril 5th 2018

PRODUCT = StochControl.exe

ODIR = obj
LDIR = lib
IDIR = include
SDIR = src

MAINFILE = $(SDIR)/StochasticEnsemble.cpp

SOURCES = $(SDIR)/StochasticPropogator.cpp
LIBRARIES = $(LDIR)/ReadWrite.cpp 
LIBRARIES_2 = $(LDIR)/FrictionCalculator.cpp
OBJECTS = $(SDIR)/$(ODIR)/StochasticPropogator.o
OBJECTS_LIB = $(SDIR)/$(ODIR)/ReadWrite.o
OBJECTS_LIB_2 = $(SDIR)/$(ODIR)/FrictionCalculator.o

CFLAGS = -I.

DEPS = $(IDIR)/StochasticPropogator.h $(IDIR)/ReadWrite.h  $(IDIR)/FrictionCalculator.h

CC = g++ -std=c++11 -O3

all: $(PRODUCT)

$(OBJECTS): $(SOURCES)
	$(CC) -c $(SOURCES) -o $(OBJECTS) $(CFLAGS)

$(OBJECTS_LIB): $(LIBRARIES)
	$(CC) -c $(LIBRARIES) -o $(OBJECTS_LIB) $(CFLAGS) 

$(OBJECTS_LIB_2): $(LIBRARIES_2)
	$(CC) -c $(LIBRARIES_2) -o $(OBJECTS_LIB_2) $(CFLAGS)

$(PRODUCT): $(MAINFILE) $(OBJECTS) $(OBJECTS_LIB) $(OBJECTS_LIB_2) $(DEPS)
	$(CC) $(MAINFILE) $(OBJECTS) $(OBJECTS_LIB) $(OBJECTS_LIB_2) -o $(PRODUCT) $(CFLAGS)

clean:
	rm -f $(SDIR)/$(ODIR)/*.o

clean_ex:
	rm -f *.exe

