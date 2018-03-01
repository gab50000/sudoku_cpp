#include <iostream>
#include <vector>
#include <random>
#include <ostream>
#include <algorithm>
#include <chrono>


#define ROWS 9
#define COLUMNS 9


std::default_random_engine rng;


class SudokuBoard{
    public:
        std::vector<std::vector<int> > board;

        SudokuBoard(void);
        void insert_first_row();
};


SudokuBoard::SudokuBoard(){
    board.resize(ROWS, std::vector<int>(COLUMNS, 0));
}

void SudokuBoard::insert_first_row(){
    for (int i=0; i<board[0].size(); i++){
        board[0][i] = i + 1;
    }
    std::shuffle(board[0].begin(), board[0].end(), rng);
}


std::ostream& operator<<(std::ostream& os, const SudokuBoard& obj){
    rng.seed(time(0));
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
    SudokuBoard sudoku;
    sudoku.insert_first_row();
    std::cout << "Content of Sudoku board:" << std::endl;
    std::cout << sudoku << std::endl;
}
