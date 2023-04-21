#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LEN = 100;

struct Queue {
    int data[MAX_LEN];
    int front, rear;
};

void initQueue(Queue& q) 
{
    q.front = -1;
    q.rear = -1;
}

bool isQueueEmpty(Queue q) {
    return (q.front == -1 && q.rear == -1);
}

bool isQueueFull(Queue q) {
    return (q.rear == MAX_LEN - 1);
}

void enqueue(Queue& q, int val) {
    if (isQueueFull(q)) {
        cout << " Queue is full\n";
        return;
    }
    else if (isQueueEmpty(q)) {
        q.front = 0;
        q.rear = 0;
    }
    else {
        q.rear++;
    }
    q.data[q.rear] = val;
}

int dequeue(Queue& q) {
    if (isQueueEmpty(q)) {
        cout << " Queue is empty\n";
        return -1;
    }
    else if (q.front == q.rear) {
        int val = q.data[q.front];
        q.front = -1;
        q.rear = -1;
        return val;
    }
    else {
        int val = q.data[q.front];
        q.front++;
        return val;
    }
}

void printQueue(Queue q) {
    if (isQueueEmpty(q)) {
        cout << "Queue is empty\n";
        return;
    }
    for (int i = q.front; i <= q.rear; i++) {
        cout << q.data[i] << " ";
    }
    cout << endl;
}

int main() {
    Queue q;
    initQueue(q);

    // читання чисел з файлу і додавання їх до черги
    ifstream fin("input.txt");
    int num;
    while (fin >> num) {
        enqueue(q, num);
    }
    fin.close();

    // виведення елементів черги
    cout << "Queue: ";
    printQueue(q);

    // пошук елемента в черзі
    int searchValue;
    cout << "Enter a value to search in the queue: ";
    cin >> searchValue;

    int foundIndex = -1;
    for (int i = q.front; i <= q.rear; i++) {
        if (q.data[i] == searchValue) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Value not found in the queue\n";
    }
    else {
        // розділення черги на дві
        Queue q2;
        initQueue(q2);

        while (!isQueueEmpty(q)) {
            int val = dequeue(q);
            if (val == searchValue) {
                enqueue(q2, val);
                break;
            }
            else {
                enqueue(q2, val);
            }
        }

        // виведення результатів
        cout << "Queue 1: ";
        printQueue(q);
        cout << "Queue 2: ";
        printQueue(q2);
    }

    return 0;
}
