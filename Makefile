# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Output directory for binaries
BIN_DIR = bin

# Source files
SRC_DIR = src

# Include directory
INC_DIR = include

# Libs directory
LIBS_DIR = libs

# Logger directory
LOGGER_DIR = $(LIBS_DIR)/Logger

# Logger source files
LOGGER_SRC_FILE = $(LOGGER_DIR)/logger.cpp

# Logger include files
LOGGER_INC_FILE = $(LOGGER_DIR)/logger.h

# Executable
EXEC = $(BIN_DIR)/SecureMac

# Libraries
LIBS = -framework CoreFoundation -framework CoreGraphics -framework Carbon

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Include files
INC_FILES = $(wildcard $(INC_DIR)/*.h)

# Command line arguments
ARGS =

# Default target
all: clean build

# Build target
build: $(EXEC)

# Compile
$(EXEC): $(SRC_FILES) $(INC_FILES) $(LOGGER_SRC_FILE) $(LOGGER_INC_FILE)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(LOGGER_INC_FILE) -o $@ $(SRC_FILES) $(LIBS) $(LOGGER_SRC_FILE)
	@echo "\033[0;32mCompiled successfully!"

# Run the program
run:
	@./$(EXEC) $(ARGS)

# Run the program with debug arguments
run_debug: ARGS = debug
run_debug: run

# Clean up
clean:
	@rm -rf $(BIN_DIR)
	@rm -rf video/
	@echo "\033[0;32mCleaned up!"

# Phony targets
.PHONY: all build run run_debug clean
