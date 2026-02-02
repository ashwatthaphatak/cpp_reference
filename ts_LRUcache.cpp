#include <bits/stdc++.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <unordered_map>

#define SIZE 5

using namespace std;
/*

DoublyNode class -> implement a Doubly linked list object

LRUCache class -> 
- Here, I will implement all operations related to modifying the Cache/
- Also I will include an unordered map to map the key inserted to the pair (Node*, value) -> This will give me O(1) retrieval time for the get operation
- Two operations ->
    a. Update a value (or insert) -> 
        1. Check if the node key is there in the map  
        2. If not, first check the size of the linked list 
        3. If space available -> create a new node and do ->
            node->next->prev = cur
            cur->next = head->next
            head->next = cur
            cur->prev = head
        4. If no space available, remove the LRU node by doing
            lru = tail->prev
            tail->prev = tail->prev->prev
            tail->prev->next = tail
            delete lru
        5. Update the map accordingly by erasing the removed key and        inserting the added key
    b. Read a node ->
        1. Check if the node is there in the map 
            a. Return val if it exists
            b. Return -1 if does not exist
*/

class DoublyNode {
public:
    int val;
    int key;
    DoublyNode* next;
    DoublyNode* prev;

    // default constructor 
    DoublyNode() : val(0), key(0), prev(nullptr), next(nullptr) {};
    // constructor with val
    DoublyNode(int x, int y) : val(x), key(y), prev(nullptr), next(nullptr) {};
    // constructor with both val and pointers
    DoublyNode(int x, int y, DoublyNode* next, DoublyNode* prev) : val(x), key(y), prev(prev), next(next)  {};
};

class LRUCache {

    DoublyNode* head; 
    DoublyNode* tail;
    unordered_map<int, DoublyNode*> keyMap; 
    int size = 0;
    mutex cache;

public:
    // constructor
    LRUCache () {
        head = new DoublyNode();
        tail = new DoublyNode();
        head->next = tail;
        tail->prev = head;
    }

    // insert new node
    void update(int key, int val) {
        // check if the value exists beforehand
        lock_guard<mutex> updateLock(cache);
        if (SIZE == 0) return;

        if (keyMap.find(key) == keyMap.end()) {
            if (size == SIZE) {
                DoublyNode* lru = tail->prev;
                lru->prev->next = tail;
                tail->prev = lru->prev;
                size--;
                keyMap.erase(lru->key);
                delete lru;
            }
            DoublyNode* cur = new DoublyNode(val, key);
            
            cur->prev = head;
            cur->next = head->next;
            head->next->prev = cur;
            head->next = cur;

            keyMap[key] = cur;
            size++;
        } else {
            DoublyNode* cur = keyMap[key];
            cur->val = val;

            cur->next->prev = cur->prev;
            cur->prev->next = cur->next;

            head->next->prev = cur;
            cur->next = head->next;
            cur->prev = head;
            head->next = cur;
        }
    }

    int fetch(int key) {
        lock_guard<mutex> readLock(cache);

        if (keyMap.find(key) == keyMap.end()) return -1;

        DoublyNode* cur = keyMap[key];
        int value = cur->val;
        
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;

        head->next->prev = cur;
        cur->next = head->next;
        cur->prev = head;
        head->next = cur;
        
        return value;
    }

};

void Insert(LRUCache& cache, int key, int value, int id) {
    cache.update(key, value);
    cout<< "Thread "<< id << " set the value " << value << " for key" << key<< endl;
}

void Fetch(LRUCache& cache, int key, int id) {
    int value = cache.fetch(key);
    cout<< "Thread "<< id << " fetched the value " << value << " for key" << key<< endl;
}


int main() {
    LRUCache cache;

    thread t1(Insert, ref(cache), 1, 100, 1);
    thread t2(Insert, ref(cache), 2, 200, 2);
    thread t7(Fetch, ref(cache), 1, 7);
    thread t3(Insert, ref(cache), 3, 300, 3);
    thread t8(Fetch, ref(cache), 4, 8);
    thread t4(Insert, ref(cache), 1, 10, 4);
    thread t5(Insert, ref(cache), 2, 20, 5);
    thread t6(Insert, ref(cache), 3, 30, 6);
    thread t9(Fetch, ref(cache), 1, 9);
    thread t10(Fetch, ref(cache), 3, 10);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    return 0;
}