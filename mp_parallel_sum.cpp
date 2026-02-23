#include <cstddef>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

/*
Problem:
Implement a fan-out / fan-in multiprocessing program that computes the sum of
an array in parallel using child processes and pipes.

Requirements:
1. Parent splits work across N child processes.
2. Each child computes a partial sum for its chunk.
3. Parent aggregates partial sums from pipes and waits for all children.
4. Keep the implementation and demo in a single file.

Follow-ups to practice:
- Handle very large payloads with shared memory instead of copying.
- Add a timeout and kill slow/hung workers.
- Return richer results (errors, stats) from children.
*/

bool writeExact(int fd, const void* buf, size_t len) {
    (void)fd;
    (void)buf;
    (void)len;
    // TODO:
    // Loop until all bytes are written or an unrecoverable error occurs.
    return false;
}

bool readExact(int fd, void* buf, size_t len) {
    (void)fd;
    (void)buf;
    (void)len;
    // TODO:
    // Loop until all bytes are read, EOF is reached, or an error occurs.
    return false;
}

long long sumChunk(const vector<int>& nums, size_t left, size_t right) {
    (void)nums;
    (void)left;
    (void)right;
    // TODO:
    // Sum nums[left:right) and return partial sum.
    return 0;
}

int main() {
    // TODO:
    // 1. Build input vector.
    // 2. Create N pipes + fork N children.
    // 3. Child computes chunk sum and writes to pipe.
    // 4. Parent reads partial sums and aggregates.
    // 5. waitpid() all children and validate result.
    return 0;
}
