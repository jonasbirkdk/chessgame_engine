CC = g++ -std=c++17 -Wpedantic
target = chess

DIRS = Bishop Castle ChessBoard King Knight Pawn Queen helper
DIRS.o = $(foreach var, $(DIRS), $(var)/$(var).o)

$(target): ChessMain.o $(DIRS.o)
	$(CC) ChessMain.o ${DIRS.o} -o $(target)

obj:
	$(CC) -c ChessMain.cpp -o ChessMain.o
	$(foreach var, $(DIRS), $(CC) -c $(var).cpp -o $(var).o;)

clean:
	rm -rf *.o $(DIRS.o) $(target)