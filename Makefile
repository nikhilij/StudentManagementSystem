CC = g++
CFLAGS = -std=c++17 -Wall
TARGET = StudentManagementSystem
SRC_DIR = src
INCLUDE_DIR = include
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

.PHONY: clean run

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
