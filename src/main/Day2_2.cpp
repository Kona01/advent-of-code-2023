#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

const int intMax = numeric_limits<int>::max();
const string colours[3] = {"red", "green", "blue"};

vector<string> split(string s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

vector<int> checkRound(string round) {
    vector<string> cubeTypes = split(round, ',');
    vector<int> results = {0, 0, 0};
    for (string cubeType : cubeTypes) {
        vector<string> details = split(cubeType, ' ');
        for (int i = 0; i < 3; i++) {
            if (details[2] == colours[i]) {
                results[i] = stoi(details[1]);
            }
        }
    }
    return results;
}

int checkGame(string game) {
    int colon = game.find(":");
    string roundsString = game.substr(colon + 1, game.length() - (colon + 1));
    vector<string> rounds = split(roundsString, ';');

    int minimums[3] = {0, 0, 0};

    for (string round : rounds) {
        vector<int> roundMinimums = checkRound(round);
        for (int i = 0; i < 3; i++) {
            if (roundMinimums[i] > minimums[i]) minimums[i] = roundMinimums[i];
        }
    }

    return minimums[0] * minimums[1] * minimums[2];
}

int main() {
    fstream input;
    
    input.open("C:/Users/matth/Documents/GitHub/advent-of-code-2023/data/Day2.txt", iostream::in);

    int total = 0;

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            total += checkGame(line);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    cout << "total: ";
    cout << total;
}