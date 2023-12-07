#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const int limits[3] = {12, 13, 14};
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

bool checkRound(string round) {
    vector<string> cubeTypes = split(round, ',');
    for (string cubeType : cubeTypes) {
        vector<string> details = split(cubeType, ' ');
        for (int i = 0; i < 3; i++) {
            if (details[2] == colours[i] && stoi(details[1]) > limits[i]) {
                return false;
            }
        }
    }
    return true;
}

int checkGame(string game) {
    int colon = game.find(":");
    string id = game.substr(0, colon);
    string roundsString = game.substr(colon + 1, game.length() - (colon + 1));
    vector<string> rounds = split(roundsString, ';');

    for (string round : rounds) {
        bool possible = checkRound(round);
        if (!possible) return 0;
    }

    return stoi(id.substr(5, id.length() - 5));
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