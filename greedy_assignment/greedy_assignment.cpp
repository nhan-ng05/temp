#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

int greedyAssignment(vector<vector<int>> &costMatrix, int n) {
  vector<bool> assigned(n, false); // Đánh dấu công việc đã được gán
  int totalCost = 0;

  for (int i = 0; i < n; i++) { // Duyệt từng thợ
    int minCost = INT_MAX;
    int jobIndex = -1;

    for (int j = 0; j < n; j++) { // Tìm công việc có chi phí thấp nhất chưa gán
      if (!assigned[j] && costMatrix[i][j] < minCost) {
        minCost = costMatrix[i][j];
        jobIndex = j;
      }
    }

    if (jobIndex != -1) {
      assigned[jobIndex] = true; // Đánh dấu công việc đã gán
      totalCost += minCost;
    }
  }
  return totalCost;
}

int main() {
  ifstream file("assignmenta.txt");
  if (!file) {
    cerr << "Không thể mở file!\n";
    return 1;
  }

  int n;
  file >> n;
  vector<vector<int>> costMatrix(n, vector<int>(n));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      file >> costMatrix[i][j];

  file.close();

  int minCost = greedyAssignment(costMatrix, n);
  cout << "Tổng chi phí phân công: " << minCost << endl;

  return 0;
}
