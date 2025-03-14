#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"


using namespace std;

int main() {
    // Option 1: Load words from a file.
    // set<string> word_list;
    // load_words(word_list, "words.txt");

    // Option 2: Use a manually defined word list.
    cout << "testing" << endl;

    string word_file = "./words.txt";  // Modify this filename if needed
    string test_file = "./small.txt";  // Modify this filename if needed

    cout << "Running automated test cases..." << endl;
    test_word_ladder(word_file, test_file);

    cout << "\nNow testing user input..." << endl;
    verify_word_ladder();

    return 0;
}