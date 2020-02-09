#include <fstream>
#include <iostream>
#include <iterator>
#include "sudoku.hpp"

void read_file(const std::string &filename)
{
    std::ifstream infile(filename);

    std::istream_iterator<std::string> iter(infile);
    std::istream_iterator<std::string> endIter;

    while (iter != endIter)
    {
        std::cout << *iter++ << std::endl;
    }
}

std::vector<int> read_ints(const std::string &filename)
{
    std::ifstream infile(filename);
    std::istream_iterator<int> iter(infile);
    std::istream_iterator<int> endIter;

    std::vector<int> vec{iter, endIter};
    return vec;
}

int main(int argc, char **argv)
{

    if (argc > 1)
    {
        std::cout << argv[1] << std::endl;
        // read_file(argv[1]);
        auto vec = read_ints(argv[1]);

        for (const int &x : vec)
        {
            std::cout << x << std::endl;
        }
    }
}