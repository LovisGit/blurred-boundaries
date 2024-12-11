# Compiler
CC := g++

# Compiler-Flags
CFLAGS := -I../include `sdl2-config --cflags` -ggdb3 -O0 -std=c++11 -Wall

# Bibliotheken
LIBS := `sdl2-config --libs` -lSDL2_image -lm

# Verzeichnisse
SRC_DIR := ../src
BUILD_DIR := objects/

# Quellcode-Dateien
SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/player.cpp

# Objektdateien (ersetze Pfad von .cpp durch .o im Build-Verzeichnis)
OBJS := $(SRCS:../src/%.cpp=objects/%.o) # $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Name der ausführbaren Datei
EXEC := blurred_boundaries

# Standardziel
all: $(EXEC)

# Ziel: Erstellung der ausführbaren Datei
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBS)

# Ziel: Kompilierung einzelner .cpp-Dateien zu .o-Dateien
#$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
#	mkdir -p $(BUILD_DIR)  # Verzeichnis erstellen, falls es nicht existiert
#	$(CC) -c -o $@ $< $(CFLAGS)

objects/%.o: ../src/%.cpp
	mkdir -p $(dir $@)  # Erstelle das Verzeichnis "objects/" falls nötig
	$(CC) -c -o $@ $< $(CFLAGS)


# Ziel: Bereinigung
clean:
	rm -rf $(EXEC) $(BUILD_DIR)

.PHONY: all clean
