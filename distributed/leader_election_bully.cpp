#include <map>

using namespace std;

/*
Problem:
Simulate the Bully leader election algorithm.

Requirements:
1. Nodes have unique integer IDs.
2. The highest alive node should become leader.
3. Any alive node can initiate an election.
4. Simulate failures/recoveries and leader re-election.
5. Keep implementation and demo in a single file.

Follow-ups to practice:
- Add timeouts and retries.
- Model message delays / drops.
- Compare with Raft-style leader election.
*/

class BullyCluster {
    map<int, bool> alive;  // node_id -> is_alive
    int leader_id = -1;

public:
    void addNode(int id) {
        (void)id;
        // TODO:
        // Add node to cluster and mark it alive.
    }

    void setAlive(int id, bool is_alive) {
        (void)id;
        (void)is_alive;
        // TODO:
        // Update node state; clear leader if current leader goes down.
    }

    void printNodes() const {
        // TODO:
        // Print node IDs and their states.
    }

    int startElection(int starter_id) {
        (void)starter_id;
        // TODO:
        // 1. Validate starter is alive.
        // 2. Send ELECTION to higher IDs.
        // 3. If no higher alive node responds, become leader.
        // 4. Otherwise higher node continues election.
        return -1;
    }

    int leader() const {
        // TODO:
        // Return current leader ID (or -1 if none).
        return leader_id;
    }
};

int main() {
    // TODO:
    // 1. Create cluster with several nodes.
    // 2. Trigger an election.
    // 3. Simulate leader failure and re-election.
    // 4. Simulate highest node recovery and another election.
    return 0;
}
