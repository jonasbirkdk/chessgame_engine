CC = clang++ -std=c++17 -Wall
target = chess
	
PIECES = Bishop Castle King Knight Pawn Queen helper
PIECES.o = $(foreach var, $(PIECES), $(var)/$(var).o)

$(target): ChessMain.o ChessBoard.o $(PIECES.o)
	$(CC) ChessMain.o ChessBoard.o ${PIECES.o} -o $(target)

obj:
	$(CC) -c ChessMain.cpp -o ChessMain.o
	$(CC) -c ChessBoard.cpp -o ChessBoard.o
	$(foreach var, $(PIECES), $(CC) -c $(var).cpp -o $(var).o;)

clean:
	rm -rf *.o $(PIECES.o) $(target)