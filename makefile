# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Source files
PIECE_SRCS = $(SRC_DIR)/pieces/Bishop.cpp $(SRC_DIR)/pieces/King.cpp \
             $(SRC_DIR)/pieces/Knight.cpp $(SRC_DIR)/pieces/Pawn.cpp \
             $(SRC_DIR)/pieces/Queen.cpp $(SRC_DIR)/pieces/Rook.cpp
BASE_PIECE_SRC = $(SRC_DIR)/Piece.cpp
UTILS_SRC = $(SRC_DIR)/Utils.cpp
GAME_SRC = $(SRC_DIR)/Game.cpp
DRIVER_SRC = $(SRC_DIR)/Driver.cpp

SRCS = $(PIECE_SRCS) $(BASE_PIECE_SRC) $(UTILS_SRC) $(GAME_SRC) $(DRIVER_SRC)

# Object files
PIECE_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(PIECE_SRCS))
BASE_PIECE_OBJ = $(OBJ_DIR)/Piece.o
UTILS_OBJ = $(OBJ_DIR)/Utils.o
GAME_OBJ = $(OBJ_DIR)/Game.o
DRIVER_OBJ = $(OBJ_DIR)/Driver.o

OBJS = $(UTILS_OBJ) $(BASE_PIECE_OBJ) $(PIECE_OBJS) $(GAME_OBJ) $(DRIVER_OBJ)

# Executable
TARGET = ChessBot

# Rules
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean

