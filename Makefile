SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = C:\libraries\SFML-2.5.1\include
LIB_DIR = C:\libraries\SFML-2.5.1\lib

SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/vector_functions.cpp
OBJ_FILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/vector_functions.o
EXECUTABLE = $(BUILD_DIR)/main

CXX = g++
CXXFLAGS = -I"$(INCLUDE_DIR)"
LDFLAGS = -L"$(LIB_DIR)" -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXECUTABLE)

$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BUILD_DIR)/vector_functions.o: $(SRC_DIR)/vector_functions.cpp | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/main

.PHONY: all clean
