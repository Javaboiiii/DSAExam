// 42.	Write a program to detect a cycle in an undirected graph using DFS.

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int V;                      // Number of vertices
    vector<list<int>> adj;      // Adjacency list representation

public:
    // Constructor
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Function to add an edge to the graph (undirected)
    void addEdge(int v, int w) {
        adj[v].push_back(w);    // Add w to v's list
        adj[w].push_back(v);    // Add v to w's list (since it's undirected)
    }

    // Helper function for cycle detection using DFS
    bool isCyclicUtil(int v, vector<bool>& visited, int parent) {
        // Mark the current node as visited
        visited[v] = true;

        // Recur for all the adjacent vertices
        for (auto i = adj[v].begin(); i != adj[v].end(); i++) {
            // If an adjacent is not visited, then recur for that adjacent
            if (!visited[*i]) {
                if (isCyclicUtil(*i, visited, v))
                    return true;
            }
            // If an adjacent is visited and not the parent of the current vertex,
            // then there is a cycle
            else if (*i != parent)
                return true;
        }
        return false;
    }

    // Function to detect cycle in an undirected graph
    bool isCyclic() {
        // Initialize all vertices as not visited
        vector<bool> visited(V, false);

        // Call the recursive helper function to detect cycle in different
        // disconnected components of the graph
        for (int u = 0; u < V; u++) {
            // Don't recur for u if it is already visited
            if (!visited[u]) {
                if (isCyclicUtil(u, visited, -1))
                    return true;
            }
        }
        return false;
    }

    // Function to display the adjacency list
    void displayGraph() {
        cout << "Graph Adjacency List:" << endl;
        for (int v = 0; v < V; v++) {
            cout << v << " -> ";
            for (auto x : adj[v]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "=== Cycle Detection in Undirected Graph using DFS ===" << endl;

    // Get number of vertices and edges
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    // Create graph with V vertices
    Graph g(V);

    // Add edges to the graph
    cout << "Enter " << E << " edges (format: u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;
        
        // Validate input
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertices! Vertices should be between 0 and " << V - 1 << endl;
            i--; // Retry this edge
            continue;
        }
        
        g.addEdge(u, v);
    }

    // Display the graph
    g.displayGraph();

    // Check if the graph contains a cycle
    if (g.isCyclic())
        cout << "Graph contains cycle" << endl;
    else
        cout << "Graph doesn't contain cycle" << endl;

    // Predefined test cases for quick testing
    cout << "\n=== Predefined Test Cases ===" << endl;
    
    // Test Case 1: Contains a cycle (0-1-2-0)
    cout << "\nTest Case 1:" << endl;
    Graph g1(3);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.displayGraph();
    cout << "Expected: Graph contains cycle" << endl;
    cout << "Result: " << (g1.isCyclic() ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
    
    // Test Case 2: No cycle (0-1-2)
    cout << "\nTest Case 2:" << endl;
    Graph g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.displayGraph();
    cout << "Expected: Graph doesn't contain cycle" << endl;
    cout << "Result: " << (g2.isCyclic() ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;
    
    // Test Case 3: Disconnected graph with a cycle
    cout << "\nTest Case 3 (Disconnected graph with cycle):" << endl;
    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(3, 4);
    g3.addEdge(4, 3); // Self loop
    g3.displayGraph();
    cout << "Expected: Graph contains cycle" << endl;
    cout << "Result: " << (g3.isCyclic() ? "Graph contains cycle" : "Graph doesn't contain cycle") << endl;

    return 0;
}