# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
RAYLIB = -lraylib -lm -ldl -lpthread -lGL



# Finds if user went "make $build run"
# if it dead, BIN == "$build" value
GOALS := $(filter-out run, $(MAKECMDGOALS))

ifeq ($(strip $(GOALS)),)
   BIN := default
else
   BIN := $(firstword $(GOALS))
endif


%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(RAYLIB)

.PHONY: run
run: 
	./$(BIN)

win:
	gcc basicw.c -o example.exe -lraylib -lglfw3 -lopengl32 -lgdi32

basic_window:
	gcc basicw.c -o example -lraylib -lm -ldl -lpthread -lGL

