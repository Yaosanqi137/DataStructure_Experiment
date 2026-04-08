#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n;

    // 接收第一行的整数 N
    cin >> n;

    // 定义一个最小堆，用于每次自动找出最小的两个数
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // 接收第二行的 N 个权值
    for (int i = 0; i < n; ++i) {
        int weight;
        cin >> weight;
        minHeap.push(weight); // 将输入的权值直接放入堆中
    }

    int wpl = 0; // 带权路径长度

    // 只要堆里还有2个以上的数字，就继续合并
    while (minHeap.size() > 1) {
        // 拿出最小的数
        int min1 = minHeap.top();
        minHeap.pop();

        // 拿出第二小的数
        int min2 = minHeap.top();
        minHeap.pop();

        int combinedWeight = min1 + min2;

        wpl += combinedWeight;

        // 把合并后的新数字重新放回堆里
        minHeap.push(combinedWeight);
    }

    cout << wpl << endl;

    return 0;
}