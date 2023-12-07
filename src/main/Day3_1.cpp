#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const char symbols[10] = {'@', '#', '$', '%', '&', '*', '=', '+', '-', '/'};
vector<string> lines;

int findPartNumberLeft(int lineNum, int linePos) {
    string line = lines[lineNum];
    int current = 0;
    int factor = 1;
    while (linePos >= 0 && isdigit(line.at(linePos))) {
        current += (line.at(linePos) - '0') * factor;
        factor *= 10;
        linePos--;
    }
    return current;
}

int findPartNumberRight(int lineNum, int linePos) {
    string line = lines[lineNum];
    int current = 0;
    while (linePos < line.length() && isdigit(line.at(linePos))) {
        current *= 10;
        current += (line.at(linePos) - '0');
        linePos++;
    }
    return current;
}

int findPartNumbersVertical(int lineNum, int linePos) {
    string line = lines[lineNum];

    if (isdigit(line.at(linePos))) {
        int current = line.at(linePos) - '0';

        int j = linePos - 1;
        int factor = 10;
        while (j >= 0 && isdigit(line.at(j))) {
            current += (line.at(j) - '0') * factor;
            factor *= 10;
            j--;
        }

        j = linePos + 1;
        while (j < line.length() && isdigit(line.at(j))) {
            current *= 10;
            current += (line.at(j) - '0');
            j++;
        }
        return current;
    }

    int total = 0;

    total += findPartNumberLeft(lineNum, linePos - 1);
    total += findPartNumberRight(lineNum, linePos + 1);

    return total;
}

int findPartNumbers(int lineNum, int linePos) {
    int total = 0;

    total += findPartNumberLeft(lineNum, linePos - 1);
    total += findPartNumberRight(lineNum, linePos + 1);

    if (lineNum > 0) {
        total += findPartNumbersVertical(lineNum - 1, linePos);
    }
    if (lineNum < lines.size() - 1) {
        total += findPartNumbersVertical(lineNum + 1, linePos);
    }

    return total;
}

int checkLine(int lineNum) {
    string line = lines[lineNum];
    int lineTotal = 0;
    for (char symbol : symbols) {
        size_t linePos = line.find(symbol);
        while (linePos != string::npos) {
            lineTotal += findPartNumbers(lineNum, linePos);
            linePos = line.find(symbol, linePos + 1);
        }
    }
    return lineTotal;
}

int main() {
    fstream input;
    
    input.open("C:/Users/matth/Documents/GitHub/advent-of-code-2023/data/Day3.txt", iostream::in);

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            lines.push_back(line);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    int total = 0;

    for (int i = 0; i < lines.size(); i++) {
        total += checkLine(i);
    }

    cout << "total: ";
    cout << total;
}