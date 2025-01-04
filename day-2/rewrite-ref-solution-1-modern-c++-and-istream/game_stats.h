#include <string>
#include <vector>
#include <istream>

enum CubeColor { RED, GREEN, BLUE };

struct CubeStats {
    CubeColor color;
    int count;
};

std::istream& operator>>(std::istream &is, struct CubeStats &cube_stats);
std::ostream& operator<<(std::ostream &os, struct CubeStats &cube_stats);


struct GameSetStats {
    std::vector<struct CubeStats> cubes_stats;
};

std::istream& operator>>(std::istream &is, struct GameSetStats &set_stats);
std::ostream& operator<<(std::ostream &os, struct GameSetStats &cube_stats);

struct GameStats {
    int id;
    std::vector<struct GameSetStats> sets_stats;
};

std::istream& operator>>(std::istream &is, struct GameStats &game_stats);
std::ostream& operator<<(std::ostream &os, struct GameStats &cube_stats);
