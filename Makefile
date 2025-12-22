# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2

# Target name (the executable)
TARGET   := orbital_planner

# Source files
SRCS := main.cpp Body.cpp Orbit.cpp 

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean