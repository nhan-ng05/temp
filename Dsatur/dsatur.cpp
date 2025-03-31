#include <algorithm>
#include <fstream>
/*#include <iomanip>*/
#include <iostream>
#include <set>
#include <vector>
#define OUTPUT_FILE "color4_dsatur.out"
#define FILE1 "color1.txt"
#define FILE2 "color2.txt"
#define FILE3 "color3.txt"
#define FILE4 "color4.txt"

using namespace std;

class Solution {
private:
  int n;                 // Số đỉnh của đồ thị
  vector<vector<int>> c; // Ma trận kề của đồ thị

  // Đọc dữ liệu từ file
  void readFile() {
    ifstream read_file_input(FILE3);
    read_file_input >> this->n;
    this->c.resize(this->n, vector<int>(n));
    for (int i = 0; i < this->n; i++) {
      for (int j = 0; j < this->n; j++) {
        read_file_input >> this->c[i][j];
      }
    }
    read_file_input.close();
  }

  // Ghi kết quả tô màu vào file
  void writeFile(const int &result, const vector<int> &color) {
    // truncate = xoá toàn bộ trước khi ghi lại
    fstream out_file(OUTPUT_FILE, ios::out | ios::trunc);
    out_file << "Màu nhỏ nhất cần tô: " << result << endl;
    for (int i = 0; i < n; i++) {
      out_file << "Đỉnh " << i << " -> Màu " << color[i] << endl;
    }
    out_file.close();
  }

  // Cấu trúc dữ liệu lưu thông tin về mỗi đỉnh
  struct Vertex {
    int id, degree, satur;  // ID, bậc, bậc bão hòa
    set<int> banned_colors; // Danh sách màu không thể sử dụng

    Vertex(const int &id, const int &degree) {
      this->id = id;
      this->degree = degree;
      this->satur = 0;
    }
  };

public:
  Solution() { readFile(); }

  // Kiểm tra xem tất cả các đỉnh đã được tô màu hay chưa
  bool allVerticesColored(const vector<int> &colors) const {
    return all_of(colors.begin(), colors.end(), [](int c) { return c != 0; });
  }

  // Tìm màu nhỏ nhất có thể sử dụng cho một đỉnh
  int minimumPossibleColor(set<int> &banned_colors) {
    int color = 1;
    while (banned_colors.count(color)) {
      color++;
    }
    return color;
  }

  // Thuật toán DSATUR
  int dsatur() {
    vector<Vertex> vertices;
    // Tính bậc của từng đỉnh
    for (int i = 0; i < this->n; i++) {
      int degree = count(c[i].begin(), c[i].end(), 1);
      vertices.push_back(Vertex(i, degree));
    }
    vector<int> colors(n, 0); // Mảng lưu màu của từng đỉnh

    int max_color = 0;
    while (!allVerticesColored(colors)) {
      // Chọn đỉnh có bậc bão hòa lớn nhất, nếu bằng nhau thì chọn bậc lớn nhất
      int max_satur = -1, max_degree = -1, vertex_id = -1;
      for (int i = 0; i < this->n; i++) {
        if (colors[vertices[i].id] == 0) {
          if (vertices[i].satur > max_satur ||
              (vertices[i].satur == max_satur &&
               vertices[i].degree > max_degree)) {
            max_satur = vertices[i].satur;
            max_degree = vertices[i].degree;
            vertex_id = vertices[i].id;
          }
        }
      }

      // Gán màu nhỏ nhất có thể cho đỉnh được chọn
      int color = minimumPossibleColor(vertices[vertex_id].banned_colors);
      colors[vertex_id] = color;
      max_color = max(max_color, color);

      // Cập nhật bậc bão hòa của các đỉnh kề
      for (int i = 0; i < this->n; i++) {
        if (c[vertex_id][i] == 1 && colors[i] == 0) {
          vertices[i].banned_colors.insert(color);
          vertices[i].satur = vertices[i].banned_colors.size();
        }
      }
    }

    // Ghi kết quả ra file
    writeFile(max_color, colors);
    return max_color;
  }
};

int main() {
  Solution solution;
  cout << "Màu nhỏ nhất cần tô: " << solution.dsatur() << endl;
  return 0;
}
