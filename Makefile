CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Ilib/openssl/include
LDFLAGS = -Llib/openssl
LDLIBS = -lssl -lcrypto

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
TARGET = prog
TEST_TARGET = test_prog

# Source and object files for the main target
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Source and object files for the test target
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean test

# Target to build everything and then run tests
all-and-test: all test

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile test source files into object files
# Note: Removed $(LDFLAGS) and $(LDLIBS) from the compilation step
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET) $(TEST_TARGET)



