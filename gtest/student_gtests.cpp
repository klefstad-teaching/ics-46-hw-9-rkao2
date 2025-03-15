#include <gtest/gtest.h>

#include "dijkstras.h"
// #include "ladder.h"
#include "ladder.h"
#include <sstream>
#include <iostream>
#include <set>
#include <vector>

// Test case 1: Basic Graph Test
TEST(DijkstraTest, BasicGraph) {
    Graph G(5);
    G[0].push_back(Edge(0, 1, 10));
    G[0].push_back(Edge(0, 2, 3));
    G[1].push_back(Edge(1, 2, 1));
    G[1].push_back(Edge(1, 3, 2));
    G[2].push_back(Edge(2, 1, 4));
    G[2].push_back(Edge(2, 3, 8));
    G[2].push_back(Edge(2, 4, 2));
    G[3].push_back(Edge(3, 4, 7));
    G[4].push_back(Edge(4, 3, 9));

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 7);
    EXPECT_EQ(distances[2], 3);
    EXPECT_EQ(distances[3], 9);
    EXPECT_EQ(distances[4], 5);

    std::vector<int> path = extract_shortest_path(distances, previous, 4);
    std::vector<int> expected_path = {0, 2, 4};
    EXPECT_EQ(path, expected_path);
}

// Test case 2: Single Node Graph
TEST(DijkstraTest, SingleNodeGraph) {
    Graph G(1);

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_TRUE(previous.empty() || previous[0] == -1);
}

// Test case 3: Disconnected Graph
TEST(DijkstraTest, DisconnectedGraph) {
    Graph G(4);
    G[0].push_back(Edge(0, 1, 5));
    G[2].push_back(Edge(2, 3, 10));

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 5);
    EXPECT_EQ(distances[2], INF);
    EXPECT_EQ(distances[3], INF);
}

// Test case 4: Cycle in Graph
TEST(DijkstraTest, GraphWithCycle) {
    Graph G(4);
    G[0].push_back(Edge(0, 1, 1));
    G[1].push_back(Edge(1, 2, 1));
    G[2].push_back(Edge(2, 3, 1));
    G[3].push_back(Edge(3, 0, 1)); // Creates a cycle

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 1);
    EXPECT_EQ(distances[2], 2);
    EXPECT_EQ(distances[3], 3);
}

// Test case 5: Large Graph Performance
TEST(DijkstraTest, LargeGraph) {
    Graph G(1000);
    for (int i = 0; i < 999; i++) {
        G[i].push_back(Edge(i, i + 1, 1));
    }

    std::vector<int> previous;
    std::vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[999], 999);
}



// Helper function to capture output from print_word_ladder
std::string capture_output(const std::vector<std::string>& ladder) {
    std::ostringstream output_stream;
    std::streambuf* original_cout = std::cout.rdbuf();  // Save the original buffer
    std::cout.rdbuf(output_stream.rdbuf());  // Redirect std::cout to output_stream

    print_word_ladder(ladder);  // This will now write to output_stream

    std::cout.rdbuf(original_cout);  // Restore the original buffer
    return output_stream.str();
}

// Helper function to test word ladder output
void assert_word_ladder(const std::vector<std::string>& ladder, const std::string& expected_output) {
    EXPECT_EQ(capture_output(ladder), expected_output);
}

// Test 1: Basic word ladder test with a valid sequence
TEST(WordLadderTest, BasicWordLadder) {
    std::set<std::string> word_list = {"awake", "aware", "ware", "were", "wee", "see", "seep", "sleep"};

    std::string begin_word = "awake";
    std::string end_word = "sleep";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "awake -> aware -> ware -> were -> wee -> see -> seep -> sleep\n");
}

// Test 2: Case with no word ladder (e.g., no transformation possible)
TEST(WordLadderTest, NoWordLadder) {
    std::set<std::string> word_list = {"cat", "bat", "rat", "mat"};
    
    std::string begin_word = "dog";
    std::string end_word = "fish";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "No word ladder found.\n");
}

// Test 3: Case with two adjacent words
TEST(WordLadderTest, TwoAdjacentWords) {
    std::set<std::string> word_list = {"hit", "hot", "dot", "dog", "cog"};

    std::string begin_word = "hit";
    std::string end_word = "hot";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "hit -> hot\n");
}

// Test 4: Case with only one word in the ladder (begin == end)
TEST(WordLadderTest, SameBeginAndEnd) {
    std::set<std::string> word_list = {"cat", "bat", "rat", "mat"};

    std::string begin_word = "cat";
    std::string end_word = "cat";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "cat\n");
}

// Test 5: Large test case with a larger word list
TEST(WordLadderTest, LargeWordList) {
    std::set<std::string> word_list = {
        "cat", "bat", "rat", "mat", "hat", "hot", "dot", "dog", "cog", "log", "fog"
    };

    std::string begin_word = "cat";
    std::string end_word = "fog";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "cat -> bat -> rat -> mat -> hat -> hot -> dot -> dog -> log -> fog\n");
}

