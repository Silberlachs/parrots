CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files
SRC_FILES = src/Parrot.cpp src/Toybox.cpp main.cpp

# Object files
OBJ_FILES = obj/Parrot.o obj/Toybox.o obj/main.o

# Target executable
TARGET = bin/parrotparty

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/Parrot.o: src/Parrot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Toybox.o: src/Toybox.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean