#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    pid_t q;
    printf("before fork\n");
    q = fork();

    if (q < 0) {
        // fork failed
        perror("Fork failed");
        return 1;
    } else if (q == 0) {
        // Child process
        printf("I am the child process with ID: %d\n", getpid());
        printf("My parent's ID is: %d\n", getppid());
    } else {
        // Parent process
        printf("I am the parent process with ID: %d\n", getpid());
        printf("My child's ID is: %d\n", q);
    }

    printf("Process complete\n");
    return 0;
}
