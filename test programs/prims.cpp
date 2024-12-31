#include <iostream>
#include <vector>
#include <climits>
#include <queue>  // To use priority_queue

using namespace std;

// Define a pair to represent an edge (weight, node)
typedef pair<int, int> Edge;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<Edge>> adjList;

    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(make_pair(weight, v));
        adjList[v].push_back(make_pair(weight, u));  // Since the graph is undirected
    }

    // Function to perform Prim's algorithm
    void primMST() {
        vector<int> key(V, INT_MAX);   // To store the minimum weight to a vertex
        vector<int> parent(V, -1);      // To store the parent of each vertex
        vector<bool> inMST(V, false);   // To track if the vertex is included in MST

        key[0] = 0; // Start with the first vertex

        // Priority queue to pick the minimum key vertex that is not yet included in MST
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        pq.push(make_pair(0, 0)); // (weight, vertex)

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            // Loop through all adjacent vertices of u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.second;
                int weight = neighbor.first;

                // If the vertex v is not in MST and the weight is smaller than the current key
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        // Output the MST
        printMST(parent);
    }

    // Function to print the constructed MST
    void printMST(const vector<int>& parent) {
        cout << "Edge   Weight\n" << flush;
        for (int i = 1; i < V; ++i) {
            cout << parent[i] << " - " << i << "   " << adjList[i][parent[i]].first << endl << flush;
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges to the graph (undirected graph)
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    // Run Prim's algorithm to find the MST
    g.primMST();

    return 0;
}