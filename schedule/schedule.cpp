#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ifstream file("schedulea.txt");
  if (!file) {
    cerr << "Không thể mở file!\n";
    return 1;
  }

  int numJobs, numMachines = 3;
  file >> numJobs;
  vector<int> jobs(numJobs);

  for (int i = 0; i < numJobs; i++) {
    file >> jobs[i];
  }

  file.close();

  // Sắp xếp công việc giảm dần để tối ưu lịch trình
  sort(jobs.rbegin(), jobs.rend());

  // Dùng hàng đợi ưu tiên (min-heap) để theo dõi tải của mỗi máy
  priority_queue<int, vector<int>, greater<int>> machines;

  // Ban đầu, tất cả máy có tải 0
  for (int i = 0; i < numMachines; i++) {
    machines.push(0);
  }

  // Gán công việc vào máy có tải nhỏ nhất hiện tại
  for (int job : jobs) {
    int minLoad = machines.top();
    machines.pop();         // Lấy máy có tải nhỏ nhất
    minLoad += job;         // Thêm công việc vào máy
    machines.push(minLoad); // Đưa máy trở lại hàng đợi
  }

  // Kết quả là tải lớn nhất của một máy
  int maxTime = 0;
  while (!machines.empty()) {
    maxTime = machines.top();
    machines.pop();
  }

  cout << "Thời gian hoàn thành tối ưu: " << maxTime << endl;
  return 0;
}
