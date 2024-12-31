#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to perform BFS traversal on the graph
void bfs(int startNode, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " " << flush;  // Visit the node (print it)

        // Traverse all adjacent nodes
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int vertices, edges;
    
    // Take input for number of vertices and edges
    cout << "Enter number of vertices: " << flush;
    cin >> vertices;
    cout << "Enter number of edges: " << flush;
    cin >> edges;

    // Create an adjacency list for the graph
    vector<vector<int>> graph(vertices);

    cout << "Enter the edges (u v format):" << flush << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);  // Add v to u's list
        graph[v].push_back(u);  // Add u to v's list (for undirected graph)
    }

    // Create a visited array to keep track of visited nodes
    vector<bool> visited(vertices, false);

    // Perform BFS starting from node 0 (or any other node)
    cout << "BFS traversal starting from node 0: " << flush;
    bfs(0, graph, visited);
    cout << endl;

    return 0;
}