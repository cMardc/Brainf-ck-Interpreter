CXX = g++
SRC_DIR = src
BUILD_DIR = build
EXAMPLES_DIR = examples
TARGET = $(BUILD_DIR)/brainf
EXAMPLES_TARGET = $(EXAMPLES_DIR)/brainf

all: $(TARGET) $(EXAMPLES_TARGET)

$(TARGET): $(SRC_DIR)/main.c
	$(CXX) $< -o $@

$(EXAMPLES_TARGET): $(SRC_DIR)/main.c
	$(CXX) $< -o $@

clean:
	rm -f $(BUILD_DIR)/brainf
	rm -f $(EXAMPLES_DIR)/brainf

.PHONY: all clean
