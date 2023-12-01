#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

vector<string> loadWordList(string fileName) {
    vector<string> wordVect;
    ifstream file;
    int index = 0;

    file.open(fileName); //open file for reading (not for writing)

    if (!file.is_open()) {
        cout << "ERROR: Could not open " << fileName << " - please ensure this file is in the directory.\n";
        wordVect.push_back("ERROR");
        return wordVect;
    }

    while (file) {
        string word;
        file >> word;
        wordVect.push_back(word);
    }

    // cout << "Finished loading " << fileName << endl;
    
    return wordVect;
}

int main() {

    vector<string> a = loadWordList("wordle-solutions.txt");
    vector<string> b = loadWordList("legal-words.txt");

    cout << "solutionList size is: " << a.size() << endl;
    cout << "legalList size is: " << b.size() << endl;

    // vector<int> a = {1, 6};
    // vector<int> b = {6, 5, 3, 1, 9, 2};
 
    bool checker = true;
    for (auto a_elt: a) {
        if (std::find(b.begin(), b.end(), a_elt) == b.end()) {
            checker = false;
        }
    }

    if (checker) {
        cout << "All of vector a's elements are in b\n";
    } else {
        cout << "Not all of vector a is in vector b\n";
    }
}