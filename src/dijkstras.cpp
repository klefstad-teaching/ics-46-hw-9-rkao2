#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <climits>
#include <algorithm>
#include "dijkstras.h"

using namespace std;



vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;

    vector<int> distance(n, INT_MAX);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;


    while(!pq.empty()){
        int u = pq.top().vertex;
        pq.pop();

        if(visited[u]){
            continue;
        }
        visited[u] = true;

        for(const auto& neighbor : G[u]){
            int v = neighbor.dst;
            int weight = neighbor.weight;
            
             if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}


vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;

    if (previous[destination] == -1) {  
        cout << "No path found to destination " << destination << endl;
        return {};
    }

    for(int v = destination; v != -1; v = previous[v]){
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}   

void print_path(const vector<int>& v, int total){
    /**
    if(v.empty()){
        cout << "No path found. " << endl; 
        return;
    }
    */
    
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";

    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}



