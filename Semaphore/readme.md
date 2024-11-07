Let's go through the code line-by-line and explain each part, along with the flow of execution.

### Code Breakdown

1. **Include Headers**
    ```c
    #include <stdio.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <unistd.h>
    ```
    These headers include:
    - `stdio.h` for input and output operations.
    - `pthread.h` for using POSIX threads.
    - `semaphore.h` for semaphore operations.
    - `unistd.h` for sleep and other POSIX functions.

2. **Semaphore Declaration**
    ```c
    sem_t mutex;
    ```
    This declares a semaphore `mutex`. It will be used to control access to a critical section.

3. **Thread Function**
    ```c
    void* thread(void* arg)
    ```
    This function, named `thread`, will be executed by each thread. It performs semaphore-based locking.

4. **Semaphore Wait (P operation)**
    ```c
    sem_wait(&mutex);
    ```
    `sem_wait` is used to lock the semaphore. If the semaphore value is greater than zero, it decrements the value and proceeds. If the semaphore value is zero, the thread will block until the value becomes positive.

5. **Enter Critical Section**
    ```c
    printf("\nEntered..\n");
    ```
    Once `sem_wait` successfully locks the semaphore, this line is executed, and the program prints "Entered..". This indicates the thread has entered the critical section.

6. **Simulate Critical Section**
    ```c
    sleep(4);
    ```
    `sleep(4)` simulates work in the critical section, making the thread sleep for 4 seconds.

7. **Semaphore Signal (V operation)**
    ```c
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
    ```
    After the critical section work is done, the program prints "Just Exiting...". The `sem_post` function unlocks the semaphore, incrementing its value and allowing another waiting thread to proceed.

8. **Main Function**
    ```c
    int main()
    ```
    The main function initializes and creates the threads.

9. **Initialize Semaphore**
    ```c
    sem_init(&mutex, 0, 1);
    ```
    Initializes the semaphore `mutex` with an initial value of 1, which allows one thread to enter the critical section at a time.

10. **Create Threads**
    ```c
    pthread_create(&t1, NULL, thread, NULL);
    sleep(2);
    pthread_create(&t2, NULL, thread, NULL);
    ```
    - `pthread_create` is called twice to create two threads `t1` and `t2`, each executing the `thread` function.
    - The `sleep(2)` between the two thread creations ensures a delay of 2 seconds, allowing `t1` to enter the critical section before `t2` tries.

11. **Wait for Threads to Finish**
    ```c
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    ```
    `pthread_join` blocks the main thread until each thread completes its execution.

12. **Destroy Semaphore**
    ```c
    sem_destroy(&mutex);
    ```
    Destroys the semaphore, releasing any resources allocated for it.

### Flow of Execution

Let's follow the flow with the expected output:

1. **Main Thread:** Initializes the semaphore `mutex` with `sem_init(&mutex, 0, 1)`, setting the initial value to 1.

2. **Main Thread:** Creates the first thread `t1` with `pthread_create(&t1, NULL, thread, NULL);`.

3. **Thread t1 Execution:**
   - `t1` calls `sem_wait(&mutex);`. Since `mutex` is 1, it decrements to 0, and `t1` proceeds.
   - `t1` prints "Entered.." and then sleeps for 4 seconds in the critical section.

4. **Main Thread:** Sleeps for 2 seconds.

5. **Main Thread:** After the 2-second delay, creates the second thread `t2` with `pthread_create(&t2, NULL, thread, NULL);`.

6. **Thread t2 Execution:**
   - `t2` calls `sem_wait(&mutex);`. Since `mutex` is 0 (locked by `t1`), `t2` blocks and waits.

7. **Thread t1 Execution (Resumes after sleep):**
   - After 4 seconds, `t1` wakes up and prints "Just Exiting...".
   - `t1` calls `sem_post(&mutex);`, incrementing `mutex` to 1. This unlocks the semaphore, allowing `t2` to proceed.
   - `t1` exits.

8. **Thread t2 Execution (Continues):**
   - Now that `mutex` is 1, `t2` can proceed. It decrements `mutex` to 0 and enters the critical section.
   - `t2` prints "Entered.." and then sleeps for 4 seconds.

9. **Thread t2 Execution (Resumes after sleep):**
   - After 4 seconds, `t2` wakes up and prints "Just Exiting...".
   - `t2` calls `sem_post(&mutex);`, setting `mutex` back to 1.
   - `t2` exits.

10. **Main Thread:** Waits for both `t1` and `t2` to finish with `pthread_join`.

11. **Main Thread:** Destroys the semaphore with `sem_destroy(&mutex);` and the program ends.

### Expected Output

The expected output follows this sequence:

```
Entered..
Just Exiting...
Entered..
Just Exiting...
```

This output is spaced out by sleep intervals, illustrating how `t1` completes its critical section before `t2` is allowed to enter.




---------------------------------

## Must Know :


------------------------------
The `sem_init` function is used to initialize a semaphore in C. This function sets up a semaphore so it can be used for controlling access to shared resources by multiple threads. Here’s a closer look at its syntax and arguments:

### Syntax

```c
int sem_init(sem_t *sem, int pshared, unsigned int value);
```

### Parameters

1. **`sem` (sem_t *):**
   - This is a pointer to the semaphore variable that will be initialized. For example, in `sem_init(&mutex, 0, 1);`, `mutex` is a global or local semaphore variable declared as `sem_t mutex;`.
   - This pointer is required because the function modifies the semaphore structure directly.

