#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Problem:
Implement a quorum-based key-value store simulator (single process, in-memory)
to practice distributed systems interview concepts.

Requirements:
1. N replicas store versioned values.
2. Writes succeed only if acknowledgments >= W.
3. Reads succeed only if replies >= R.
4. Reads return the latest version seen and perform simple read-repair.
5. Keep implementation and demo in a single file.

Follow-ups to practice:
- Add hinted handoff for down replicas.
- Add vector clocks instead of a single version counter.
- Simulate network partitions and stale reads.
*/

struct VersionedValue {
    string value;
    int version = -1;
    bool exists = false;
};

struct Replica {
    string name;
    bool up = true;
    unordered_map<string, VersionedValue> store;
};

class QuorumKVStoreSim {
    vector<Replica> replicas;
    int read_quorum = 0;
    int write_quorum = 0;
    int next_version = 1;

    Replica* findReplica(const string& name) {
        (void)name;
        // TODO:
        // Return pointer to replica by name, or nullptr if not found.
        return nullptr;
    }

public:
    QuorumKVStoreSim(vector<string> names, int r, int w)
        : read_quorum(r), write_quorum(w) {
        (void)names;
        // TODO:
        // Initialize replica list from names.
    }

    void setReplicaUp(const string& name, bool is_up) {
        (void)name;
        (void)is_up;
        // TODO:
        // Mark replica availability.
    }

    bool put(const string& key, const string& value) {
        (void)key;
        (void)value;
        // TODO:
        // 1. Assign a new version.
        // 2. Send write to all reachable replicas.
        // 3. Count ACKs and compare with write_quorum.
        return false;
    }

    optional<string> get(const string& key) {
        (void)key;
        // TODO:
        // 1. Query reachable replicas.
        // 2. Ensure read_quorum replies.
        // 3. Pick latest version.
        // 4. Optionally perform read-repair.
        return nullopt;
    }

    void printReplicaValues(const string& key) {
        (void)key;
        // TODO:
        // Print current value/version per replica for debugging.
    }
};

int main() {
    // TODO:
    // 1. Create cluster with N replicas and quorum settings (R/W).
    // 2. Simulate writes, reads, and replica failures.
    // 3. Observe quorum success/failure and read-repair behavior.
    return 0;
}
