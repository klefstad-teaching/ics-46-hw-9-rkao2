#include <gtest/gtest.h>

#include "dijkstras.h"
// #include "ladder.h"


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
