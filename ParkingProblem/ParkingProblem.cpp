#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// 车辆信息结构体
struct Car {
    string plate;    // 车牌号
    int arriveTime;  // 到达/进入停车场的时间
    
    Car(string p, int t) : plate(p), arriveTime(t) {}
};

class ParkingLot {
private:
    int capacity;          // 停车场最大容量
    double pricePerUnit;   // 每单位时间收费标准
    
    stack<Car> parkStack;  // 停车场主栈
    queue<Car> waitQueue;  // 便道等候队列

public:
    ParkingLot(int cap, double price) : capacity(cap), pricePerUnit(price) {}

    // 车辆到达
    void carArrive(string plate, int time) {
        if (parkStack.size() < capacity) {
            // 停车场有空位，直接进入
            parkStack.push(Car(plate, time));
            cout << "[到达] 车辆 " << plate << " 直接进入停车场，停在第 " 
                 << parkStack.size() << " 个车位。" << endl;
        } else {
            // 停车场已满，进入便道等候
            waitQueue.push(Car(plate, time));
            cout << "[到达] 停车场已满，车辆 " << plate << " 进入便道等候，当前排在第 " 
                 << waitQueue.size() << " 位。" << endl;
        }
    }

    // 车辆离开
    void carDepart(string plate, int leaveTime) {
        stack<Car> tempStack; // 临时栈，用于给里面的车让路
        bool found = false;

        // 1. 在停车场中寻找该车，并让挡路的车退出到临时栈
        while (!parkStack.empty()) {
            Car topCar = parkStack.top();
            if (topCar.plate == plate) {
                found = true;
                break; // 找到了，跳出循环，此时 topCar 就是要离开的车
            }
            // 还没找到，说明这辆车挡路了，先退到临时栈
            tempStack.push(topCar);
            parkStack.pop();
        }

        // 2. 判断是否找到该车并进行结算
        if (found) {
            Car departCar = parkStack.top();
            parkStack.pop(); // 目标车辆正式离开停车场
            
            // 计算停留时间和费用
            int stayTime = leaveTime - departCar.arriveTime;
            double fee = stayTime * pricePerUnit;
            cout << "[离开] 车辆 " << plate << " 离开停车场。停留时间: " 
                 << stayTime << "，应缴费用: " << fee << " 元。" << endl;

            // 3. 把临时栈里的车重新开回停车场
            while (!tempStack.empty()) {
                parkStack.push(tempStack.top());
                tempStack.pop();
            }

            // 4. 从便道队列中放一辆车进入停车场
            if (!waitQueue.empty()) {
                Car nextCar = waitQueue.front();
                waitQueue.pop();
                // 注意：进入停车场的时间要更新为当前时间（即上一辆车离开的时间）
                nextCar.arriveTime = leaveTime; 
                parkStack.push(nextCar);
                cout << "[调度] 便道等候的车辆 " << nextCar.plate 
                     << " 进入停车场，记时开始。" << endl;
            }
        } else {
            // 恢复原状（把临时栈里的车放回去）
            while (!tempStack.empty()) {
                parkStack.push(tempStack.top());
                tempStack.pop();
            }
            cout << "[错误] 停车场内未找到车牌号为 " << plate << " 的车辆！" << endl;
        }
    }
    
    // 打印当前停车场状态（用于调试和展示）
    void printStatus() {
        cout << "\n--- 当前状态 ---" << endl;
        cout << "停车场内车辆数: " << parkStack.size() << " / " << capacity << endl;
        cout << "便道等候车辆数: " << waitQueue.size() << endl;
        cout << "----------------\n" << endl;
    }
};

int main() {
    int n;
    double price;
    cout << "请输入停车场最大容量 n: ";
    cin >> n;
    cout << "请输入每单位时间收费价格: ";
    cin >> price;

    ParkingLot pl(n, price);

    cout << "\n系统初始化完成。支持的操作指令：" << endl;
    cout << "A 车牌号 到达时间  (例: A 京A99999 10)" << endl;
    cout << "D 车牌号 离开时间  (例: D 京A99999 15)" << endl;
    cout << "E 退出系统" << endl;

    char action;
    string plate;
    int time;

    while (true) {
        cout << "\n请输入指令: ";
        cin >> action;
        if (action == 'E' || action == 'e') {
            cout << "撒由那拉" << endl;
            break;
        }

        cin >> plate >> time;

        if (action == 'A' || action == 'a') {
            pl.carArrive(plate, time);
            pl.printStatus();
        } else if (action == 'D' || action == 'd') {
            pl.carDepart(plate, time);
            pl.printStatus();
        } else {
            cout << "无效指令，请重新输入！" << endl;
        }
    }

    return 0;
}