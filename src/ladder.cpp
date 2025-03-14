
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

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    // Allow for one character difference in length
    if (abs(int(str1.length()) - int(str2.length())) > 1) return false; // More than one character difference in length is not allowed

    int count = 0;
    size_t i = 0, j = 0;

    while (i < str1.length() && j < str2.length()) {
        if (str1[i] != str2[j]) {
            count++;
            if (count > d) return false;
            
            // If lengths are different, try to align words by skipping a character
            if (str1.length() > str2.length()) {
                i++; // Skip one character in str1
            } else if (str1.length() < str2.length()) {
                j++; // Skip one character in str2
            } else {
                i++; // Otherwise, move both pointers
                j++;
            }
        } else {
            i++;
            j++;
        }
    }

    // Account for remaining characters if the strings are of different lengths
    count += (i < str1.length()) + (j < str2.length());

    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1); // Words can differ by one insertion/deletion or substitution
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        cout << "current ladder: ";
        for (const string& word : ladder) {
            cout << word << " ";
        }
        cout << endl;

        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                cout << "Pushing new ladder: ";
                for (const string& word : new_ladder) {
                    cout << word << " ";
                }
                cout << endl;


                if(word == end_word){
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    

    }
return {};

}


void load_words(set<string> & word_list, const string& file_name){ // working?
    ifstream file(file_name);
    string word;
    while(file >> word){
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    for(size_t i = 0; i < ladder.size(); i++){
        cout << ladder[i];
        if(i != ladder.size() - 1) cout << " "; // if it's not the end, put a space between the words
    }
    cout << endl;
}

void test_word_ladder(const string& word_file, const string& test_file) {
    set<string> word_list;
    load_words(word_list, word_file);  // Load word list from the given file

    ifstream test_file_stream(test_file);
    if (!test_file_stream) {
        cerr << "Error: Could not open test file!" << endl;
        return;
    }

    string begin_word, end_word;
    while (test_file_stream >> begin_word >> end_word) {
        cout << "Processing test case: Begin word = " << begin_word << ", End word = " << end_word << endl;

        vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
        print_word_ladder(ladder);
    }
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "small.txt");

    string begin_word, end_word;
    cout << "Enter begin word: ";
    cin >> begin_word;
    cout << "Enter end word: ";
    cin >> end_word;

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}
