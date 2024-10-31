### Multithreading in C

**What is a Thread?**  
A thread is a single sequence of instructions within a process. Because threads share some characteristics with processes, they are often referred to as lightweight processes.

**What are the Differences Between Processes and Threads?**  
Unlike processes, threads are not completely independent. They share their code, data, and operating system resources, such as open files and signals. However, each thread has its own program counter, set of registers, and stack space, just like processes do.

**Why Use Multithreading?**  
Threads are a popular way to enhance applications through parallelism. For example, in a web browser, each tab can operate as a separate thread. Microsoft Word also utilizes multiple threads: one for formatting text and another for handling user inputs. To learn how to use multithreading with data structures for efficient programming, consider taking a comprehensive course like the C Programming Course Online with Data Structures.

Threads are faster than processes for several reasons:
1. **Faster Creation**: Creating threads is quicker than creating processes.
2. **Quick Context Switching**: Switching between threads is more efficient.
3. **Easy Termination**: Threads can be terminated more easily.
4. **Faster Communication**: Communication between threads is quicker.

For more details, visit [this resource](http://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/threads.htm).

**Can We Write Multithreading Programs in C?**  
Unlike Java, the C language standard does not support multithreading natively. However, you can use POSIX Threads (Pthreads), which is a standard for implementing multithreading in C. The Pthreads library can be accessed using the gcc compiler.

### Example C Program Using Pthreads

The following program demonstrates basic Pthread functions. Note that it requires a C compiler with the Pthreads library to compile successfully.

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For the sleep() function

// A normal C function that runs as a thread
void* myThreadFun(void* vargp)
{
    sleep(1);
    printf("Hello World from Thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}
```

In the `main()` function, we declare a variable called `thread_id`, which is of type `pthread_t`, used to identify the thread in the system. After declaring `thread_id`, we call `pthread_create()` to create a thread.

The `pthread_create()` function takes four arguments:
1. A pointer to `thread_id`, which gets set by this function.
2. Attributes for the thread. If set to `NULL`, default attributes are used.
3. The name of the function to execute for the new thread.
4. An argument to pass to the function `myThreadFun`.

The `pthread_join()` function is similar to the `wait()` function for processes. It blocks the calling thread until the specified thread terminates.

#### Explanation of Each Line

1. **`#include <pthread.h>`**: Includes the Pthreads library, which provides functions for creating and managing threads.
  
2. **`#include <stdio.h>`**: Includes the standard input/output library for functions like `printf`.

3. **`#include <stdlib.h>`**: Includes the standard library for functions like `exit`.

4. **`#include <unistd.h>`**: Includes the header for UNIX standard functions, including `sleep`.

5. **`void* myThreadFun(void* vargp)`**: Defines a function `myThreadFun` that will be executed as a thread. It takes a `void*` argument, which allows passing any data type.

6. **`sleep(1);`**: The thread pauses for 1 second to simulate some work being done.

7. **`printf("Hello World from Thread \n");`**: Prints a message indicating that the thread is running.

8. **`return NULL;`**: Indicates that the thread has completed its execution.

9. **`int main()`**: The main function where the program starts executing.

10. **`pthread_t thread_id;`**: Declares a variable `thread_id` of type `pthread_t` to hold the thread identifier.

11. **`printf("Before Thread\n");`**: Prints a message before the thread is created.

12. **`pthread_create(&thread_id, NULL, myThreadFun, NULL);`**: Creates a new thread. 
   - `&thread_id` is a pointer to the thread ID variable.
   - `NULL` means default thread attributes are used.
   - `myThreadFun` is the function that the thread will execute.
   - `NULL` indicates no arguments are passed to `myThreadFun`.

13. **`pthread_join(thread_id, NULL);`**: Waits for the thread identified by `thread_id` to finish execution before proceeding.

14. **`printf("After Thread\n");`**: Prints a message after the thread has completed.

15. **`exit(0);`**: Exits the program with a status code of 0, indicating successful completion.

### Output of the First Program

When you run this program, you may see the following output:

```
Before Thread
Hello World from Thread 
After Thread
```

- **"Before Thread"** is printed first because the main thread runs it.
- After a 1-second pause, **"Hello World from Thread"** is printed by the created thread.
- Finally, after the thread finishes, **"After Thread"** is printed by the main thread.

### C Program Demonstrating Multiple Threads with Global and Static Variables

Since all threads share the data segment, global and static variables are accessible by all threads. Here’s an example:

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Global variable
int g = 0;

// Function to be executed by all threads
void* myThreadFun(void* vargp)
{
    int myid = getpid(); // Get thread ID

    // Static variable to observe changes
    static int s = 0;

    // Increment static and global variables
    ++s;
    ++g;

    // Print thread ID, static, and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid,
           ++s, ++g);
}

int main()
{
    pthread_t tid;

    // Create three threads
    for (int i = 0; i < 3; i++)
        pthread_create(&tid, NULL, myThreadFun, NULL);

    pthread_exit(NULL); // Wait for threads to finish
    return 0;
}
```

#### Explanation of Each Line

1. **`#include <pthread.h>`**: Includes the Pthreads library.

2. **`#include <stdio.h>`**: Includes the standard input/output library.

3. **`#include <stdlib.h>`**: Includes the standard library.

4. **`#include <sys/types.h>`**: Includes definitions for data types used in system calls.

5. **`#include <unistd.h>`**: Includes the header for UNIX standard functions.

6. **`int g = 0;`**: Declares a global variable `g`, initialized to 0.

7. **`void* myThreadFun(void* vargp)`**: Defines the function executed by each thread.

8. **`int myid = getpid();`**: Retrieves the process ID of the current thread.

9. **`static int s = 0;`**: Declares a static variable `s` that retains its value between function calls.

10. **`++s;`**: Increments the static variable `s` by 1.

11. **`++g;`**: Increments the global variable `g` by 1.

12. **`printf("Thread ID: %d, Static: %d, Global: %d\n", myid, ++s, ++g);`**: Prints the thread ID, the current value of the static variable `s`, and the current value of the global variable `g`. Note that `++s` and `++g` are incremented again when printed.

13. **`int main()`**: The main function where execution starts.

14. **`pthread_t tid;`**: Declares a thread identifier variable `tid`.

15. **`for (int i = 0; i < 3; i++)`**: A loop that runs three times to create three threads.

16. **`pthread_create(&tid, NULL, myThreadFun, NULL);`**: Creates a new thread that executes `myThreadFun`.

17. **`pthread_exit(NULL);`**: Waits for all threads to finish before exiting the program.

18. **`return 0;`**: Returns 0 from `main`, though this line is never reached because of the previous `pthread_exit`.

When compiled and executed, you may see output like this:

```bash
Thread ID: 1234, Static: 2, Global: 2
Thread ID: 1234, Static: 4, Global: 4
Thread ID: 1234, Static: 6, Global: 6
```

- Each thread will print its process ID, the static variable s, and the global variable g.
- All threads share the same global variable g, so it is incremented by each thread. The value shown is the count after all threads have executed, which may lead to confusion in interpretation.
- The static variable s is also shared across threads, and it keeps accumulating its value, but since it is static, each thread sees its own changes rather than a new instance.
  
### Important Note

Accessing global and static variables from multiple threads can lead to unpredictable results due to race conditions. If multiple threads modify these variables simultaneously, it can lead to incorrect values. In practice, synchronization mechanisms like mutexes are recommended to avoid these issues when threads need to share variables.

### Compiling the Program
To compile a multithreaded program using gcc, you need to link it with the Pthreads library. Use the following command:

bash
gfg@ubuntu:~/$ gcc multithread.c -lpthread
gfg@ubuntu:~/$ ./a.out
Before Thread
Printing GeeksQuiz from Thread 
After Thread
gfg@ubuntu:~/$


**Note**: This simple example shows how threads work. Accessing a global variable from multiple threads can be problematic. If one thread changes the variable while another is using it, it can lead to errors. In practice, if multiple threads need to access a global variable, it’s best to use a mutex to prevent conflicts.

**References**:  
For more information, check out [this Pthreads resource](http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html).
