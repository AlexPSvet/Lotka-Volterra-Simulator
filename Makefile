TARGET_EXEC := Simulator
PATH_ROOT := /home/alex/Documents/Projets/Lotka-Volterra Simulator
SRC_DIR := src
BUILD_DIR := target

CXX := g++
CXXFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -fsanitize=address
HEADERS_INCLUDE := -I$(SRC_DIR)/HeaderFiles

SRCS := $(shell find $(SRC_DIR)/ -type f -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_FLAG) $(NCURSES_FLAG)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(HEADERS_INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)