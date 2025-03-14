
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
    if(str1.length() != str2.length()) return false;

    int count = 0;
    for(size_t i = 0; i < str1.length(); i++){
        if(str1[i] != str2[i]) count++;
        if(count > d) return false;
    }
    return count <= d;

}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);

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

        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if(word == end_word){
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
            }
        }
    

    }
return {};

}


void load_words(set<string> & word_list, const string& file_name){
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
        if(i != ladder.size() - 1) cout << " -> ";
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
