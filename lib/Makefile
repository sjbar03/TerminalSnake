OBJ = main.o board.o snake.o food.o keylistener.o
STD = -std=c++20
LFLAG =
CC = g++


snake : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LFLAG) $(STD)

main.o: main.cpp board.h
	$(CC) -c main.cpp $(STD)

board.o: board.cpp snake.h food.h
	$(CC) -c board.cpp $(STD)

snake.o: snake.cpp
	$(CC) -c snake.cpp $(STD)

food.o: food.cpp
	$(CC) -c food.cpp $(STD)

keylistener.o: keylistener.cpp
	$(CC) -c keylistener.cpp $(STD)

clean:
	rm snake $(OBJ)