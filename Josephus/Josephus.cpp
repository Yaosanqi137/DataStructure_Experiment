#include <iostream>
using namespace std;

class JosephusRing {
public:
    // 初始化并构建循环链表
    JosephusRing(int n) {
        if (n <= 0) {
            head = nullptr;
            size = 0;
            return;
        }

        size = n;
        head = new Node(1);
        Node* prev = head;

        for (int i = 2; i <= n; ++i) {
            prev->next = new Node(i);
            prev = prev->next;
        }
        prev->next = head; // 尾节点连回头节点，闭合成环
    }

    // 从编号 k 开始，报数 m 的人出列
    void play(int k, int m) {
        if (head == nullptr || k <= 0 || m <= 0 || k > size) {
            cout << "参数不合法！" << endl;
            return;
        }

        Node* curr = head;
        Node* tail = nullptr;

        // 为了方便删除，先找到初始的尾节点
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        tail = temp;

        // 移动到起点 k
        for (int i = 1; i < k; ++i) {
            tail = curr;
            curr = curr->next;
        }

        cout << "出列顺序为: " << endl;

        // 开始报数循环
        while (size > 0) {
            // 报数 m-1 次
            for (int i = 1; i < m; ++i) {
                tail = curr;
                curr = curr->next;
            }

            cout << curr->id << " ";

            // 剔除当前节点
            if (size == 1) {
                // 只剩最后一个人时的特殊处理
                delete curr;
                head = nullptr;
            } else {
                tail->next = curr->next; // 断开连接
                Node* deleteNode = curr;
                curr = curr->next;       // 从下一个人重新开始
                delete deleteNode;       // 释放内存
            }
            size--; // 总人数减一

            if (size % 10 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }

    ~JosephusRing() {
        if (head == nullptr) return;

        Node* curr = head->next;
        while (curr != head) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }

private:
    struct Node {
        int id;
        Node* next;
        Node(int val) : id(val), next(nullptr) {}
    };

    Node* head;
    int size;   // 总人数
};

int main() {
    int n, k, m;
    cout << "请输入总人数 n, 起始编号 k, 报数间隔 m:";
    cin >> n >> k >> m;
    JosephusRing ring(n);
    ring.play(k, m);
    return 0;
}