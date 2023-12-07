#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

vector<string> split(string s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

int checkCard(string card) {
    int colon = card.find(":");
    string cardNums = card.substr(colon + 1, card.length() - (colon + 1));

    int line = cardNums.find("|");
    string winningNumsString = cardNums.substr(1, line - 2);
    string yourNumsString = cardNums.substr(line + 2, cardNums.length() - (line + 2));

    vector<string> winningNums = split(winningNumsString, ' ');
    vector<string> yourNums = split(yourNumsString, ' ');

    int points = 0;
    for (string num : winningNums) {
        if (num.length() > 0 && find(yourNums.begin(), yourNums.end(), num) != yourNums.end()) {
            if (points == 0) {
                points = 1;
            } else {
                points *= 2;
            }
        }
    }
    
    return points;
}

int main() {
    fstream input;
    
    input.open("C:/Users/matth/Documents/GitHub/advent-of-code-2023/data/Day4.txt", iostream::in);

    int total = 0;

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            total += checkCard(line);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    cout << "total: ";
    cout << total;
}