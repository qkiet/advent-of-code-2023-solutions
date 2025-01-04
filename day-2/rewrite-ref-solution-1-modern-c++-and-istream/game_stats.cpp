#include "game_stats.h"
#include <iostream>
#include <string>
#define RED_LIMIT 12
#define GREEN_LIMIT 13
#define BLUE_LIMIT 14

// A cube stat istream looks like this: (yes, include space before number)
// " 3 blue"
// "1 red"
// "5 green"
std::istream& operator>>(std::istream &is, CubeStats &cube_stats) {
    is >> cube_stats.count;
    // Ignore space " "
    is.ignore(1);
    char first_char;
    is >> first_char;
    switch (first_char)
    {
    case 'r':
        cube_stats.color = CubeColor::RED;
        is.ignore(2);
        break;
    case 'g':
        cube_stats.color = CubeColor::GREEN;
        is.ignore(4);
        break;
    case 'b':
        cube_stats.color = CubeColor::BLUE;
        is.ignore(3);
        break;
    }
#ifdef DEBUG
        std::cout << "Extracted cube stats: " << cube_stats << std::endl;
#endif
    return is;
}

std::ostream& operator<<(std::ostream &os, CubeStats &cube_stats) {
    os << "{\"color\": ";
    switch (cube_stats.color)
    {
    case CubeColor::RED:
        os << "\"red\"";
        break;
    case CubeColor::GREEN:
        os << "\"green\"";
        break;
    case CubeColor::BLUE:
        os << "\"blue\"";
        break;
    }
    os << ", \"count\": " << cube_stats.count << "}";
    return os;
}


// A game set istream looks like this:
// "3 blue, 4 red;"
// "1 red, 2 green;"
// "3 red, 3 blue;"
std::istream& operator>>(std::istream &is, GameSetStats &set_stats) {
    set_stats.cubes_stats.clear();
    CubeStats cube_stats;
    while(true) {
        is >> cube_stats;
        set_stats.cubes_stats.push_back(cube_stats);
        if (is.peek() == EOF) {
            break;
        }
        char c;
        is.get(c);
        if (c == ';') {
            break;
        }
    }
#ifdef DEBUG
        std::cout << "Extracted set stats: " << set_stats << std::endl;
#endif
    return is;
}

std::ostream& operator<<(std::ostream &os, GameSetStats &set_stats) {
    os << "[";
    for (auto &cube_stats : set_stats.cubes_stats) {
        os << cube_stats;
        os << ", ";
    }
    os << "]";
    return os;
}

// A particular game istream looks like this:
// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
std::istream& operator>>(std::istream &is, GameStats &game_stats) {
    game_stats.sets_stats.clear();
    is.ignore(5);
#ifdef DEBUG_BUFF
    std::cout <<"Stream now: "<< is.rdbuf() << std::endl;
#endif
    is >> game_stats.id;
#ifdef DEBUG_BUFF
    std::cout <<"Stream now: "<< is.rdbuf() << std::endl;
#endif
    is.ignore(1);
#ifdef DEBUG_BUFF
    std::cout <<"Stream now: "<< is.rdbuf() << std::endl;
#endif

    GameSetStats set_stats;
    while (true) {
        is >> set_stats;
#ifdef DEBUG_DEEP
        std::cout << "Extracted set stats for appending game stats: " << set_stats << std::endl;
#endif
        game_stats.sets_stats.push_back(set_stats);
        if (is.peek() == EOF) {
            break;
        }
    }
#ifdef DEBUG
        std::cout << "Extracted game stats: " << game_stats << std::endl;
#endif
    return is;
}

std::ostream& operator<<(std::ostream &os, GameStats &game_stats) {
    os << "{\"game_id\": " << game_stats.id << ", \"sets\": [";
    for (auto &set_stats : game_stats.sets_stats) {
        os << set_stats;
        os << ", ";
    }
    os << "]}";
    return os;
}
