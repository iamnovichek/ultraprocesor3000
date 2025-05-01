#
# Makefile for the Ultra Core processor simulator
#
# This makefile compiles the Ultra Core processor simulator and provides
# targets for building, running, testing, and cleaning the project.
#
# Author: Dmytro Lunhu
# Date: April 21, 2025
#

CXX = g++

# Keep std=c++23 but add flags to work around system header issues
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++23 -D'_Alignof(x)=__alignof__(x)'

SOURCES = main.cpp software.cpp values.cpp memory.cpp hardware.cpp insctructions.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

compile: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: compile
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) && clear
