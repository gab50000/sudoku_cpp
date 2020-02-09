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

int main(int argc, char **argv)
{

    if (argc > 1)
    {
        std::cout << argv[1] << std::endl;
        read_file(argv[1]);
    }
}