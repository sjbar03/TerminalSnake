snake : bin/main.cpp lib/board.cpp lib/food.cpp lib/snake.cpp
	clang++ -o snake bin/main.cpp lib/board.cpp lib/food.cpp lib/snake.cpp -I lib \
	 -lncurses -std=c++17

.PHONY: clean

clean:
	rm snake