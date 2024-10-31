## Orphan and Zombie Processes

### Orphan Processes

An **orphan process** is a process that continues to run after its parent process has terminated. When a parent process exits, its child processes are not immediately destroyed. Instead, they are adopted by the `init` process (usually with PID 1) in Unix-like operating systems. The `init` process periodically checks for terminated child processes to clean up.

**Characteristics:**
- Orphan processes can consume system resources until they are reaped by the `init` process.
- They can be identified by the absence of a parent process ID (PPID) other than 1.

**Example:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(5); // Simulate some work
        printf("Child process %d is running\n", getpid());
        exit(0);
    } else {
        // Parent process exits immediately
        exit(0);
    }
}
```

In this example, the child process becomes an orphan when the parent exits before the child has finished executing.

### Zombie Processes

A **zombie process** is a process that has completed execution but still has an entry in the process table. This occurs when a parent process has not yet called `wait()` or `waitpid()` to read the exit status of the terminated child process. The zombie process retains its PID and resource information until it is reaped.

**Characteristics:**
- Zombie processes do not consume system resources like CPU or memory but occupy a slot in the process table.
- They can lead to resource leaks if too many zombies accumulate, as they reduce the number of available process IDs.

**Example:**
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process %d is running\n", getpid());
        exit(0); // Terminate child process
    } else {
        // Parent process sleeps for a while
        sleep(10); // Simulate work
        printf("Parent process %d exiting\n", getpid());
        // If wait() is not called, child becomes a zombie
    }
}
```

In this example, the child process becomes a zombie after it exits because the parent process does not call `wait()` to read its exit status before exiting.

### Summary

- **Orphan Process**: A child process that continues to run after its parent has terminated. It is adopted by the `init` process.
- **Zombie Process**: A completed child process that still has an entry in the process table because its parent has not called `wait()`.

