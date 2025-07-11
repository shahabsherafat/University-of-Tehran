CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -I./include #-fsanitize=address -fsanitize=undefined
SRCDIR = src
INCLUDEDIR = includes
OBJDIR = objects
BINDIR = .
EXECUTABLE = $(BINDIR)/MK.out

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(INCLUDEDIR)/*.hpp)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)