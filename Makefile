ARMA = /home/jbrzensk/armadillo/armadillo-12.6.4
INC = /usr/local/include
LIBPATH = /usr/lib
LIBS = -L$(ARMA) -larmadillo -L$(LIBPATH) -lsuperlu -llapack -lopenblas

# Compiler and flags
CXX = mpic++

CXXFLAGS = -O3 -std=c++11 -Wall -Wextra  

# This is based on the machine basics we et up above.
INCPATH = -I. -I$(ARMA)/include -I$(INC)

# Source files and object files
SOURCES = circular_shift.cpp \
		  shift_example.cpp

OBJECTS = $(SOURCES:.cpp=.o)


# Rules
all: shift_example

shift_example: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $<

clean:
	rm -f *.o shift_example

# # Rules:
# all: shift_example

# shift_example: shift_example.cpp
# 	$(CXX) $(CXXFLAGS) -I$(ARMA)/include -o shiftexample shift_example.cpp $(LIBS)

# clean:
# 	rm -f 