// Test 6: Test for a large word ladder with a longer sequence
TEST(WordLadderTest, LongWordLadder) {
    std::set<std::string> word_list = {"tap", "map", "mad", "pad", "bad", "bat", "rat", "mat"};

    std::string begin_word = "tap";
    std::string end_word = "mat";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "tap -> map -> mad -> pad -> bad -> bat -> rat -> mat\n");
}

// Test 7: Edge case - empty word list
TEST(WordLadderTest, EmptyWordList) {
    std::set<std::string> word_list = {};
    
    std::string begin_word = "start";
    std::string end_word = "end";
    
    std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    assert_word_ladder(ladder, "No word ladder found.\n");
}


void create_test_file(const std::string& file_name, const std::vector<std::string>& words) {
    std::ofstream file(file_name);
    for (const std::string& word : words) {
        file << word << std::endl;
    }
}


TEST(LoadWordsTest, CorrectlyLoadsWords) {
    // Prepare a test file with some words
    std::string test_file = "test_file.txt";
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    create_test_file(test_file, words);

    std::set<std::string> word_list;
    load_words(word_list, test_file);

    // Verify the set contains the correct words
    ASSERT_EQ(word_list.size(), words.size());
    for (const auto& word : words) {
        ASSERT_TRUE(word_list.find(word) != word_list.end());
    }

    // Clean up test file
    std::remove(test_file.c_str());
}


TEST(WordLadderTest, IsAdjacentTest) { // passed
    // Test case 1: Same length, one character difference
    EXPECT_TRUE(is_adjacent("apple", "appl"));  // Should return true

    // Test case 2: Same length, one character difference
    EXPECT_TRUE(is_adjacent("appl", "apple"));  // Should return true

    // Test case 3: Same length, one character difference
    EXPECT_TRUE(is_adjacent("zoom", "zoo"));    // Should return true

    // Test case 4: Same length, no character difference
    EXPECT_FALSE(is_adjacent("hello", "hello"));  // Should return false (no difference)

    // Test case 5: Different length by 1 character (insertion or deletion)
    EXPECT_TRUE(is_adjacent("hello", "hell"));   // Should return true (insertion/deletion)

    // Test case 6: One character difference and different length
    EXPECT_FALSE(is_adjacent("hello", "helloo"));  // Should return false (difference more than one character)

    // Test case 7: More than 1 character difference
    EXPECT_FALSE(is_adjacent("apple", "banana"));  // Should return false (more than one character difference)
}


TEST(PrintWordLadderTest, NonEmptyLadder) {
    vector<string> ladder = {"awake", "aware", "ware", "were", "wee", "see", "seep", "sleep"};
    
    stringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());  // Redirect cout to the stringstream
    
    print_word_ladder(ladder);  // Call the function
    
    cout.rdbuf(old_buf);  // Restore original cout
    
    // Verify the output
    string expected_output = "awake aware ware were wee see seep sleep \n";
    EXPECT_EQ(output.str(), expected_output);
}

// Test 2: Check if the correct message is printed when the ladder is empty
TEST(PrintWordLadderTest, EmptyLadder) {
    vector<string> ladder;
    
    stringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf());  // Redirect cout to the stringstream
    
    print_word_ladder(ladder);  // Call the function
    
    cout.rdbuf(old_buf);  // Restore original cout
    
    // Verify the output
    string expected_output = "No word ladder found.\n";
    EXPECT_EQ(output.str(), expected_output);
}



class PrintPathTest : public ::testing::Test {
protected:
    std::ostringstream outputBuffer;
    std::streambuf* oldCout;  // Store old cout buffer

    void SetUp() override {
        oldCout = std::cout.rdbuf(outputBuffer.rdbuf());  // Redirect cout
    }

    void TearDown() override {
        std::cout.rdbuf(oldCout);  // Restore cout
    }
};


TEST_F(PrintPathTest, ValidPath) {
    std::vector<int> path = {1, 3, 5, 7};  
    int totalCost = 12;

    print_path(path, totalCost);

    std::string expectedOutput = "1 3 5 7 \nTotal cost is 12\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);  
}


TEST_F(PrintPathTest, SingleNodePath) {
    std::vector<int> path = {2};  
    int totalCost = 0;

    print_path(path, totalCost);

    std::string expectedOutput = "2 \nTotal cost is 0\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);  
}


TEST_F(PrintPathTest, NoPath) {
    std::vector<int> path = {};  
    int totalCost = -1;

    print_path(path, totalCost);

    std::string expectedOutput = "No path found. \n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);  
}

TEST_F(PrintPathTest, PathFound) {
    std::vector<int> path = {1, 2, 3, 4};  // Sample path
    int totalCost = 8;

    print_path(path, totalCost);

    // Expected output
    std::string expectedOutput = "1 2 3 4 \nTotal cost is 8\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);
}

// Test 2: No Path Found - Expect "No path found."
TEST_F(PrintPathTest, NoPathFound) {
    std::vector<int> path = {};  // Empty path indicating no path found
    int totalCost = INT_MAX;  // Total cost should not matter in this case

    print_path(path, totalCost);

    // Expected output
    std::string expectedOutput = "No path found. \n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);
}