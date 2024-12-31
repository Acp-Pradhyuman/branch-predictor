#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>  // For reverse

using namespace std;

// Function to perform DFS traversal on the graph using a stack
void dfs(int startNode, vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(startNode);
    visited[startNode] = true;

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        cout << node << " " << flush;  // Visit the node (print it) with flush

        // Traverse all adjacent nodes in reverse order
        // Reverse the neighbors before pushing to the stack
        for (int i = graph[node].size() - 1; i >= 0; i--) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
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

    // Perform DFS starting from node 0 (or any other node)
    cout << "DFS traversal starting from node 0: " << flush;
    dfs(0, graph, visited);
    cout << endl;

    return 0;
}