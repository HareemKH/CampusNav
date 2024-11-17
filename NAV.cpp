#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <list>
#include <stack>

using namespace std;

struct Edge {
    string destination;
    int weight;
};

struct Node {
    string name;
    int distance;

    bool operator>(const Node &other) const {
        return distance > other.distance;
    }
};

void dijkstra(unordered_map<string, list<Edge>> &graph, const string &start, const string &destination) {

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    unordered_map<string, int> distances;

    unordered_map<string, string> previous;

    // Initialize distances to "infinity" and set the start node to 0 distance
    for (const auto &node : graph) {
        distances[node.first] = INT_MAX;
    }
    distances[start] = 0;

    pq.push({start, 0});

    // Dijkstra's algorithm
    while (!pq.empty()) {
        string current = pq.top().name;
        int currentDistance = pq.top().distance;
        pq.pop();

        if (currentDistance > distances[current]) continue;

        // Explore neighbors of the current node
        for (const auto &neighbor : graph[current]) {
            string adjNode = neighbor.destination;
            int weight = neighbor.weight;
            int newDist = currentDistance + weight;

            if (newDist < distances[adjNode]) {
                distances[adjNode] = newDist;
                previous[adjNode] = current;
                pq.push({adjNode, newDist});
            }
        }
    }

    // Check if destination is reachable
    if (distances[destination] == INT_MAX) {
        cout << "No valid path found from " << start << " to " << destination << "." << endl;
        return;
    }

    cout << "Shortest distance from " << start << " to " << destination << " is: " << distances[destination] << endl;

    // Reconstruct the shortest path
    stack<string> pathStack;
    string node = destination;

    while (node != start) {
        pathStack.push(node);
        node = previous[node];
    }
    pathStack.push(start);

    // Print the path in correct order
    cout << "Shortest path: ";
    while (!pathStack.empty()) {
        cout << pathStack.top();
        pathStack.pop();
        if (!pathStack.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    unordered_map<string,  list<Edge>> graph;

    // Define locations and distances based on map layout
    graph["CSIT"].push_back({"Courtyard", 1});
    graph["Courtyard"].push_back({"Circulation Library", 2});
    graph["Circulation Library"].push_back({"Masjid", 1});
    graph["CSIT"].push_back({"Math Building", 1});
    graph["Math Building"].push_back({"Admin Block", 2});
    graph["Admin Block"].push_back({"Masjid", 3});
    graph["Admin Block"].push_back({"Humanities", 1});

    // Adding more connections for accurate campus layout
    graph["CSIT"].push_back({"Auditorium", 2});
    graph["Auditorium"].push_back({"Medical Dept", 3});
    graph["Medical Dept"].push_back({"Masjid", 1});

    // Ensure bidirectional paths
    for (auto &node : graph) {
        for (auto &edge : node.second) {
            graph[edge.destination].push_back({node.first, edge.weight});
        }
    }

    // Take user input for destination selection
    cout << "Enter the destination from the following list:\n";
    cout << "1. Math Building\n";
    cout << "2. Courtyard\n";
    cout << "3. Circulation Library\n";
    cout << "4. Admin Block\n";
    cout << "5. Auditorium\n";
    cout << "6. Medical Dept\n";
    cout << "7. Masjid\n";
    
    int option;
    cout << "Enter your destination number: ";
    cin >> option;

    string destination;
    switch (option) {
        case 1: destination = "Math Building"; break;
        case 2: destination = "Courtyard"; break;
        case 3: destination = "Circulation Library"; break;
        case 4: destination = "Admin Block"; break;
        case 5: destination = "Auditorium"; break;
        case 6: destination = "Medical Dept"; break;
        case 7: destination = "Masjid"; break;
        default: 
            cout << "Invalid option selected. Exiting.";
            return 0;
    }

    dijkstra(graph, "CSIT", destination);

    return 0;
}
