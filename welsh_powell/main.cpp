
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define FILE "graph2.txt"

using namespace std;

struct Vertex {
    int id, degree;
    Vertex(int i, int d) : id(i), degree(d) {}
    bool operator<(const Vertex& other) const {
        return degree > other.degree; // Sắp xếp giảm dần
    }
};

class Graph {
private:
    int n; // Số đỉnh
    vector<vector<int>> c; // Ma trận kề

public:
    Graph(int size) : n(size), c(size, vector<int>(size, 0)) {}
    void addEdge(int u, int v) {
        c[u][v] = c[v][u] = 1; // Đồ thị vô hướng
    }

    void writeFile(int colorCount, vector<int>& colors) {
        ofstream outFile("result.txt");
        outFile << "Số màu sử dụng: " << colorCount << "\n";
        for (int i = 0; i < n; ++i)
            outFile << "Đỉnh " << i << " có màu " << colors[i] << "\n";
        outFile.close();
    }

    int welshPowell() {
        vector<Vertex> vertices;
        for (int i = 0; i < n; ++i) {
            int degree = count(c[i].begin(), c[i].end(), 1);
            vertices.emplace_back(i, degree);
        }
        stable_sort(vertices.begin(), vertices.end());
        
        vector<int> colors(n, 0);
        int color = 1;
        bool all_colored;
        
        while (true) {
            all_colored = true;
            for (auto& vertex : vertices) {
                if (!colors[vertex.id]) {
                    bool can_color = true;
                    for (int i = 0; i < n; ++i) {
                        if (c[vertex.id][i] && colors[i] == color) {
                            can_color = false;
                            break;
                        }
                    }
                    if (can_color) {
                        colors[vertex.id] = color;
                        all_colored = false;
                    }
                }
            }
            if (all_colored) break;
            ++color;
        }
        writeFile(color - 1, colors);
        return color - 1;
    }
};

int main() {
    int n, m, u, v;
    ifstream inFile(FILE);
    if (!inFile) { 
        cerr << "Không thể mở file " << FILE << endl;
        return 1;
    }
    inFile >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        inFile >> u >> v;
        g.addEdge(u, v);
    }
    inFile.close();
    
    int colors_used = g.welshPowell();
    cout << "Số màu cần thiết: " << colors_used << endl;
    return 0;
}
