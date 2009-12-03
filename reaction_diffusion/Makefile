# Makefile

CPP = g++
CPPFLAGS = -g -Wall
LDFLAGS = -lGL -lGLU -lglut
INCLUDES = -I./ 

# Compile the program.
program : rdp3.cpp
	$(CPP) $(CPPFLAGS) -o reaction ReactionDiff.cpp rdp3.cpp $(LDFLAGS) $(INCLUDES)
