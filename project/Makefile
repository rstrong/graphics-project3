# Makefile

CPP = g++
CPPFLAGS = -g -Wall
LDFLAGS = -lGL -lGLU -lglut
INCLUDES = -I./ -Iilmbase/Imath -Iilmbase/Iex

# Compile the program.
program : main.cpp
	$(CPP) $(CPPFLAGS) -o project3 bitmap.c main.cpp $(LDFLAGS) $(INCLUDES)
