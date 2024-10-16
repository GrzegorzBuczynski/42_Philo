
https://medium.com/@jalal92/the-dining-philosophers-7157cc05315


I explained the main ideas in my playlist, probably you come from there.

This is all the threads theory I used to code. If race-condition & deadlock are “..Hu..!?” words, have a look ^^

Let’s discuss threads, grab a coffee
Threads aren’t just theoretical constructs — they have tangible benefits that can be witnessed in real-world…
medium.com

Deadlocks
Aka Mexican Standoffs
medium.com

Here I wanna dig a little into some specific functions:


There are indeed important considerations about details to be made.

pthread_join

prototype
The pthread_join() function serves a dual purpose: synchronization and cleanup.

1. Synchronization:
At its core, pthread_join() is a synchronization primitive. When you call pthread_join(tid, &result), the calling thread will be blocked until the thread with ID tid completes its execution. This allows for structured coordination between threads, ensuring that the main thread (or any other thread) can wait for another thread to finish its work.

2. Cleanup:
Beyond synchronization, pthread_join() performs an essential cleanup role. When a thread completes its execution, it doesn't simply vanish. Instead, the system keeps some metadata about that thread.

Reclaiming Stack Memory: Every thread has its own stack memory, which it uses to store local variables, function call information, and more. When the thread is done, this memory can be reclaimed, but the system won’t do so until another thread acknowledges the thread’s termination. pthread_join() serves this role.
Fetching Return Value: If the thread was terminated with pthread_exit() or just returned, it might have produced a result. This result is stored, and pthread_join() allows another thread to fetch this result. If the result isn't fetched, it might be leaked.
Releasing Internal Resources: The pthreads library might allocate other internal resources for thread management. Calling pthread_join() ensures that these resources are also released.
If a thread isn’t joined or detached (pthread_detach()), these resources can linger, leading to a resource leak. You can think of joining as a handshake between the finished thread and another thread. The finished thread says, "I'm done, here's what I found out" and the other thread responds with, "Got it, thanks for letting me know." Until this handshake occurs, the system retains resources in case they're needed.

TL;DR while the act of joining threads is about synchronization, the broader role of pthread_join() includes cleaning up the system's and the pthread library's resources associated with the finished thread.

Try the code with valgrind, toggling the pthread_join()

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void* thread_func(void* arg) 
{
    printf("Hello from the thread!\n");
    return NULL;
}

int main() 
{
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, thread_func, NULL) != 0) 
    {
        perror("Failed to create thread");
        return 1;
    }

    // Give the thread some time to execute.
    sleep(2);

    // 🚨🚨 Uncomment the following line to reclaim resources of the thread, 
    // preventing the leak.🚨🚨
    pthread_join(thread_id, NULL);

    printf("Exiting main function.\n");
    return 0;
}
Without pthread_join()


With pthread_join()



🐇 Rabbit hole alert 🚨
Pthread_Join() Function in C Language with Single and Multiple Thread Examples
Guide on the pthread library of POSIX standard to increase the speed of the finished program by executing multiple…
linuxhint.com

pthread_detach

At its core, pthread_detach() is like telling the system

"Hey, once this particular thread finishes its job, you can immediately free up any resources it used."

This is handy because you might not always want to manually check and reclaim resources every time a thread concludes its task. With pthread_detach(), you set a thread to 'auto-clean' mode. If the thread has already completed its execution by the time you call this function, the system will promptly reclaim its resources.

Having understood pthread_detach(), it's natural to wonder how it differs from its counterpart, pthread_join(). Imagine you've sent out multiple agents (threads) on different missions. Once an agent completes their mission, you might want to debrief them personally, understand their findings, and then dismiss them. This process of debriefing and dismissal is akin to pthread_join(). When you join a thread, you wait for it to finish, possibly collect any results it offers, and then free up its resources. It's a manual and involved process, ensuring that nothing goes unnoticed.

On the other hand, with pthread_detach(), you're essentially saying,

"Once you're done with your mission, you're free to go; no need to report back."

The most important thing though is that the main thread does not have to wait! Indeed it is not blocked by pthread_join().

Launch this code toggling the functions, with detached threads the main goes on!

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // for sleep

// This function will be executed by the detached thread
void* print_in_background(void* arg)
{
    printf("This is printed from the thread.\n");
    sleep(5);
    return NULL;
}

