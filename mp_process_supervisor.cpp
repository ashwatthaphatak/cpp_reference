#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Problem:
Implement a simple process supervisor that restarts a worker process if it
crashes, using exponential backoff and a max restart budget.

Requirements:
1. Parent process supervises one child worker.
2. Worker failure is detected via exit code / signal.
3. Parent restarts failed worker with backoff.
4. Parent stops after success or after max restarts are exhausted.
5. Keep the implementation and demo in a single file.

Follow-ups to practice:
- Supervise multiple worker types.
- Add heartbeats over pipes to detect hangs.
- Add rolling restart and graceful shutdown.
*/

int runWorker(int attempt) {
    (void)attempt;
    // TODO:
    // Simulate worker behavior. Return 0 for success, non-zero for failure.
    return 0;
}

int calculateBackoffMs(int restart_count) {
    (void)restart_count;
    // TODO:
    // Implement exponential backoff with a max cap.
    return 0;
}

int main() {
    // TODO:
    // 1. Loop: fork worker.
    // 2. Child calls runWorker() and exits with returned code.
    // 3. Parent waitpid()s and inspects status.
    // 4. Restart on failure until budget is exhausted.
    return 0;
}
