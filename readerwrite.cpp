#include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

// Multiple Readers, Single writer only at a time

class RWController {

    mutex database;
    condition_variable can_read;
    condition_variable can_write;

    int active_readers = 0;
    int active_writers = 0;
    int waiting_readers = 0;
    int waiting_writers = 0;

public:
    // Called before a reader enters
    void reader_enter() {
        unique_lock<mutex> lock(database);
        waiting_readers++;

        can_read.wait(lock, [&] {
            return (waiting_writers + active_writers == 0);
        });

        waiting_readers--;
        active_readers++;
        // lock.unlock();
    }

    // Called after a reader exits
    void reader_exit() {
        unique_lock<mutex> lock(database);
        active_readers--;
        if (active_readers == 0 && waiting_writers > 0) {
            can_write.notify_one();
        }
        // lock.unlock();
    }

    // Called before a writer enters
    void writer_enter() {
        unique_lock<mutex> lock(database);
        waiting_writers++;

        can_write.wait(lock, [&] {
            return (active_readers + active_writers == 0);
        });

        waiting_writers--;
        active_writers++;
        // lock.unlock();
    }

    // Called after a writer exits
    void writer_exit() {
        unique_lock<mutex> lock(database);
        active_writers--;
        if (waiting_writers == 0) {
            can_read.notify_all();
        } else can_write.notify_one();
        // lock.unlock();
    }
};

void reader(RWController& c, int& resource, int id) {
    c.reader_enter();
    int value = resource;
    cout << "Reader " << id << " read data" << value << endl;
    c.reader_exit();    
    // return value;
};

void writer(RWController& c, int& resource, int value, int id) {
    c.writer_enter();
    value += resource;
    resource = value;
    cout << "Writer " << id << " wrote data" << value << endl;
    c.writer_exit();
    
    // return value;
}

int main() {

    int resource = 0;
    RWController c;
    // writer 1
    thread writer1(writer, ref(c), ref(resource), 1, 1);
    // readers 1,2
    thread reader1(reader, ref(c), ref(resource), 1);
    thread reader2(reader, ref(c), ref(resource), 2);
    // writer 2
    thread writer2(writer, ref(c), ref(resource), 2, 2);
    // readers 3,4
    thread reader3(reader, ref(c), ref(resource), 3);
    thread reader4(reader, ref(c), ref(resource), 4);

    writer1.join();
    reader1.join();
    reader2.join();
    writer2.join();
    reader3.join();
    reader4.join();

    cout << "All threads have finished execution." << endl;

    return 0;
}