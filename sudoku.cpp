#include <iostream>
#include <vector>
#include <random>
#include <ostream>


#define ROWS 9
#define COLUMNS 9


class SudokuBoard{
    public:
        SudokuBoard(void);
        std::vector<std::vector<int> > board;
};


SudokuBoard::SudokuBoard(){
    board.resize(ROWS, std::vector<int>(COLUMNS, 0));
}


std::ostream& operator<<(std::ostream& os, const SudokuBoard& obj){
    for (const auto& inner: obj.board){
        for (const auto& item: inner){
            std::cout << item << " ";
        }
    }
}


int main(){
    SudokuBoard sudoku;
    std::cout << "Hi there" << std::endl;
    std::cout << sudoku << std::endl;
}