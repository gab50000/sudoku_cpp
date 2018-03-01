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
    SudokuBoard sudoku;
    std::cout << "Content of Sudoku board:" << std::endl;
    std::cout << sudoku << std::endl;
}
