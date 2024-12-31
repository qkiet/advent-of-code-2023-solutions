#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <map>
#include <locale>

using namespace std;

map<string, unsigned int> text_to_number = {
    {"one", '1'},
    {"two", '2'},
    {"three", '3'},
    {"four", '4'},
    {"five", '5'},
    {"six", '6'},
    {"seven", '7'},
    {"eight", '8'},
    {"nine", '9'},
};

// Return 0 if success, -1 otherwise
int try_convert_to_digit(const string& str, size_t pos, char& digit) {
    size_t possible_substring_len = str.length() - pos;
    if (possible_substring_len < 3)
        return -1;
    for (auto it = text_to_number.begin(); it != text_to_number.end(); it++) {
        string num_text = it->first;
        if (possible_substring_len < num_text.length()) {
            continue;
        }
        string substr_to_check = str.substr(pos, num_text.length());
        if (substr_to_check.compare(num_text) == 0) {
            digit = it->second;
            return 0;
        }
    }
    return -1;
}

unsigned int part_one_get_calibrated_value(const string& str) {
    string calibrated_value_str = "";
    for (auto it = str.begin(); it != str.end(); ++it) {
        const auto c = *it;
        if (isdigit(c)) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            calibrated_value_str += c;
            break;
        }
    }

    // Yes, DO THIS TO REVERSE ITERATING. DO NOT use begin(), end() because it shall
    // miss the first element!!!. Refer to https://cplusplus.com/reference/string/string/end/
    // and https://cplusplus.com/reference/string/string/begin/ to know why
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        const auto c = *it;
        if (isdigit(c)) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            calibrated_value_str += c;
            break;
        }
    }
    return unsigned(stoi(calibrated_value_str));
}

unsigned int part_two_get_calibrated_value(const string& str) {
    string calibrated_value_str = "";
    for (auto it = str.begin(); it != str.end(); ++it) {
        const auto c = *it;
        if (isdigit(c)) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            calibrated_value_str += c;
            break;
        }
        char digit_from_spelling;
        if (try_convert_to_digit(str, distance(str.begin(), it), digit_from_spelling) != -1) {
            calibrated_value_str += digit_from_spelling;
            break;
        }
    }

    // Yes, DO THIS TO REVERSE ITERATING. DO NOT use begin(), end() because it shall
    // miss the first element!!!. Refer to https://cplusplus.com/reference/string/string/end/
    // and https://cplusplus.com/reference/string/string/begin/ to know why
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        const auto c = *it;
        if (isdigit(c)) {
            // Fast conversion using ASCII. I hate using library just for this :-)
            calibrated_value_str += c;
            break;
        }
        char digit_from_spelling;
        if (try_convert_to_digit(str, str.length() - distance(str.rbegin(), it) - 1, digit_from_spelling) != -1) {
            calibrated_value_str += digit_from_spelling;
            break;
        }
    }
    return unsigned(stoi(calibrated_value_str));
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
        const auto part_one_calibrated_value = part_one_get_calibrated_value(str);
        const auto part_two_calibrated_value = part_two_get_calibrated_value(str);
        part_one_result += part_one_calibrated_value;
        part_two_result += part_two_calibrated_value;
    }
    printf("Part 1 result is %lu\n", part_one_result);
    printf("Part 2 result is %lu\n", part_two_result);
    input_file.close();
    return 0;
}
