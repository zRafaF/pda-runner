
# Detect the operating system
OS := $(shell uname -s)

# Compiler settings
CXX := g++
CXXFLAGS := -Wall -std=c++11
LDFLAGS :=

# Project name
PROJECT := pda-runner

# Source and binary settings
SRCDIR := src
BINDIR := bin
TARGET := $(BINDIR)/$(PROJECT)

# Source files
SOURCES := $(SRCDIR)/main.cpp
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

# Platform specific adjustments
ifeq ($(OS),Windows_NT)
    TARGET := $(BINDIR)/$(PROJECT).exe
    RM := del /Q
    FixPath = $(subst /,\,$1)
else
    RM := rm -f
    FixPath = $1
endif

# Default rule
all: $(TARGET)

# Link the target
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile the source files into objects
$(OBJECTS): $(BINDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	$(RM) $(call FixPath,$(OBJECTS) $(TARGET))

# Phony targets
.PHONY: all clean

# Rule for running the program
run: $(TARGET)
	./$(call FixPath,$(TARGET))



