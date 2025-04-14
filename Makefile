TARGET_EXEC := Simulator
SRC_DIR := src
BUILD_DIR := target

CXX := g++
CXXFLAGS := -std=c++11 -fsanitize=address -I$(SRC_DIR)/HeaderFiles

SRCS := $(shell find $(SRC_DIR)/ -type f -name "*.cpp")
OBJS_O := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS_HPP := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.hpp)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_O)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OBJS_O) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/HeaderFiles/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Graphics.o: $(SRC_DIR)/Graphics.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean