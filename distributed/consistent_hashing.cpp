#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Problem:
Implement consistent hashing for distributing keys across nodes.

Requirements:
1. Support addNode / removeNode.
2. Support virtual nodes for better balance.
3. Given a key, return the owning node.
4. Keep implementation and demo in a single file.

Follow-ups to practice:
- Add weighted nodes.
- Add replication factor > 1.
- Track key movement percentage after topology changes.
*/

class ConsistentHashRing {
    map<uint64_t, string> ring;  // token -> node
    unordered_map<string, vector<uint64_t>> tokens_by_node;

    static uint64_t hash64(const string& key) {
        (void)key;
        // TODO:
        // Return a stable hash for the given key/string.
        return 0;
    }

public:
    void addNode(const string& node, int virtual_nodes = 50) {
        (void)node;
        (void)virtual_nodes;
        // TODO:
        // 1. Generate virtual node tokens.
        // 2. Insert tokens into ring.
        // 3. Track tokens in tokens_by_node.
    }

    void removeNode(const string& node) {
        (void)node;
        // TODO:
        // Remove all virtual node tokens for the given node.
    }

    string getNode(const string& key) const {
        (void)key;
        // TODO:
        // 1. Hash key to a token.
        // 2. Find first token >= key hash (wrap if needed).
        // 3. Return owning node.
        return "";
    }

    void printNodes() const {
        // TODO:
        // Print nodes and vnode counts for debugging/demo.
    }
};

int main() {
    // TODO:
    // 1. Build ring with a few nodes.
    // 2. Map sample keys to nodes.
    // 3. Add/remove a node and observe remapping.
    return 0;
}
