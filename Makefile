chess: ChessMain.o
	g++ -g -Wall ChessMain.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h helper.h Pawn.h Queen.h Bishop.h Castle.h Piece.h Knight.h macros.h
	g++ -c -g -Wall ChessMain.cpp -o ChessMain.o

# chess: ChessMain.o ChessBoard.o Pieces.o macros.o helper.o
# 	g++ -g -Wall ChessMain.o ChessBoard.o helper.o macros.o Pieces.o -o chess

# ChessMain.o: ChessMain.cpp ChessBoard.h helper.h macros.h Pieces.h
# 	g++ -c -g -Wall ChessMain.cpp -o ChessMain.o

# ChessBoard.o: ChessBoard.h Pieces.h helper.h macros.h
# 	g++ -c -g -Wall ChessBoard.h -o ChessBoard.o

# Pieces.o: Pieces.h ChessBoard.h helper.h macros.h
# 	g++ -c -g -Wall Pieces.h -o Pieces.o

# helper.o: helper.h ChessBoard.h macros.h Pieces.h
# 	g++ -c -g -Wall helper.h -o helper.o

# macros.o: macros.h helper.h ChessBoard.h Pieces.h
# 	g++ -c -g -Wall macros.h -o macros.o

clean: 
	rm -rf *.o chess