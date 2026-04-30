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

const int SIZE = 11;

//function prototype to help with application output
string getCityName(int);

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
        cout << "City Travel Network Topology:" << endl;
        cout << "================================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << getCityName(i) << " connects to:" << endl;
            for (Pair v : adjList[i]) {
                cout << " -> " << getCityName(v.first) << " (Travel Time: " 
                     << v.second << " mins)" << endl;
            }
        }
        cout << endl;
    }

    //Depth-First Search
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);

        cout << "Regional Travel Trace (DFS) from " << getCityName(start) 
             << ":" << endl;
        cout << "Purpose: Tracing long-distance continuous travel routes" << endl;
        cout << "=======================================================" << endl;

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << "Visiting " << getCityName(node) << endl;
                visited[node] = true;
            }
            // Push neighbors to stack
            for (Pair neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    cout << " -> Possible connection to " 
                         << getCityName(neighbor.first) << " - Travel Time: " 
                         << neighbor.second << " mins" << endl;
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

        cout << "Proximity-Based City Inspection (BFS) from " << getCityName(start) 
             << ":" << endl;
        cout << "Purpose: Analyzing nearby cities by travel distance" << endl;
        cout << "===================================================" << endl;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << "Checking " << getCityName(node) << endl;
   
            // Push neighbors to queue
            for (Pair neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    cout << " -> Next closest city: " << getCityName(neighbor.first) 
                         << " - Travel Time: " << neighbor.second << " mins" << endl;
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

//getCityName() returns the city name associated with the passed node
//arguments: an integer for the node of the respective city in the graph
//returns: a string, the city name
string getCityName(int node) {
    string cities[SIZE] = {
        "Berkeley", "Richmond", "Walnut Creek", "Oakland", "Alameda", "Hayward",
        "Concord", "Antioch", "Dublin", "Pleasanton", "Fremont"};
    return cities[node];
}