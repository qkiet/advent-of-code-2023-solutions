#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <cstdio>

using namespace std;

tuple<unsigned int, unsigned int> get_first_last_numbers_from_string(const string& str) {
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


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Expect only one argument, which is filename!" << endl;
        return -1;
    }
    ifstream input_file("input.txt");
    string str;
    unsigned long int result = 0;
    while (getline(input_file, str)) {
        const auto pair_of_number = get_first_last_numbers_from_string(str);
        auto first_digit = get<0>(pair_of_number);
        auto second_digit = get<1>(pair_of_number);
        auto number = get<0>(pair_of_number) * 10 + get<1>(pair_of_number);
        result += number;
    }
    printf("Result is %lu\n", result);
    input_file.close();
    return 0;
}
