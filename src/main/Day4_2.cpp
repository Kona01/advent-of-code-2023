#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

vector<string> cards;
int cardCount[197] = {1};

vector<string> split(string s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

void checkCard(int cardNum) {
    string card = cards[cardNum];
    int colon = card.find(":");
    string cardNums = card.substr(colon + 1, card.length() - (colon + 1));

    int line = cardNums.find("|");
    string winningNumsString = cardNums.substr(1, line - 2);
    string yourNumsString = cardNums.substr(line + 2, cardNums.length() - (line + 2));

    vector<string> winningNums = split(winningNumsString, ' ');
    vector<string> yourNums = split(yourNumsString, ' ');

    int matches = 0;
    for (string num : winningNums) {
        if (num.length() > 0 && find(yourNums.begin(), yourNums.end(), num) != yourNums.end()) {
            matches++;
        }
    }

    for (int i = cardNum + 1; matches > 0; i++, matches--) {
        cardCount[i] = cardCount[i] + cardCount[cardNum];
    }
}

int main() {
    fstream input;
    
    input.open("C:/Users/matth/Documents/GitHub/advent-of-code-2023/data/Day4.txt", iostream::in);

    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            cards.push_back(line);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    fill_n(cardCount, cards.size(), 1);

    for (int i = 0; i < cards.size(); i++) {
        checkCard(i);
    }

    int total = 0;
    for (int count : cardCount) {
        total += count;
    }

    cout << "total: ";
    cout << total;
}