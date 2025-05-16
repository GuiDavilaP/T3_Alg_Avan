# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I inc/

# Folders
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin

# Source files (excluding generate_tournament.cpp)
SRCS = $(filter-out $(SRC_DIR)/generate_tournament.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main targets
TARGET = $(BIN_DIR)/torneio
GEN_TARGET = $(BIN_DIR)/generate_tournament

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Main target build
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Tournament generator build
$(GEN_TARGET): $(SRC_DIR)/generate_tournament.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(GEN_TARGET)

# Build all
all: $(TARGET) $(GEN_TARGET)

# Dependencies
-include $(OBJS:.o=.d)

# Run rule
run: $(TARGET)
	$(TARGET)

.PHONY: clean run all