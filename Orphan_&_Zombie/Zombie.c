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
