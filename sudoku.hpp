#include <vector>
#include <optional>

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