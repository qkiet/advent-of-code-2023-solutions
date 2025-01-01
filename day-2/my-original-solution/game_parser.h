#include <string>
#include <tuple>

class GameParserPartOne {
public:
    GameParserPartOne(const std::string &game_text, int red_limit, int green_limit, int blue_limit);
    bool IsGameValid();
    int GetId();
private:
    // I know game id is supposed to be unsigned. But there is currently
    // no way to seamlessly convert string to unsigned integer. If so,
    // I have to use...unsigned long int (which is too bing)
    int mGameId;
    bool mIsValid;
};

class GameParserPartTwo {
public:
    GameParserPartTwo(const std::string &game_text);
    std::tuple<int, int, int> GetPossibleNumberOfCubes();
private:
    int mPossibleNumberOfRedCubes;
    int mPossibleNumberOfGreenCubes;
    int mPossibleNumberOfBlueCubes;
};
