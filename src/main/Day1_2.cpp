#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string words[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const string replacedWords[10] = {"zer0o", "on1e", "tw2o", "thre3e", "fou4r", "fiv5e", "si6x", "seve7n", "eigh8t", "nin9e"};

string replaceNumber(string line, string word, string replacement) {
    size_t pos = 0;
    while ((pos = line.find(word, pos)) != string::npos) {
        line.replace(pos, word.length(), replacement);
        pos += replacement.length();
    }
    return line;
}

string processLine(string line) {
    string result = line;
    for (int i = 0; i < 10; i++) {
        result = replaceNumber(result, words[i], replacedWords[i]);
    }
    return result;
}

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
            string replaced = processLine(line);
            total += readLine(replaced);
        }
    } else {
        cout << "Couldn't open input file\n";
    }

    cout << "total: ";
    cout << total;
}