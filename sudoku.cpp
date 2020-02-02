#include <iostream>
#include <vector>
#include <random>
#include <ostream>
#include <algorithm>
#include <chrono>
#include <assert.h>

#define ROWS 9
#define COLUMNS 9

std::default_random_engine rng;

typedef std::vector<std::vector<int>> GridOfInts;
typedef std::vector<int> RowOfInts;

class SudokuBoard
{

public:
    SudokuBoard();
    SudokuBoard(GridOfInts &board);
    SudokuBoard insert_first_row();
    SudokuBoard insert_first_row(RowOfInts &row);
    SudokuBoard insert(int row, int col, int val);
    SudokuBoard fill_board();
    SudokuBoard fill_board(int row, int col, int val);
    bool is_valid(int row, int col);

    friend std::ostream &operator<<(std::ostream &os, const SudokuBoard &obj);

private:
    GridOfInts board;
};

SudokuBoard::SudokuBoard() : board(GridOfInts{9, RowOfInts(9, 0)}){};
SudokuBoard::SudokuBoard(GridOfInts &board) : board{board}
{
}

SudokuBoard SudokuBoard::insert_first_row()
{
    RowOfInts row{};
    for (int i = 0; i < COLUMNS; i++)
    {
        row.push_back(i + 1);
    }
    std::shuffle(row.begin(), row.end(), rng);

    return insert_first_row(row);
}

SudokuBoard SudokuBoard::insert_first_row(RowOfInts &row)
{
    auto new_board{board};
    new_board[0] = row;

    return SudokuBoard{new_board};
}

SudokuBoard SudokuBoard::fill_board()
{
    return SudokuBoard(*this);
}

SudokuBoard SudokuBoard::fill_board(int row, int col, int val)
{
    return SudokuBoard(*this);
}

bool SudokuBoard::is_valid(int row, int col)
{
    int value_to_check = board[row][col];

    assert(value_to_check != 0);

    for (int i = 0; i < 9; i++)
    {
        if (i != row)
        // check for duplicates in the same column
        {
            if (board[i][col] == value_to_check)
            {
                return false;
            }
        }

        if (i != col)
        {
            if (board[row][i] == value_to_check)
            {
                return false;
            }
        }
    }

    int m = row / 3;
    int n = col / 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m + i == row && n + j == col)
            {
                continue;
            }

            if (board[m + i][n + j] == value_to_check)
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const SudokuBoard &obj)
{
    std::string output = "";
    for (const auto &inner : obj.board)
    {
        for (const auto &item : inner)
        {
            output += std::to_string(item) + " ";
        }
        output += "\n";
    }
    return os << output;
}

SudokuBoard SudokuBoard::insert(int row, int col, int val)
{
    auto new_board = GridOfInts(board);
    new_board[row][col] = val;

    return SudokuBoard(new_board);
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
    // SudokuBoard sudoku;
    // sudoku.insert_first_row();
    // std::cout << "Content of Sudoku board:" << std::endl;
    // std::cout << sudoku << std::endl;
    std::vector<std::vector<int>> x{9, std::vector<int>(9, 0)};

    SudokuBoard board;
    board = board.insert_first_row().fill_board();

    SudokuBoard board2 = board.insert(1, 0, 9);

    std::cout << board2;
    std::cout << board2.is_valid(1, 0) << std::endl;
}
