#include "dijkstras.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
    // Get filename from arguments; default to "./largest.txt"
    string filename = (argc > 1) ? argv[1] : "./small.txt";
    

    Graph G(0);

    // Build the graph from file
    try {
        file_to_graph(filename, G);
    } catch (const std::exception &e) {
        cerr << "Error reading graph: " << e.what() << endl;
        return 1;
    }

    // Define source and destination vertices
    int source = 0;
    int destination = (G.numVertices > 0) ? G.numVertices - 1 : 0;

    // Run Dijkstra's algorithm from the source vertex
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    // Extract the shortest path from source to destination
    vector<int> path = extract_shortest_path(distances, previous, destination);

    // Output the shortest path and its total distance
    cout << "Shortest path from " << source << " to " << destination << " is: ";
    print_path(path, distances[destination]);
    cout << "Total distance = " << distances[destination] << endl;

    return 0;
}
