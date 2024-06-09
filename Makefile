OBJ = main.o board.o snake.o food.o keylistener.o
ODIR = obj/
SDIR = lib/
STD = -std=c++20
INC = -I lib/
CC = g++


snake : $(addprefix $(ODIR), $(OBJ))
	$(CC) -o $@ $(addprefix $(ODIR), $(OBJ)) $(STD) $(INC)

main.o: $(addprefix $(SDIR),main.cpp board.h)
	$(CC) -c $(addprefix $(SDIR),main.cpp) $(STD)

board.o: $(addprefix $(SDIR),board.cpp snake.h food.h)
	$(CC) -c $(addprefix $(SDIR),board.cpp) $(STD)

snake.o: $(addprefix $(SDIR),snake.cpp)
	$(CC) -c $(addprefix $(SDIR),snake.cpp) $(STD)

food.o: $(addprefix $(SDIR),food.cpp)
	$(CC) -c $(addprefix $(SDIR),food.cpp) $(STD)

keylistener.o: $(addprefix $(SDIR),keylistener.cpp)
	$(CC) -c $(addprefix $(SDIR),keylistener.cpp) $(STD)

clean:
	rm snake $(addprefix $(ODIR), $(OBJ))