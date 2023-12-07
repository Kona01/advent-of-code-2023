#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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
    
    if (current == 0) current = 1;

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
    
    if (current == 0) current = 1;

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

    int total = 1;

    total *= findPartNumberLeft(lineNum, linePos - 1);
    total *= findPartNumberRight(lineNum, linePos + 1);

    return total;
}

bool isGear(int lineNum, int linePos) {
    int adjacentPartNums = 0;
    if (isdigit(lines[lineNum].at(linePos - 1))) adjacentPartNums++;
    if (isdigit(lines[lineNum].at(linePos + 1))) adjacentPartNums++;
    
    if (lineNum > 0) {
        if (isdigit(lines[lineNum - 1].at(linePos))) {
            adjacentPartNums++;
        } else {
            if (isdigit(lines[lineNum - 1].at(linePos - 1))) adjacentPartNums++;
            if (isdigit(lines[lineNum - 1].at(linePos + 1))) adjacentPartNums++;
        }
    }

    if (lineNum < lines.size() - 1) {
        if (isdigit(lines[lineNum + 1].at(linePos))) {
            adjacentPartNums++;
        } else {
            if (isdigit(lines[lineNum + 1].at(linePos - 1))) adjacentPartNums++;
            if (isdigit(lines[lineNum + 1].at(linePos + 1))) adjacentPartNums++;
        }
    }

    return adjacentPartNums == 2;
}

int findGearRatio(int lineNum, int linePos) {
    if (!isGear(lineNum, linePos)) return 0;

    int total = 1;

    total *= findPartNumberLeft(lineNum, linePos - 1);
    total *= findPartNumberRight(lineNum, linePos + 1);

    if (lineNum > 0) {
        total *= findPartNumbersVertical(lineNum - 1, linePos);
    }
    if (lineNum < lines.size() - 1) {
        total *= findPartNumbersVertical(lineNum + 1, linePos);
    }

    return total;
}

int checkLine(int lineNum) {
    string line = lines[lineNum];
    int lineTotal = 0;
    size_t linePos = line.find('*');
    while (linePos != string::npos) {
        lineTotal += findGearRatio(lineNum, linePos);
        linePos = line.find('*', linePos + 1);
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