2. **`pshared` (int):**
   - This parameter determines if the semaphore is shared between processes or just between threads within the same process.
   - If `pshared` is set to `0`, the semaphore is shared only between threads of the same process.
   - If `pshared` is set to a non-zero value, the semaphore can be shared between processes, provided it’s located in a shared memory region. This is useful for inter-process communication (IPC), but not relevant when threads in a single process are being synchronized, as in this example.

3. **`value` (unsigned int):**
   - This is the initial value of the semaphore.
   - Setting `value` to `1` makes it a binary semaphore (or mutex), allowing one thread at a time to access the critical section.
   - If the value is greater than `1`, it allows more than one thread to enter the critical section concurrently. For example, a semaphore initialized to `3` would allow up to three threads to access the critical section simultaneously.

### Return Value

- **`0`** on success.
- **`-1`** on failure (in which case, `errno` is set to indicate the error).

### Example: `sem_init(&mutex, 0, 1);`

In this example:
- `&mutex`: A pointer to the semaphore variable `mutex`.
- `0`: Specifies that the semaphore is only shared between threads within the same process.
- `1`: Initializes the semaphore with a value of `1`, making it a binary semaphore (only one thread can access the critical section at a time).

### Usage

Here’s what happens in the program with `sem_init(&mutex, 0, 1);`:
- When `sem_wait` is called by a thread, it decrements the semaphore’s value.
   - If the value is greater than 0, the thread enters the critical section.
   - If the value is 0, the thread waits until another thread increments the semaphore with `sem_post`.
- When a thread calls `sem_post`, it increments the semaphore’s value, potentially allowing a waiting thread to proceed.

This setup with `sem_init` helps control access to shared resources, preventing race conditions by ensuring that only one thread can enter the critical section at a time.
------------------------------------

The `pthread_create` function in C is used to create a new thread within a program. It allows the program to perform tasks concurrently by running multiple threads in parallel. 

### Syntax

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

### Parameters

1. **`thread` (pthread_t *):**
   - A pointer to a `pthread_t` variable where the ID of the newly created thread will be stored.
   - This ID is used later to identify and interact with the thread, such as waiting for it to finish with `pthread_join`.

2. **`attr` (const pthread_attr_t *):**
   - Specifies the thread attributes, such as stack size and scheduling parameters.
   - Passing `NULL` uses the default attributes, which are usually sufficient unless there are specific requirements.

3. **`start_routine` (void *(*)(void *)):**
   - A pointer to the function that the thread will execute. This function must have a specific signature: it takes a `void *` argument and returns a `void *`.
   - When the thread starts, it immediately begins executing this function.

4. **`arg` (void *):**
   - A pointer to an argument that will be passed to the `start_routine` function.
   - If the function doesn’t need an argument, `NULL` is typically passed here. If an argument is needed, it can be a pointer to any data type, and the function must interpret it accordingly.

### Return Value

- **`0`** on success, indicating that the thread was successfully created.
- **Non-zero value** on failure, indicating an error (the exact error code varies).

### Example: `pthread_create(&t1, NULL, thread, NULL);`

In this example:
- **`&t1`:** A pointer to the `pthread_t` variable `t1`, where the new thread's ID will be stored.
- **`NULL`:** This indicates that the default thread attributes are used.
- **`thread`:** The function that the thread will execute. This is the entry point for the new thread.
- **`NULL`:** No argument is being passed to the `thread` function, so `NULL` is specified.

### How `pthread_create` Works in the Program

Let’s break down what happens when `pthread_create(&t1, NULL, thread, NULL);` is called:

1. **Create a New Thread:**
   - A new thread `t1` is created, and it begins executing the specified `start_routine` function, which in this case is `thread`.
   - The main thread continues to run in parallel, and both threads (main and `t1`) run concurrently.

2. **Thread Entry Point:**
   - The new thread `t1` starts at the beginning of the `thread` function.
   - In this example, `thread` contains code to wait on a semaphore, print a message, and simulate work with `sleep`.

3. **Concurrent Execution:**
   - After creating `t1`, the main thread waits for 2 seconds, then creates another thread `t2`.
   - Each thread executes the `thread` function independently, but due to the semaphore (`sem_wait` and `sem_post`), only one thread can enter the critical section at a time.

4. **Returning from `pthread_create`:**
   - `pthread_create` returns immediately after starting the thread, so it doesn't wait for the thread to finish.
   - Control returns to the main thread, allowing it to proceed with its next instructions, such as creating additional threads or waiting for them to finish with `pthread_join`.

### Example Program

Here’s a minimal example that shows the use of `pthread_create`:

```c
#include <stdio.h>
#include <pthread.h>

void* print_message(void* arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Creating two threads that will run the print_message function
    pthread_create(&thread1, NULL, print_message, "Hello from Thread 1");
    pthread_create(&thread2, NULL, print_message, "Hello from Thread 2");

    // Waiting for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

### Expected Output

Since `thread1` and `thread2` run concurrently, the output order may vary, but it might look like:

```
Hello from Thread 1
Hello from Thread 2
```

In this example, `pthread_create` starts two threads, each of which runs `print_message` and prints a message. The main function then waits for both threads to complete before exiting.



