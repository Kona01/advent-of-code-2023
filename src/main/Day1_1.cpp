#include <iostream>
#include <fstream>
#include <string>

int main() {
    fstream input;

    input.open("Day1.txt", iostream::in);

    int total = 0;

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            total += readline(line);
        }
    }

    cout << total
}

int readline(string line) {
    int length = line.length();
    int result = 0;
    for (int i = 0; i < length; i++) {
        if (isdigit(s.at(i))) {
            result = s.at(i) * 10;
            break;
        }
    }
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(s.at(i))) {
            result += s.at(i);
            break;
        }
    }
}