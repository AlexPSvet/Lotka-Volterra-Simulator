TARGET_EXEC := Simulator
SRC_DIR := src
BUILD_DIR := target

CXX := clang++
CXXFLAGS := -std=c++11 -fsanitize=address
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -fsanitize=address -framework OpenGL -framework Foundation -framework AppKit
HEADERS_INCLUDE := -I$(SRC_DIR)/HeaderFiles
LIB_PATH := -L/usr/local/lib
INCLUDE_PATH := -I/usr/local/include

SRCS := $(shell find $(SRC_DIR)/ -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) $(LIB_PATH) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(HEADERS_INCLUDE) $(INCLUDE_PATH) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean