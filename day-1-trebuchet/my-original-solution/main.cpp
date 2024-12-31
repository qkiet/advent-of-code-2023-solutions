#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <cstdio>
#include <map>

using namespace std;

map<string, unsigned int> text_to_number = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

// Return 0 if success, -1 otherwise
int try_convert_to_number(const string& str, unsigned int pos, unsigned int& number) {
    unsigned int possible_substring_len = str.length() - pos;
    if (possible_substring_len < 3)
        return -1;
    //  Why 5? 5 is the max length of all text number, which are "three" and "eight"
    for (auto it = text_to_number.begin(); it != text_to_number.end(); it++) {
        string num_text = it->first;
        if (possible_substring_len < num_text.length()) {
            continue;
        }
        string substr_to_check = str.substr(pos, num_text.length());
        if (substr_to_check.compare(num_text) == 0) {
            number = it->second;
            return 0;
        }
    }
    return -1;
}

tuple<unsigned int, unsigned int> part_one_get_pair_of_first_last_numbers(const string& str) {
    unsigned int first_digit, last_digit;
    for (auto it = str.begin(); it != str.end(); ++it) {
        const auto c = *it;
        if (('0' <= c) && (c <= '9')) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            first_digit = c - 48;
            break;
        }
    }

    // Yes, DO THIS TO REVERSE ITERATING. DO NOT use begin(), end() because it shall
    // miss the first element!!!. Refer to https://cplusplus.com/reference/string/string/end/
    // and https://cplusplus.com/reference/string/string/begin/ to know why
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        const auto c = *it;
        if (('0' <= c) && (c <= '9')) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            last_digit = c - 48;
            break;
        }
    }
    return {first_digit, last_digit};
}

tuple<unsigned int, unsigned int> part_two_get_pair_of_first_last_numbers(const string& str) {
    unsigned int first_digit, last_digit;
    for (auto it = str.begin(); it != str.end(); ++it) {
        const auto c = *it;
        if (('0' <= c) && (c <= '9')) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            first_digit = c - 48;
            break;
        }
        // Then check text to number
        if (try_convert_to_number(str, distance(str.begin(), it), first_digit) != -1) {
            break;
        }
    }

    // Yes, DO THIS TO REVERSE ITERATING. DO NOT use begin(), end() because it shall
    // miss the first element!!!. Refer to https://cplusplus.com/reference/string/string/end/
    // and https://cplusplus.com/reference/string/string/begin/ to know why
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        const auto c = *it;
        if (('0' <= c) && (c <= '9')) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            last_digit = c - 48;
            break;
        }
        // Then check text to number. For reverse iterator, I have to do some clever like this
        if (try_convert_to_number(str, str.length() - distance(str.rbegin(), it) - 1, last_digit) != -1) {
            break;
        }
    }
    return {first_digit, last_digit};
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Expect only one argument, which is filename!" << endl;
        return -1;
    }
    ifstream input_file(argv[1]);
    string str;
    unsigned long int part_one_result = 0;
    unsigned long int part_two_result = 0;
    while (getline(input_file, str)) {
        const auto part_one_pair_of_numbers = part_one_get_pair_of_first_last_numbers(str);
        const auto part_two_pair_of_numbers = part_two_get_pair_of_first_last_numbers(str);
        part_one_result += get<0>(part_one_pair_of_numbers) * 10 + get<1>(part_one_pair_of_numbers);
        part_two_result += get<0>(part_two_pair_of_numbers) * 10 + get<1>(part_two_pair_of_numbers);
    }
    printf("Part 1 result is %lu\n", part_one_result);
    printf("Part 2 result is %lu\n", part_two_result);
    input_file.close();
    return 0;
}
