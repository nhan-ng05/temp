#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm> // cần cho reverse

using namespace std;

const int INF = INT_MAX;

void dijkstra(const vector<vector<int>>& graph, int start, vector<int>& dist, vector<int>& parent) {
    int n = graph.size();
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();
        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                int new_dist = dist[u] + graph[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    parent[v] = u;
                    pq.push(make_pair(new_dist, v));
                }
            }
        }
    }
}

vector<int> reconstruct_path(int u, const vector<int>& parent) {
    vector<int> path;
    for (; u != -1; u = parent[u])
        path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ifstream file("color1.txt");
    if (!file.is_open()) {
        cerr << "Không thể mở file!" << endl;
        return 1;
    }

    int n;
    file >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> graph[i][j];

    file.close();

    int start = 0;
    vector<int> dist, parent;
    dijkstra(graph, start, dist, parent);

    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << "Không có đường đi từ " << start << " đến " << i << endl;
        } else {
            cout << "Đường đi ngắn nhất từ " << start << " đến " << i << " (chi phí: " << dist[i] << "): ";
            vector<int> path = reconstruct_path(i, parent);
            for (int v : path) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
