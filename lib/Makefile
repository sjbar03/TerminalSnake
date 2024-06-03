OBJ = main.o board.o snake.o food.o


snake : $(OBJ)
	clang++ -o snake $(OBJ) -lncurses -std=c++17

main.o: main.cpp board.h
	clang++ -c main.cpp -std=c++17

board.o: board.cpp snake.h food.h
	clang++ -c board.cpp -std=c++17

snake.o: snake.cpp
	clang++ -c snake.cpp -std=c++17

food.o: food.cpp
	clang++ -c food.cpp -std=c++17

clean:
	rm snake $(OBJ)