# Compiler settings
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
EXE_DIR = bin

# List of days
DAYS = 1 2 3
# DAYS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

# Pattern rule for compiling .cpp files to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Pattern rule for creating executables for each day
$(EXE_DIR)/day%: $(BUILD_DIR)/day%.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Default target: build all executables
all: $(DAYS:%=$(EXE_DIR)/day%)

# Clean up the build and bin directories
clean:
	rm -rf $(BUILD_DIR) $(EXE_DIR)

# Create the directories if they don't exist
$(BUILD_DIR) $(EXE_DIR):
	mkdir -p $@

# Target to build just the day N
day%: $(EXE_DIR)/day%

# You can also define a target to run all programs (if you need it)
run_all: $(DAYS:%=$(EXE_DIR)/day%)
	@for exe in $(EXE_DIR)/day*; do \
		$$exe; \
	done

