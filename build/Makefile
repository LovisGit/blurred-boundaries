# Compiler
CC := g++

# Compiler flags without stack-protection
#CFLAGS := -I../include `sdl2-config --cflags` -ggdb3 -O0 -std=c++11 -Wall -fno-stack-protector -z execstack

UNAME_S := $(shell uname -s)
CFLAGS := -I../include `sdl2-config --cflags` -ggdb3 -O0 -std=c++11 -Wall -fno-stack-protector
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -I/opt/homebrew/include
else
    CFLAGS += -z execstack -no-pie -fno-plt -fcf-protection=none
endif

# Libraries
LIBS := `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm

# Directories
SRC_DIR := ../src
BUILD_DIR := objects/

# Source files
SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/player.cpp $(SRC_DIR)/camera.cpp $(SRC_DIR)/object.cpp $(SRC_DIR)/objectAdminstrator.cpp

# Object files (replace path from .cpp to .o in build directory)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Name of executable
EXEC := blurred_boundaries

# Default target
all: $(EXEC)

# Target: Create executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBS)

# Target: Compile individual .cpp files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)  # Create directory if it doesn't exist
	$(CC) -c -o $@ $< $(CFLAGS)

# Target: Clean build files
clean:
	rm -rf $(EXEC) $(BUILD_DIR)

.PHONY: all clean
