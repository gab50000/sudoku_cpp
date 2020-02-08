#include <iostream>
#include <vector>
#include <random>
#include <ostream>
#include <algorithm>
#include <chrono>
#include <assert.h>
#include <optional>

#define ROWS 9
#define COLUMNS 9

std::default_random_engine rng;

typedef std::vector<std::vector<int>> GridOfInts;
typedef std::vector<int> RowOfInts;

class SudokuBoard
{

public:
    SudokuBoard();
    SudokuBoard(const GridOfInts &board);
    SudokuBoard insert_first_row();
    SudokuBoard insert_first_row(const RowOfInts &row);
    SudokuBoard insert(int row, int col, int val);
    SudokuBoard fill_board();
    std::optional<SudokuBoard> fill_board(int row, int col);
    bool is_valid(int row, int col);

    friend std::ostream &operator<<(std::ostream &os, const SudokuBoard &obj);

private:
    GridOfInts board;
};

SudokuBoard::SudokuBoard() : board(GridOfInts{ROWS, RowOfInts(COLUMNS, 0)}){};

SudokuBoard::SudokuBoard(const GridOfInts &board) : board{board}
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

SudokuBoard SudokuBoard::insert_first_row(const RowOfInts &row)
{
    auto new_board{board};
    new_board[0] = row;

    return SudokuBoard{new_board};
}

SudokuBoard SudokuBoard::fill_board()
{
    return SudokuBoard(*this);
}

std::optional<SudokuBoard> SudokuBoard::fill_board(int row, int col)
{

    int next_col = (col + 1) % COLUMNS;
    int next_row = next_col == 0 ? row + 1 : row;

    for (int i = 1; i < 10; i++)
    {
        auto new_board = this->insert(row, col, i);
        if (new_board.is_valid(row, col))
        {
            std::cout << "New board: " << std::endl
                      << new_board << std::endl;

            // Check if we reached the end
            if (next_row == ROWS)
            {
                std::cout << "Reached the end" << std::endl;
                return new_board;
            }

            auto solution = new_board.fill_board(next_row, next_col);
            if (solution.has_value())
            {
                return solution.value();
            }
            else
            {
                std::cout << "Found no solution for board[" << row << "][" << col << "] = " << i << std::endl;
            }
        }
    }

    std::cout << "Returning nothing" << std::endl;
    return {};
}

bool SudokuBoard::is_valid(int row, int col)
{
    int value_to_check = board[row][col];

    assert(value_to_check != 0);

    for (int i = 0; i < ROWS; i++)
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

    int m = (row / 3) * 3;
    int n = (col / 3) * 3;

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

    SudokuBoard board;
    board = board.insert_first_row();

    auto solution = board.fill_board(1, 0);

    if (solution.has_value())
    {
        std::cout << solution.value();
    }
}
