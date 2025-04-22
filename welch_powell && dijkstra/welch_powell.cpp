#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define FILE "color4.txt"

using namespace std;

// Hàm đọc ma trận kề từ file
vector<vector<int>> readAdjacencyMatrix(const string &filename, int &n) {
  ifstream file(filename);
  if (!file) {
    cerr << "Không thể mở file!" << endl;
    exit(1);
  }

  file >> n;
  vector<vector<int>> adjMatrix(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      file >> adjMatrix[i][j];
    }
  }
  file.close();
  return adjMatrix;
}

// Hàm thực hiện thuật toán Welch-Powell
vector<int> welchPowellColoring(const vector<vector<int>> &adjMatrix, int n) {
  vector<int> degree(n, 0);
  vector<int> colors(n, -1);
  vector<int> vertices(n);

  // Tính bậc của từng đỉnh
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adjMatrix[i][j] == 1)
        degree[i]++;
    }
    vertices[i] = i;
  }

  // Sắp xếp đỉnh theo bậc giảm dần
  sort(vertices.begin(), vertices.end(),
       [&](int a, int b) { return degree[a] > degree[b]; });

  int color = 0;
  for (int i = 0; i < n; i++) {
    int v = vertices[i];
    if (colors[v] == -1) { // Nếu đỉnh chưa được tô màu
      colors[v] = color;
      for (int j = i + 1; j < n; j++) {
        int u = vertices[j];
        bool canColor = true;
        for (int k = 0; k < n; k++) {
          if (adjMatrix[u][k] == 1 && colors[k] == color) {
            canColor = false;
            break;
          }
        }
        if (canColor) {
          colors[u] = color;
        }
      }
      color++;
    }
  }
  return colors;
}

int main() {
  int n;
  vector<vector<int>> adjMatrix = readAdjacencyMatrix(FILE, n);
  vector<int> colors = welchPowellColoring(adjMatrix, n);

  int totalColors = *max_element(colors.begin(), colors.end()) +
                    1; // Tìm số màu lớn nhất được sử dụng
  cout << "Tổng chi phí tô màu (số màu sử dụng): " << totalColors << endl;

  return 0;
}
