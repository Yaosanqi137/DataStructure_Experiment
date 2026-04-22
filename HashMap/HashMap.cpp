#include <iostream>

using namespace std;

// 定义哈希表链表节点
struct HashNode {
    int key;            // 存储的数据（键）
    HashNode* next;     // 指向下一个冲突节点的指针

    // 构造函数
    HashNode(int k) {
        key = k;
        next = nullptr;
    }
};

// 定义哈希表类
class HashTable {
private:
    static const int TABLE_SIZE = 10; // 固定的哈希表大小
    HashNode* table[TABLE_SIZE];      // 指针数组，存放链表头节点

    // 私有哈希函数：除留余数法
    int hashFunction(int key) {
        // 如果有负数，abs(key) % TABLE_SIZE 更安全，这里假设输入为非负整数
        return key % TABLE_SIZE;
    }

public:
    // 构造函数：初始化哈希表为空
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    // (2) 插入元素
    void insert(int key) {
        int index = hashFunction(key);

        // 为了严谨，先检查元素是否已经存在，防止重复插入
        HashNode* curr = table[index];
        while (curr != nullptr) {
            if (curr->key == key) {
                // cout << "元素 " << key << " 已存在，无需重复插入。" << endl;
                return;
            }
            curr = curr->next;
        }

        // 发生冲突或首个元素，采用“头插法”插入到链表中
        HashNode* newNode = new HashNode(key);
        newNode->next = table[index];
        table[index] = newNode;

        cout << "已执行 insert(" << key << ")，存入下标 [" << index << "]" << endl;
    }

    // (3) 查找元素
    void search(int key) {
        int index = hashFunction(key);

        // 遍历对应的链表寻找 key
        HashNode* curr = table[index];
        while (curr != nullptr) {
            if (curr->key == key) {
                cout << "search(" << key << "): 存在" << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "search(" << key << "): 不存在" << endl;
    }

    // (4) 删除元素 (注意：避开 C++ 关键字 delete)
    void deleteKey(int key) {
        int index = hashFunction(key);

        HashNode* curr = table[index]; // 当前节点
        HashNode* prev = nullptr;      // 前驱节点

        while (curr != nullptr) {
            if (curr->key == key) {
                // 找到了要删除的节点
                if (prev == nullptr) {
                    // 情况1：要删除的是链表的头节点
                    table[index] = curr->next;
                } else {
                    // 情况2：要删除的是链表的中间或尾部节点
                    prev->next = curr->next;
                }
                delete curr; // 释放内存
                cout << "已执行 delete(" << key << ")" << endl;
                return;
            }
            // 指针后移
            prev = curr;
            curr = curr->next;
        }
        // 如果循环结束还没 return，说明没找到
        cout << "执行 delete(" << key << ") 失败：元素不存在" << endl;
    }

    // 析构函数：释放动态分配的内存，防止内存泄漏
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* curr = table[i];
            while (curr != nullptr) {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
};

int main() {
    HashTable ht;

    cout << "测试插入操作" << endl;
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);

    cout << "\n测试查找操作" << endl;
    ht.search(10);
    ht.search(20);
    ht.search(99); // 额外测一个不存在的数字

    cout << "\n测试删除操作" << endl;
    ht.deleteKey(20);

    cout << "\n验证删除后的查找结果" << endl;
    ht.search(20); // 确保再次查找返回“不存在”

    // 验证删除 20 后，同链表上的 10 和 30 是否依然安好
    ht.search(10);
    ht.search(30);

    return 0;
}