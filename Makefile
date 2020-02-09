CC=g++
CFLAGS = -g -Wall -std=c++17


default: sudoku


sudoku: sudoku.cpp
	$(CC) $(CFLAGS) -o sudoku sudoku.cpp

main: sudoku
	$(CC) $(CFLAGS) -o main main.cpp

clean:
	$(RM) sudoku main