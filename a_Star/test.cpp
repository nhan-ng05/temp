#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

#define FILE4 "graph2.txt"

using namespace std;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int vertex;
    int f_score;
    bool operator>(const Node &other) const { return f_score > other.f_score; }
};

// A* Algorithm
int a_star(int start, int goal, const unordered_map<int, vector<Edge>> &graph, const vector<int> &heuristic) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    unordered_map<int, int> g_score;
    unordered_map<int, int> f_score;

    for (const auto &pair : graph) {
        g_score[pair.first] = numeric_limits<int>::max();
        f_score[pair.first] = numeric_limits<int>::max();
    }

    g_score[start] = 0;
    f_score[start] = heuristic[start];
    openSet.push({start, f_score[start]});

    while (!openSet.empty()) {
        int current = openSet.top().vertex;
        openSet.pop();

        if (current == goal) {
            return g_score[goal];
        }

        if (graph.find(current) == graph.end()) continue;  // Tránh lỗi truy cập

        for (const Edge &edge : graph.at(current)) {
            int neighbor = edge.to;
            int tentative_g_score = g_score[current] + edge.weight;

            if (tentative_g_score < g_score[neighbor]) {
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + heuristic[neighbor];
                openSet.push({neighbor, f_score[neighbor]});
            }
        }
    }

    return -1; // Không tìm thấy đường đi
}

// Read Graph from File
void read_graph_from_file(const string &filename, int &start, int &goal, unordered_map<int, vector<Edge>> &graph, vector<int> &heuristic) {
    ifstream file(filename);
    if (!file) {
        cerr << "Không thể mở file!\n";
        exit(1);
    }

    int V, E;
    file >> V >> E;
    file >> start >> goal;

    graph.clear();
    heuristic.assign(V, 0);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        file >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for (int i = 0; i < V; i++) {
        file >> heuristic[i];
    }

    file.close();
}

int main() {
    string filename = FILE4;
    int start, goal;
    unordered_map<int, vector<Edge>> graph;
    vector<int> heuristic;

    read_graph_from_file(filename, start, goal, graph, heuristic);

    int min_cost = a_star(start, goal, graph, heuristic);

    if (min_cost != -1) {
        cout << "Chi phí thấp nhất từ " << start << " đến " << goal << " là: " << min_cost << endl;
    } else {
        cout << "Không tìm thấy đường đi!\n";
    }

    return 0;
}
