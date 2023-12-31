#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int readLine(string line) {
    int length = line.length();
    int result = 0;
    for (int i = 0; i < length; i++) {
        if (isdigit(line.at(i))) {
            int num = line.at(i) - '0';
            result = num * 10;
            break;
        }
    }
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(line.at(i))) {
            int num = line.at(i) - '0';
            result += num;
            break;
        }
    }
    return result;
}

int main() {
    fstream input;
    
    input.open("C:/Users/matth/Documents/GitHub/advent-of-code-2023/data/Day1.txt", iostream::in);

    int total = 0;

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            total += readLine(line);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    cout << "total: ";
    cout << total;
}