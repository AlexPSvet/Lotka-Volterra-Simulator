TARGET_EXEC := LotkaVolterra
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := target

INCLUDE := -I$(SRC_DIR)/HeaderFiles
SRCS := $(shell find $(SRC_DIR)/ -type f -name "*.cpp")
OBJS_O := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS_HPP := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.hpp)

SFML_FLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
CXXFLAGS := -std=c++20 -fsanitize=address $(INCLUDE)

all: start

start: $(BUILD_DIR)/$(TARGET_EXEC) $(BUILD_DIR)/EnsembleTest $(BUILD_DIR)/CoordTest $(BUILD_DIR)/PopulationTest
	echo "Compiled succesfully main file and test files! Yey :D"

# Project compiler rules

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_O)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJS_O) $(SFML_FLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Graphics.o: $(SRC_DIR)/Graphics.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(SFML_FLAGS)

# Test compiler rules

$(BUILD_DIR)/EnsembleTest: $(TEST_DIR)/EnsembleTest.cpp $(SRC_DIR)/Ensemble.cpp
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/doctest.h $(TEST_DIR)/EnsembleTest.cpp $(SRC_DIR)/Ensemble.cpp -o $@

$(BUILD_DIR)/CoordTest: $(TEST_DIR)/CoordTest.cpp $(SRC_DIR)/Coord.cpp
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/doctest.h $(TEST_DIR)/CoordTest.cpp $(SRC_DIR)/Coord.cpp $(SRC_DIR)/Ensemble.cpp -o $@

$(BUILD_DIR)/PopulationTest: $(TEST_DIR)/PopulationTest.cpp $(SRC_DIR)/Coord.cpp $(SRC_DIR)/Entity.cpp $(SRC_DIR)/Ensemble.cpp $(SRC_DIR)/Population.cpp
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/doctest.h $(TEST_DIR)/PopulationTest.cpp $(SRC_DIR)/Coord.cpp $(SRC_DIR)/Entity.cpp $(SRC_DIR)/Ensemble.cpp $(SRC_DIR)/Population.cpp -o $@

# $(BUILD_DIR)/EntityTest: $(TEST_DIR)/EntityTest.cpp $(SRC_DIR)/Entity.cpp $(SRC_DIR)/Coord.cpp
# 	$(CXX) $(CXXFLAGS) $(TEST_DIR)/doctest.h $(TEST_DIR)/EntityTest.cpp $(SRC_DIR)/Entity.cpp $(SRC_DIR)/Coord.cpp $(INCLUDE) -o $@

# Other rules

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean