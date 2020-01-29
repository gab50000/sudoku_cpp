#include <iostream>
#include <vector>
#include <random>
#include <ostream>
#include <algorithm>
#include <chrono>


#define ROWS 9
#define COLUMNS 9


std::default_random_engine rng;

typedef std::vector<std::vector<int>> GridOfInts;
typedef std::vector<int> RowOfInts;

class SudokuBoard{
    const GridOfInts board;

    public:
        SudokuBoard();
        SudokuBoard(GridOfInts& board);
        SudokuBoard insert_first_row();
        SudokuBoard insert_first_row(RowOfInts& row);
        SudokuBoard fill_board();
        SudokuBoard fill_board(int row, int col, int val);

    friend std::ostream& operator<<(std::ostream& os, const SudokuBoard& obj);
};

SudokuBoard::SudokuBoard() : board(GridOfInts{9, RowOfInts(9, 0)}){};
SudokuBoard::SudokuBoard(GridOfInts& board) : board {board}{
}

SudokuBoard SudokuBoard::insert_first_row(){
    RowOfInts row{};
    for (int i=0; i < COLUMNS; i++){
        row.push_back(i+1);
    }
    std::shuffle(row.begin(), row.end(), rng);

    return insert_first_row(row);
}

SudokuBoard SudokuBoard::insert_first_row(RowOfInts& row){
    auto new_board{board};
    new_board[0] = row;

    return SudokuBoard{new_board};
}


SudokuBoard SudokuBoard::fill_board(){
    return *this;
}
SudokuBoard SudokuBoard::fill_board(int row, int col, int val){

}


std::ostream& operator<<(std::ostream& os, const SudokuBoard& obj){
    std::string output = "";
    for (const auto& inner: obj.board){
        for (const auto& item: inner){
            output += std::to_string(item) + " ";
        }
        output += "\n";
    }
    return os << output;
}


int main(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    // SudokuBoard sudoku;
    // sudoku.insert_first_row();
    // std::cout << "Content of Sudoku board:" << std::endl;
    // std::cout << sudoku << std::endl;
    std::vector<std::vector<int>> x{9, std::vector<int>(9, 0)};

    SudokuBoard board;

    std::cout << board.insert_first_row().fill_board();

}
