
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
RAYLIB = -lraylib -lm -ldl -lpthread -lGL

SRC_DIR   =
BUILD_DIR =bin

# every build target must depend on this
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Finds if user went "make $build run"
# if it dead, BIN == "$build" value
GOALS := $(filter-out run, $(MAKECMDGOALS))

ifeq ($(strip $(GOALS)), )
   BIN := default
else
   BIN := $(firstword $(GOALS))
endif

%: %.cpp $(BUILD_DIR) 
	@echo "Removing older binary"
	@rm -rf $(BUILD_DIR)/$@

	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ $@.cpp $(RAYLIB)


.PHONY: run
run: 
	$(BUILD_DIR)/$(BIN)

.PHONY: clean
clean: 
	@ls $(BUILD_DIR)

#win:
#	gcc basicw.c -o example.exe -lraylib -lglfw3 -lopengl32 -lgdi32