int main() {
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, print_in_background, NULL) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }

    // 🚨 toggle these 2 🚨
    pthread_detach(thread_id);
//    pthread_join(thread_id, NULL);

    // Continue with the main thread's work
    printf("This is printed from the main thread.\n");
    usleep(100000);

    return 0;
}
pthread_detach() and pthread_join() are two sides of the same coin, both aiding in the proper management of thread resources but with distinct approaches. While pthread_join() involves waiting for the thread, retrieving its results, and then cleaning up, pthread_detach() sets the thread to automatically clean up after itself once it's done. Deciding between them is a matter of understanding the needs of your program and the level of involvement you desire in the thread cleanup process.


I highly suggest his playlist on threads!
gettimeofday

All you need to know
How much time does it take to measure the time?
i.e., How much the act of measuring influences the measurement itself?

#include <stdio.h>
#include <sys/time.h>  // This includes the declaration for gettimeofday
#include <time.h>
#include <unistd.h>

#define NUM_CALLS 100
#define BOLD "\033[1m"
#define GOLD "\033[0;33m"
#define RESET "\033[0m"

void foo(void) {
    // Empty function
}

int main(void)
{
    struct timespec start_ts, end_ts;
    double elapsed_usleep_us, elapsed_usleep_ns;
    double elapsed_gettimeofday_us, elapsed_gettimeofday_ns;
    double elapsed_foo_us, elapsed_foo_ns;

    // Measure usleep
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    for (int i = 0; i < NUM_CALLS; i++)
        usleep(0);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_usleep_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_usleep_us = elapsed_usleep_ns / 1e3;

    // Measure gettimeofday
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    struct timeval tmp;
    for (int i = 0; i < NUM_CALLS; i++)
        gettimeofday(&tmp, NULL);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_gettimeofday_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_gettimeofday_us = elapsed_gettimeofday_ns / 1e3;

    // Measure foo
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    for (int i = 0; i < NUM_CALLS; i++)
        foo();
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_foo_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_foo_us = elapsed_foo_ns / 1e3;

    printf("Time for %d calls to usleep(0):\t\t" BOLD "%.0f microseconds %.0f ns\n" RESET,
           NUM_CALLS, elapsed_usleep_us, elapsed_usleep_ns);
    printf("Time for %d calls to gettimeofday():\t\t" BOLD "%.0f microseconds\t %.0fns\n" RESET,
           NUM_CALLS, elapsed_gettimeofday_us, elapsed_gettimeofday_ns);
    printf("Time for %d calls to foo():\t\t\t" BOLD "%.0f microseconds\t%.0f ns\n\n" RESET,
           NUM_CALLS, elapsed_foo_us, elapsed_foo_ns);

    return 0;
}
foo( ): This is a simple user-space function that does nothing. Invoking this function is essentially just a jump to the function’s address followed by an immediate return. The overhead is minimal since it’s just a few processor instructions without any memory accesses, system calls, or other complex operations.
gettimeofday( ): gettimeofday( ) doesn’t involve a traditional user-to-kernel mode switch in modern systems (thanks to vDSO virtual dynamic shared object), but it still does more than the foo function accessing some shared memory maintained by the kernel. Thus, its overhead is higher than a simple function call like foo(), but still much lower than a traditional syscall.
Proof

Launch this code in Linux, and you will see that the address of the gettimeofday falls exactly in the vDSO area.



usleep(0): This involves a full system call, with the associated user-to-kernel mode switch. Even though you’re asking it to sleep for zero microseconds, the overhead isn’t in the sleep itself but in the mechanism to perform the sleep. The system call overhead involves saving the state of the current process, switching to kernel mode, handling the request, then restoring the process’s state and switching back to user mode.
run the code -> while true; ./test; end

gettimeofday is much faster than usleep, even though both are sys calls
🐇 hole🐇

clock_gettime
Does gettimeofday() on macOS use a system call?
I expect that gettimeofday() will call a system call to do the work of actually getting the time. However, running the…
stackoverflow.com


Low Level explanation
How does the gettimeofday syscall wor‍k?
gettimeofday is a syscall of x86–86 according to this page(just search gettimeofday in the box): int…
stackoverflow.com

Two frequently used system calls are ~77% slower on AWS EC2 | Packagecloud Blog
This article reveals the stats that show two frequently used system calls are 77% slower on AWS EC2 and its causes.
blog.packagecloud.io

