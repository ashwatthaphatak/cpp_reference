#include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <semaphore>

using namespace std;

#define SIZE 5


class Queue {
private:
    int buffer[SIZE];
    // Circular buffer implementation
    int head = 0, tail = 0, count = 0; // count >= SIZE -> buffer full ; count <= 0 -> buffer empty

    // Linear Queue (Bounded)
    // int front = -1;
    // int rear = -1;

    mutex mtx;
    condition_variable not_empty;
    condition_variable not_full;

public: 

    void enqueue(int value) {
        // insert the value at the rear of the queue
        unique_lock<mutex> lock(mtx);

        // not_full.wait(lock, [&] { 
        //    return rear < SIZE - 1; // check if the queue has space 
        // });

        // if (front == -1) {
        //     front = 0;
        // }
        // rear++;
        // buffer[rear] = value;
        
        // Circular Buffer
        not_full.wait(lock, [&] { 
           return count < SIZE; // check if the queue has space 
        });

        buffer[tail] = value;
        tail = (tail + 1) % SIZE;
        count++;
        lock.unlock();
        not_empty.notify_one();
    }

    int dequeue() {
        // remove the value from the front of the queue
        unique_lock<mutex> lock(mtx);

        // not_empty.wait(lock, [&] {
        //     return !isempty(); 
        // });

        // int value = buffer[front];

        // if (front == rear) {
        //     front = rear = -1;
        // } else {
        //     front++;
        // }

        not_empty.wait(lock, [&] {
            return !isempty(); 
        });

        int value = buffer[head];
        head = (head + 1) % SIZE;
        count--; 
        
        lock.unlock();
        not_full.notify_one();
        return value;
    }

    int showfront() {
        // display the front value of the queue
        lock_guard<mutex> lock(mtx);
        if (isempty()) {
            return -1;
        } else {
            return buffer[head];
        }
    }

    bool isempty() {
        // check if the queue is empty
        if (count <= 0) {
            return true;
        } else  {
            return false;
        }        
    }
    bool isfull() {
        if (count >= SIZE) {
            return true;
        } else return false;
    }
};

void producer(Queue& q, int id, int count) {
    for (int i = 0; i < count; i++) {
        int value = id * 100 + i;
        q.enqueue(value);
        cout << "Producer " << id << " enqueued " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

void consumer(Queue& q, int id, int count) {
    for (int i = 0; i < count; i++) {
        int value = q.dequeue();
        cout << "Consumer " << id << " dequeued " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

int main() {
    Queue q;

    thread prod1(producer, ref(q), 1, 50);
    thread cons1(consumer, ref(q), 1, 20);
    thread prod2(producer, ref(q), 2, 10);
    thread cons2(consumer, ref(q), 2, 40);
    // cout << "Is queue empty? " << (q.isempty() ? "Yes" : "No") << endl;

    prod1.join();
    cons1.join();
    prod2.join();
    cons2.join();

    cout << "All threads have finished execution." << endl;

    return 0;
}
