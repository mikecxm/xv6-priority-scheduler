// testprio.c
// ------------------------------
// User program to test the priority-based scheduler in xv6.
//
// Creates 3 child processes, each running a simple loop.
// Parent assigns different priorities to each child using setpriority().
// Demonstrates that the scheduler prefers processes with higher priority.
//
// Expected: Process with highest priority prints more frequently.
// ------------------------------

#include "types.h"
#include "stat.h"
#include "user.h"

// Function executed by each child process
void child_work(int id) {
    int i;
    for(i = 0; i < 10; i++){
        // Print PID, child ID, and iteration number
        printf(1, "PID %d (child %d) iter %d\n", getpid(), id, i);

        // Yield to allow scheduler to switch processes
        yield();
    }
    exit();  // terminate child
}

int main(int argc, char *argv[]){
    int p1, p2, p3;

    // Fork first child
    p1 = fork();
    if(p1 == 0){
        child_work(1);  // child 1 executes
    }

    // Fork second child
    p2 = fork();
    if(p2 == 0){
        child_work(2);  // child 2 executes
    }

    // Fork third child
    p3 = fork();
    if(p3 == 0){
        child_work(3);  // child 3 executes
    }

    // Parent process: set priorities
    // Lower number = lower priority, higher number = higher priority
    setpriority(p1, 5);   // child 1: low priority
    setpriority(p2, 30);  // child 2: high priority
    setpriority(p3, 10);  // child 3: medium priority

    // Wait for all children to finish
    wait();
    wait();
    wait();

    exit();  // parent exits
}