https://www.baeldung.com/linux/vdso-vsyscall-memory-regions

The usleep Function in Depth
The usleep function, *as its name implies, allows for microsecond resolution pauses in a program. However, there are caveats and considerations one must take into account when using this function.

*”u” isn’t the standard symbol for “micro.” The correct symbol for “micro” is the Greek letter mu (µ). However, in many computer systems and programming contexts, it’s common to see the “u” character used as a substitute for “µ”, especially when the latter might be difficult or inconvenient to type or display.

How does usleep work?
When you invoke usleep, the calling thread (i.e., the sequence of commands being executed in your program) is told to pause or "sleep" for the specified duration. However, the actual sleep duration might be longer than requested due to various factors:

System Load & Scheduler: Sleep functions don’t guarantee precise wake-up times. They guarantee a minimum sleep time. The operating system’s scheduler will not interrupt another running process to resume your sleeping thread exactly wh. If the system is busy with other tasks, it might delay the resumption of your process slightly.
Time Spent Processing the Call: Before the system can process the sleep request, it needs to handle the system call’s overhead, which might add some microseconds or even milliseconds to the actual sleep duration. We saw previously this.

Granularity of System Timers: The timers used by operating systems aren’t infinitely precise. They have a specific granularity or resolution, which can affect the accuracy of your sleep duration.
You got the point. usleep does not have absolute precision.

and so…?
Unpredictability: As mentioned, the actual sleep duration might be longer than requested. Fine tuning the synchronization will be not assured.

When should you use usleep?
For rudimentary thread or process synchronization, although there are far better mechanisms like mutexes, semaphores, or condition variables for this purpose.

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// Define ANSI escape sequences for colors and styles
#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

int main()
{
    struct timeval start, end;

    gettimeofday(&start, NULL); // Get the current time before sleeping
    usleep(500000);  // Expected sleep: 500 milliseconds (0.5 seconds)
    gettimeofday(&end, NULL);  // Get the time after sleeping

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;

    double elapsedMilliseconds = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Expected sleep duration: "BOLD_CYAN"\t500 milliseconds\n"RESET);
    printf("Actual sleep duration: "BOLD_CYAN"\t\t%.2f milliseconds\n\n"RESET, elapsedMilliseconds);

    return 0;
}
Randomness. Run this code multiple times you’ll see delays. Even 5ms which in CPU land is a lot! (if you run the code longer, even worse delays!)


We are in the peaceful hands of Kali goddess with this usleep.


Precision vs. Accuracy

It’s important to distinguish between precision (how detailed the measurement is) and accuracy (how close the measurement is to the actual value). For many applications, usleep( ) provides sufficient precision. It is consistently inconsistent (even though I can stumble upon black swan where the inconsistency may be big).

“Precision hits the same spot, accuracy hits the right spot”

Solution : Custom usleep
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define BOLD_RED "\033[1;31m"
#define RESET    "\033[0m"

