#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int index, a, b;
};

bool compareN1(const Task &t1, const Task &t2) {
    return t1.a < t2.a;
}

bool compareN2(const Task &t1, const Task &t2) {
    return t1.b > t2.b;
}

int main() {
    ifstream input("Johnsona.txt");
    if (!input) {
        cerr << "không thể mở file!" << endl;
        return 1;
    }
    
    int n;
    input >> n;
    vector<Task> N1, N2;
    vector<int> order;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) input >> a[i];
    for (int i = 0; i < n; i++) input >> b[i];
    
    for (int i = 0; i < n; i++) {
        Task t = {i, a[i], b[i]};
        if (a[i] <= b[i]) N1.push_back(t);
        else N2.push_back(t);
    }
    
    sort(N1.begin(), N1.end(), compareN1);
    sort(N2.begin(), N2.end(), compareN2);
    
    for (auto &t : N1) order.push_back(t.index);
    for (auto &t : N2) order.push_back(t.index);
    
    int timeA = 0, timeB = 0;
    for (int i : order) {
        timeA += a[i];
        timeB = max(timeA, timeB) + b[i];
    }
    
    cout << "output: " << timeB << endl;
    return 0;
}
