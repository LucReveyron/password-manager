CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Ilib/openssl/include
LDFLAGS = -Llib/openssl
LDLIBS = -lssl -lcrypto

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
TARGET = prog
TEST_TARGET = test_prog

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean test

all: $(TARGET) test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	@echo "TEST_TARGET: $(TEST_TARGET)"
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)
