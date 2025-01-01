#include "game_parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid number of arugment!" << std::endl;
        return -1;
    }
    std::ifstream input_file(argv[1]);
    std::string line;
    long int part_one_answer = 0;
    while (getline(input_file, line)) {
        GameParserPartOne parser_part_one(line, 12, 13, 14);
        if (!parser_part_one.IsGameValid()) {
            continue;
        }
        part_one_answer += parser_part_one.GetId();
    }
    std::cout << "Answer for part one is: " << part_one_answer << std::endl;
    return 0;
}