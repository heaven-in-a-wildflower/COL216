CC = g++
CFLAGS = -std=c++11 -Wall -Wextra --pedantic

SRC = cacheSim.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = cacheSim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJ)
