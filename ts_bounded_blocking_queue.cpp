#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>
#include <thread>

using namespace std;

/*
Problem:
Implement a thread-safe bounded blocking queue for a producer-consumer system.

Requirements:
1. Multiple producers and multiple consumers must be supported.
2. Producers block when the queue is full.
3. Consumers block when the queue is empty.
4. Add a graceful shutdown so waiting threads can exit cleanly.
5. Keep the implementation and demo in a single file.

Follow-ups to practice:
- Add timed push/pop APIs.
- Add metrics (drops, waits, throughput).
- Make the queue generic and move-only friendly.
*/

template <typename T>
class BoundedBlockingQueue {
    deque<T> buffer;
    size_t capacity;
    bool closed = false;

    mutex mtx;
    condition_variable not_empty;
    condition_variable not_full;

public:
    explicit BoundedBlockingQueue(size_t cap) : capacity(cap) {}

    bool push(T value) {
        (void)value;
        // TODO:
        // 1. Wait until queue has space or shutdown is triggered.
        // 2. Return false if queue is closed.
        // 3. Push value, then notify one consumer.
        return false;
    }

    optional<T> pop() {
        // TODO:
        // 1. Wait until queue has an item or shutdown is triggered.
        // 2. If queue is empty and closed, return nullopt.
        // 3. Pop item, notify one producer, return item.
        return nullopt;
    }

    void shutdown() {
        // TODO:
        // 1. Mark queue as closed under lock.
        // 2. Wake all waiting producers and consumers.
    }

    size_t size() {
        // TODO:
        // Return current queue size under lock.
        return 0;
    }
};

void producer(BoundedBlockingQueue<int>& q, int producer_id, int start_value) {
    (void)q;
    (void)producer_id;
    (void)start_value;
    // TODO:
    // Produce a sequence of values and push into queue.
}

void consumer(BoundedBlockingQueue<int>& q, int consumer_id) {
    (void)q;
    (void)consumer_id;
    // TODO:
    // Repeatedly pop until shutdown/empty sentinel behavior is defined.
}

int main() {
    // TODO:
    // 1. Construct queue with a small capacity.
    // 2. Start multiple producer/consumer threads.
    // 3. Join producers, then call shutdown().
    // 4. Join consumers.
    return 0;
}
