## Imp point:
User-level threads requires non-blocking systems call i.e., a multithreaded kernel. Otherwise, entire process will blocked in the kernel, even if there are runable threads left in the processes. For example, if one thread causes a page fault, the process blocks.

awesome link to study thread: https://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/threads.htm