long get_elapsed_time_microseconds(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void precise_usleep(long usec) {
    struct timeval start, current;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    do {
        gettimeofday(&current, NULL);
        elapsed = get_elapsed_time_microseconds(start, current);
        rem = usec - elapsed;

        if (rem > 1000) 
            usleep(rem / 2);
        
    } while (elapsed < usec);
}

int main(void) 
{
    struct timeval start;
    struct timeval end;
    long seconds;
    long microseconds;
    double elapsed;

    gettimeofday(&start, NULL);
    precise_usleep(500000);
    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    
    printf("Expected sleep duration: "BOLD_RED"\t0.5"RESET" seconds\n");
    printf("Actual sleep duration: "BOLD_RED"\t\t%f"RESET" seconds\n\n", elapsed);
    return (0);
}


Pretty darn precise.
The usleep function uses the gettimeofday function to measure the current time before and during a while loop. It then calculates the elapsed time. If elapsed is > than a threshold (in this case 1000), simply call usleep for half the time. On the contrary, keep looping. This is a Hybrid implementation usleep-busy wait to optimize CPU workload.

💡I usleep the majority of the time and then I busy wait the last microseconds to get a refined control💡

Mutexes VS Spinlocks: Choosing the Right Locking Mechanism
Mutex: When a thread tries to acquire a mutex and it’s unavailable, the thread is put to sleep. It wakes up when the…
medium.com

Why do the custom usleep is more Precise?
The custom usleep function, which uses a both usleep and busy-wait or spin-wait, tends to be more precise than usleep for several reasons, even though neither offers absolute precision.

Active Monitoring:
precise_usleep actively monitors the elapsed time, if under a threshold, doesn't release the CPU spin locking. It's continually checking the time and comparing it to the desired sleep duration.
In contrast, usleep requests the OS to suspend the thread for a specific duration, and it depends on the OS scheduler to wake it up after that time. The OS might not resume execution of the thread immediately after the specified time due to various reasons, such as other higher-priority tasks being scheduled.
OS Sleep Mechanisms:
OS-based sleep mechanisms like usleep might round up the sleep time to the nearest scheduling quantum or timer tick. For instance, if the OS scheduler operates in 10ms quanta, asking it to sleep for 5ms might result in sleeping for 10ms.
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define USECREQ 250
#define LOOPS 1000

void event_handler(int signum)
{
    static unsigned long cnt = 0;
    static struct timeval tsFirst;
    if (cnt == 0)
    {
        gettimeofday(&tsFirst, 0);
    }
    cnt++;
    if (cnt >= LOOPS)
    {
        struct timeval tsNow;
        struct timeval diff;
        setitimer(ITIMER_REAL, NULL, NULL);
        gettimeofday(&tsNow, 0);
        timersub(&tsNow, &tsFirst, &diff);
        unsigned long long udiff = (diff.tv_sec * 1000000) + diff.tv_usec;
        double delta = (double)(udiff / cnt) / 1000000;
        int hz = (unsigned)(1.0 / delta);
        printf("Estimated frequency:\n");
        printf("- Hertz: %d Hz", hz);
        printf("\n- Milliseconds: %.3f ms", 1000.0 * delta);
        printf("\n- Seconds: %.6f s\n", delta);
        exit(0);
    }
}

int main(int argc, char **argv)
{
    struct sigaction sa;
    struct itimerval timer;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &event_handler;
    sigaction(SIGALRM, &sa, NULL);
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = USECREQ;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = USECREQ;
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1) ;
}
Linux VM, i have one tick every ~0.3 milliseconds.


In my macOS, i have one tick every ~0.2 milliseconds.


TL;DR rule:

“Typical operating system configures time interval to be anywhere between 1 to 10 milliseconds. This means ticks per sec is usually 100 to 1000” quote

Now, let’s discuss in practice a usleep(600000) call. The usleep function takes an argument in microseconds, so usleep(600000) requests a sleep of 600 ms.

Here’s the explanation with respect to rounding:

Given the tick rate of 0.249 ms:

When your process makes the usleep(600000) call, it's effectively telling the operating system: "Please pause my execution for 600 milliseconds."
However, the OS scheduler operates based on its tick rate, which in my case is every 0.249 ms.
The scheduler doesn’t have the granularity to wake up the process exactly at 600 ms, so it will wake up the process on the next tick after the 600 ms duration has passed.
Given the 0.249 ms tick, the actual wake-up might be slightly after the 600 ms mark, but no more than one tick's duration later. The worst-case scenario is that your process will sleep for 600 ms + 0.249 ms = 600.249 ms.
It’s worth noting that this explanation simplifies a few details. Modern operating systems and CPUs have additional mechanisms to handle short sleep durations with better accuracy than just relying on the scheduler’s tick rate. For example, there might be high-resolution timers that can provide more precise sleeping durations. Still, for the purposes of this explanation, the round-up behavior described above gives you an idea of the effects of the OS tick rate on sleep durations.

This round-up thing, probably, won’t influence sleep values. Just ponder the crazy amount of details to take care to derive conclusions.

🚨Trade-offs 🚨:
The precision of precise_usleep comes at a slight higher CPU utilization. Since under a treshold, the CPU is continuously polling in the busy-wait loop, it's using computational resources that might be better allocated elsewhere, especially on systems with other demanding tasks.
Preemption is still possible. While the function is more predictable than usleep, it's not immune to interruptions from the scheduler, especially on a system with high load or many concurrent processes.
In essence, while neither function provides absolute real-time guarantees, the busy-wait hybrid approach in precise_usleep tends to be more consistent and predictable for short durations compared to traditional sleep mechanisms like usleep. But the choice between them should be made based on the specific requirements and constraints of the application.