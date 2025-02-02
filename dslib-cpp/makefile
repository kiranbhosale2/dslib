CC = g++
CFLAGS = -Wall -Iqueue -Ilist # Add queue directory to include path

TESTS = tests
SRC = $(wildcard $(TESTS)/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = dslib

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
