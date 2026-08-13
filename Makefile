PROJECT_NAME := sonar

CXX ?= g++

BUILD_DIR := build
TARGET    := $(PROJECT_NAME)

VERSION_FILE := VERSION
VERSION_IN   := include/version.hpp.in
VERSION_OUT  := $(BUILD_DIR)/generated/version.hpp

CPPFLAGS += -Iinclude -I$(BUILD_DIR)/generated
CXXFLAGS += -std=c++17 -Wall -Wextra -Werror -O2 -MMD -MP

SRCS := $(shell find src libs -type f -name '*.cpp' 2>/dev/null)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -lncurses -o $@

$(BUILD_DIR)/%.o: %.cpp $(VERSION_OUT)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(VERSION_OUT): $(VERSION_IN) $(VERSION_FILE)
	@mkdir -p $(dir $@)
	@VERSION_NUM=$$(cat $(VERSION_FILE) 2>/dev/null || echo "0.0.0"); \
	sed "s/@PROJECT_VERSION@/$$VERSION_NUM/g" $(VERSION_IN) > $@

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
