#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
 // THIS IS NOT THE REAL CODE BUT A SAMPLE LIKE IT :) 
using namespace std;

struct Location {
    string name;
    int id;
};

vector<Location> locations = {
    {"CSIT", 0}, {"Girls Common Room", 1}, {"Auditorium", 2},
    {"Admin Block", 3}, {"Bank", 4}, {"Medical Dept", 5},
    {"Library", 6}, {"Engineering Dept", 7}, {"Cafeteria", 8},
    {"Sports Complex", 9}, {"Main Gate", 10}
};

unordered_map<int, vector<pair<int, double>>> adjList = {
    {0, {{1, 2.5}, {2, 3.5}, {3, 4.0}}},
    {1, {{0, 2.5}, {3, 2.0}, {4, 5.5}}},
    {2, {{0, 3.5}, {3, 1.0}, {5, 6.0}}},
    {3, {{0, 4.0}, {1, 2.0}, {2, 1.0}, {5, 3.5}, {6, 4.5}}},
    {4, {{1, 5.5}, {5, 2.0}, {7, 3.5}}},
    {5, {{2, 6.0}, {3, 3.5}, {4, 2.0}, {8, 2.5}}},
    {6, {{3, 4.5}, {9, 2.5}}},
    {7, {{4, 3.5}, {10, 2.0}}},
    {8, {{5, 2.5}, {9, 4.0}}},
    {9, {{6, 2.5}, {8, 4.0}, {10, 5.0}}},
    {10, {{7, 2.0}, {9, 5.0}}}
};

vector<double> dijkstra(int start, int numLocations, vector<int>& previous ) {
    vector<double> distances(numLocations, numeric_limits<double>::infinity());
    distances[start] = 0.0;
    previous[start] = -1;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> minHeap;
    minHeap.push({0.0, start});

    while (!minHeap.empty()) {
        auto top = minHeap.top();
        double currentDistance = top.first;
        int currentLocation = top.second;
        minHeap.pop();

        for (const auto& neighborWeightPair : adjList[currentLocation]) {
            int neighbor = neighborWeightPair.first;
            double weight = neighborWeightPair.second;

            double newDist = currentDistance + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                previous[neighbor] = currentLocation;
                minHeap.push({newDist, neighbor});
            }
        }
    }
    return distances;
}

void printPath(int destination, const vector<int>& previous) {
    if (previous[destination] == -1) {
        cout << "No path found.\n";
        return;
    }

    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); ++i) {
        cout << locations[path[i]].name;
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int numLocations = locations.size();
    vector<int> previous(numLocations);

    int start, end;
    cout << "Enter the starting location ID (0 for CSIT): ";
    cin >> start;
    cout << "Enter the destination location ID (e.g., 5 for Medical Dept): ";
    cin >> end;

    if (start < 0 || start >= numLocations || end < 0 || end >= numLocations) {
        cout << "Invalid location ID entered.\n";
        return 1;
    }

    vector<double> distances = dijkstra(start, numLocations, previous);
    cout << "\nShortest path from " << locations[start].name << " to " << locations[end].name << ":\n";
    printPath(end, previous);
    if (distances[end] != numeric_limits<double>::infinity()) {
        cout << "Distance: " << distances[end] << " units\n";
    } else {
        cout << "Distance: No path available.\n";
    }

    vector<int> returnPrevious(numLocations);
    distances = dijkstra(end, numLocations, returnPrevious);
    cout << "\nReturn path from " << locations[end].name << " back to " << locations[start].name << ":\n";
    printPath(start, returnPrevious);
    if (distances[start] != numeric_limits<double>::infinity()) {
        cout << "Distance: " << distances[start] << " units\n";
    } else {
        cout << "Distance: No path available.\n";
    }

    return 0;
}  
