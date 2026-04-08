#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义道路（边）的结构体
struct Edge {
    int u;      // 村庄A的编号
    int v;      // 村庄B的编号
    int weight; // 修建成本

    // 重载小于号 < ，为了让 sort 函数能按成本从小到大对道路进行排序
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// 并查集数组，parent_node[i] 表示村庄 i 的父节点
int parent_node[1005];

// 并查集核心操作 1：查找根节点（带路径压缩优化）
int find(int x) {
    // 如果自己就是根节点，直接返回
    if (parent_node[x] == x) {
        return x;
    }
    // 否则顺藤摸瓜找根节点，并将沿途所有的节点直接连到根节点上（路径压缩）
    return parent_node[x] = find(parent_node[x]);
}

int main() {
    int n, m;
    // 输入：n为村庄数，m为道路数
    if (!(cin >> n >> m)) return 0; 

    // 使用 vector 存储所有的道路信息
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // --- 算法开始 ---

    // 1. 初始化并查集，一开始每个村庄各自独立，父节点是自己
    for (int i = 1; i <= n; ++i) {
        parent_node[i] = i;
    }

    // 2. 将所有道路按成本从低到高排序
    sort(edges.begin(), edges.end());

    int total_cost = 0;  // 记录最低总成本
    int edges_added = 0; // 记录已经修建了多少条路

    // 3. 遍历排序后的道路，尝试修建
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        // 查找村庄 u 和村庄 v 所在集合的根节点
        int root_u = find(u);
        int root_v = find(v);

        // 如果根节点不同，说明它们目前不连通，可以修这条路
        if (root_u != root_v) {
            // 在并查集中合并它们（也就是宣布这两个村庄连通了）
            parent_node[root_u] = root_v; 
            
            total_cost += edges[i].weight; // 累加成本
            edges_added++;                 // 修建道路数 + 1

            // 优化：n个村庄只需要 n-1 条路就能全部连通，达到了就可以提前结束
            if (edges_added == n - 1) {
                break;
            }
        }
    }

    // --- 输出结果 ---
    
    // 如果成功修建了 n-1 条路，说明全部连通了
    if (edges_added == n - 1) {
        cout << total_cost << endl;
    } else {
        // 否则说明给定的道路不足以让所有村庄连通
        cout << -1 << endl;
    }

    return 0;
}