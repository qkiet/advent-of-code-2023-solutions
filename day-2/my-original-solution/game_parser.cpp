#include "game_parser.h"
#include <boost/tokenizer.hpp>
#include <iostream>


static bool is_string_a_number(const std::string &str) {
    for (const auto &c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Parse the game text immediately
// Example: 
// - Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
// - Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
GameParserPartOne::GameParserPartOne(const std::string &game_text, int red_limit, int green_limit, int blue_limit) {
    size_t colon_pos = game_text.find(':');
    const std::string game_id_substr = game_text.substr(0, colon_pos);
    const std::string game_result_substr = game_text.substr(colon_pos);
    boost::tokenizer tok_id(game_id_substr);
    for(boost::tokenizer<>::iterator it=tok_id.begin(); it!=tok_id.end();++it){
        if (is_string_a_number(*it)) {
            mGameId = stoi(*it);
            break;
        }
    }
    boost::tokenizer<> set_result_token(game_result_substr);

    bool is_valid = true;
    for(boost::tokenizer<>::iterator it=set_result_token.begin(); it!=set_result_token.end(); ++it) {
        int cube_number;
        // Because a token is either a number or a string (one of "red", "blue", "green")
        // with number token always come first, we can do a trick like these
        if (is_string_a_number(*it)) {
            cube_number = std::stoi(*it);
        } else {
            if (std::string(*it).find("red") == 0) {
                if (cube_number <= red_limit) {
                    continue;
                }
            } else if (std::string(*it).find("blue") == 0) {
                if (cube_number <= blue_limit) {
                    continue;
                }
            } else if (std::string(*it).find("green") == 0) {
                if (cube_number <= green_limit) {
                    continue;
                }
            }
            is_valid = false;
        }
    }
    mIsValid = is_valid;
}

int GameParserPartOne::GetId() {
    return mGameId;
}

bool GameParserPartOne::IsGameValid() {
    return mIsValid;
}
