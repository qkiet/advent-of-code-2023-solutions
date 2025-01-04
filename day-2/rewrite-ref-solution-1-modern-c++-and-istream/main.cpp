#include <sstream>
#include <iostream>
#include "game_stats.h"
#include <fstream>
#include <tuple>


bool is_game_valid(const GameStats &game_stats, int red_limit, int green_limit, int blue_limit) {
    for (auto &set_stats: game_stats.sets_stats) {
        for (auto &cube_stats: set_stats.cubes_stats) {
            if ((cube_stats.color == CubeColor::RED) && (cube_stats.count > red_limit))
                return false;
            if ((cube_stats.color == CubeColor::GREEN) && (cube_stats.count > green_limit))
                return false;
            if ((cube_stats.color == CubeColor::BLUE) && (cube_stats.count > blue_limit))
                return false;
        }
    }
    return true;
}

std::tuple<int, int, int> get_possible_cubes_count(const GameStats &game_stats) {
    int possible_red_cube_count = 0, possible_green_cube_count = 0, possible_blue_cube_count = 0;
    for (auto &set_stats: game_stats.sets_stats) {
        for (auto &cube_stats: set_stats.cubes_stats) {
            if ((cube_stats.color == CubeColor::RED) && (cube_stats.count > possible_red_cube_count))
                possible_red_cube_count = cube_stats.count;
            if ((cube_stats.color == CubeColor::GREEN) && (cube_stats.count > possible_green_cube_count))
                possible_green_cube_count = cube_stats.count;
            if ((cube_stats.color == CubeColor::BLUE) && (cube_stats.count > possible_blue_cube_count))
                possible_blue_cube_count = cube_stats.count;
        }
    }
    return {possible_red_cube_count, possible_green_cube_count, possible_blue_cube_count};
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Invalid number of arugment!" << std::endl;
        return -1;
    }
    std::ifstream input_file(argv[1]);
    std::string line;
    long int part_one_answer = 0;
    long int part_two_answer = 0;
    while (getline(input_file, line)) {
        GameStats game_stats;
        std::stringstream(line) >> game_stats;
        if (is_game_valid(game_stats, 12, 13, 14)) {
            part_one_answer += game_stats.id;
        }
        const auto [red_cube, green_cube, blue_cube] = get_possible_cubes_count(game_stats);
        const long int power = red_cube * green_cube * blue_cube;
        part_two_answer += power;
    }
    std::cout << "Answer for part one is: " << part_one_answer << std::endl;
    std::cout << "Answer for part two is: " << part_two_answer << std::endl;
    return 0;
}