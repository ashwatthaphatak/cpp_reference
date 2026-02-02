#include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

/*
    Implement a thread-safe data structure that tracks incoming requests grouped by IP over a time window.
    Add support for grouping by other attributes (e.g., BrowserAgent).

-----

Solution

Goal ->
1. Track incoming requests grouped by IP
2. Support a sliding time window
3. Ensure thread-safe updates and reads
4. Allow easy extension for grouping by other attributes

-----

Clarifications / Assumptions ->

1. Each request has a timestamp (epoch seconds)
2. Time window is sliding (last W seconds)
3. Exact counts are required (no approximation)
4. Data structure is in-memory
5. Starvation is acceptable (simple locking)

-----

Invariants ->

1. Only requests with timestamp >= (now - WINDOW) are counted
2. Requests are immutable events
3. For each IP, timestamps are stored in increasing order
4. Memory usage is bounded by evicting old timestamps
5. All shared state is protected by a mutex

-----

Approach ->

1. Use an unordered_map to group requests by IP
2. For each IP, maintain a queue (deque) of timestamps
3. On every insert or read:
   a. Remove timestamps older than (now - WINDOW)
4. Protect the entire structure using a single mutex

-----

Scenarios ->

1. Multiple threads recording requests for same IP
2. Multiple threads querying counts concurrently
3. Requests arriving out of order (handled by timestamp checks)
4. IP stops sending requests -> entry removed automatically

*/

using namespace std;

#define WINDOW 5   // sliding window size in seconds

// Request object (immutable)
struct Request {
    uint64_t timestamp;
    string ip;
    string agent; // optional grouping attribute (unused for now)
};

class TrackRequests {

    // Map -> IP -> timestamps of requests
    unordered_map<string, deque<uint64_t>> requests;
    mutex mtx;

    // Remove expired timestamps for a given IP
    void cleanup(const string& ip, uint64_t now) {
        auto& q = requests[ip];

        while (!q.empty() && q.front() <= now - WINDOW) {
            q.pop_front();
        }

        // Remove IP entry if no requests remain
        if (q.empty()) {
            requests.erase(ip);
        }
    }

public:

    // Called when a request arrives
    void recordRequest(const Request& r) {
        unique_lock<mutex> lock(mtx);

        requests[r.ip].push_back(r.timestamp);
        cleanup(r.ip, r.timestamp);
    }

    // Called to query request count for an IP
    int getRequestCount(const string& ip, uint64_t now) {
        unique_lock<mutex> lock(mtx);

        if (requests.find(ip) == requests.end()) {
            return 0;
        }

        cleanup(ip, now);
        return requests[ip].size();
    }
};

// Simulated request generator
void Client(TrackRequests& t, string ip, int delay) {
    this_thread::sleep_for(chrono::milliseconds(delay));
    t.recordRequest({static_cast<uint64_t>(time(nullptr)), ip, ""});
    cout << "Request from IP " << ip << endl;
}

// Simulated reader
void Monitor(TrackRequests& t, string ip) {
    this_thread::sleep_for(chrono::milliseconds(200));
    int count = t.getRequestCount(ip, time(nullptr));
    cout << "Count for IP " << ip << " = " << count << endl;
}

int main() {

    TrackRequests tracker;

    thread c1(Client, ref(tracker), "1.1.1.1", 10);
    thread c2(Client, ref(tracker), "1.1.1.1", 20);
    thread c3(Client, ref(tracker), "2.2.2.2", 30);
    thread c4(Client, ref(tracker), "2.2.2.2", 40);

    thread m1(Monitor, ref(tracker), "1.1.1.1");
    thread m2(Monitor, ref(tracker), "2.2.2.2");

    c1.join();
    c2.join();
    c3.join();
    m1.join();
    m2.join();

    return 0;
}