NAME = slang

SRC_DIR = src
INC_DIR = include
OBJ_DIR = bin

CXX = clang++
CXX += $(addprefix -I,$(INC_DIR))
CXX += -Wall -Werror
CXX += -std=c++14 -stdlib=libc++
CXX += -O0 -g

LD = clang++

SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(OBJ_DIR)/$(NAME).release

default: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $^

$(TARGET): $(OBJ)
	$(LD) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJ)

all: clean default

run: default
	time $(TARGET)
