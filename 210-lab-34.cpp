//*****************************************************************************
// COMSC-210 | Lab 34 | Gabriel Marquez
// Description: this program shows the capabilities of a graph data structure 
// with the help of an LLM.
//*****************************************************************************

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 11; //changing for Step 2

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    //Depth-First Search
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);

        cout << "DFS starting from vertex " << start << ":" << endl;
        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }
            // Push neighbors to stack
            for (Pair neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                        s.push(neighbor.first);
                }
            }  
        }
        cout << endl;
    }

    //Breadth-First Search
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

                
            // Push neighbors to queue
            for (Pair neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        //changed values for Step 2
        {0,1,8},{0,2,12},{0,3,9},{1,6,10},{2,6,4},
        {2,5,6},{3,4,3},{3,5,7},{4,5,10},{4,8,3},
        {5,6,7},{5,7,8},{5,8,9},{6,7,14},{8,9,5},{8,10,4}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    //output DFS & BFS
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}