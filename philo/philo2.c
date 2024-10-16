The dining philosophers problem is a very famous and interesting problem used to demonstrate the concept of deadlock.

To understand what the dining philosophers problem actually is, you can refer this blog:

The Dining Philosopher’s problem
The dining philosopher’s problem is a real life demonstration of the resource sharing problem in operating systems.
anushkaa5000.medium.com

Here, I am going to explain the solution to this problem using the concept of semaphores in C. Here’s the program:

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;
sem_t chopstick[5];

void * philosopher(void *);
void eat(int);
int main()
{
	int i,a[5];
	pthread_t tid[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&chopstick[i],0,1);
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
}

void * philosopher(void * num)
{
	int phil=*(int *)num;

	sem_wait(&room);
	printf("\nPhilosopher %d has entered room",phil);
	sem_wait(&chopstick[phil]);
	sem_wait(&chopstick[(phil+1)%5]);

	eat(phil);
	sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	sem_post(&chopstick[(phil+1)%5]);
	sem_post(&chopstick[phil]);
	sem_post(&room);
}

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
}
/* BY - ANUSHKA DESHPANDE */
Let us first understand what is a semaphore and why it is used.

Basically, semaphore is a special type of variable used to control the access to a shared resource.

The definition of semaphore is in the library semaphore.h .

There are many functions related to semaphores like sem_inti(), sem_wait(), sem_post(), etc. These functions are also defined under the semaphore.h library.

The data type of the semaphores is sem_t

There are two types of semaphores-:

Binary semaphore
Counting semaphore
The binary semaphore is used when there is only one instance of the resource whereas the counting semaphore is used when there are multiple instances of the resources.

In our program, we have used both types of semaphores.

sem_t room;
sem_t chopstick[5];
Here, the semaphore room is a counting semaphore since there is one dining room which can accommodate 4 philosophers. (i.e. Consider there are 4 chairs in the room and that is the resource. Hence there are multiple instances of the resource in the room. Therefore, room is a counting semaphore.)

sem_init(&room,0,4);
The function sem_init() is used to initialize the semaphore.

int sem_init(sem_t *sem, int pshared, unsigned int value);
The first parameter is the pointer to the declared semaphore.

The second parameter is pshared. If it is zero, the semaphore is shared between threads; else it is shared between processes. In our case it is zero meaning it is shared between threads.

The third parameter value is the value with which the semaphore is initialized.

Here, the semaphore room is initialized as 4 meaning it will vary between 0–3 and have 4 values.

Now, since there are 5 chopsticks, we have created 5 binary semaphores referring to the five chopsticks C0-C4.

for(i=0;i<5;i++)
		sem_init(&chopstick[i],0,1);
For the chopsticks, we have used binary semaphores since for every chopstick, C0-C4 we have only one instance of it.

So, according to our program, we have a scenario like:-


An empty room with 5 chopsticks and places for four philosophers.

In the program above, we have created threads.

pthread_t tid[5];
These threads refer to the 5 philosophers sitting around the table.

We have them as threads since we want these to execute simultaneously (i.e. we want multiple philosophers to eat at a time).

Now there can be a situation where all 5 threads start executing i.e. all 5 philosophers enter the room and cause deadlock. Hence, we are allowing 4 philosophers to enter the room first so that at least one of them can finish eating.

for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
We are calling the function philosopher() from pthread_create and passing it the address of an integer variable which refers to the philosopher number.

In the philosopher function,

void * philosopher(void * num)
{
	int phil=*(int *)num;

	sem_wait(&room);
	printf("\nPhilosopher %d has entered room",phil);
	sem_wait(&chopstick[phil]);
	sem_wait(&chopstick[(phil+1)%5]);

	eat(phil);
	sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	sem_post(&chopstick[(phil+1)%5]);
	sem_post(&chopstick[phil]);
	sem_post(&room);
}
we are first converting the number passed as a void * into integer.

Then we have called the sem_wait function which first checks if the resource is available and if it is available, the resource is allocated to the philosopher i.e. the semaphore is locked.

sem_wait(&room);
This being a counting semaphore, the prototype of sem_wait is:

struct semaphore {
      int count;
      queueType queue;
};
void sem_wait(semaphore s)
{
      s.count--;
      if(s.count<0)
      {
            /*place this process in s.queue */;
            /*block this process*/;      
      }
}
So here, the number of semaphores is decremented, meaning one of the semaphores is allocated. If all of the resources are allocated, the thread is placed on waiting queue.

Now, we apply sem_wait on chopsticks which are binary semaphores.

sem_wait(&chopstick[phil]);
sem_wait(&chopstick[(phil+1)%5]);
The definition of sem_wait for binary semaphores is:

struct binary_semaphore {
      enum {zero,one} value;
      queueType queue;
}
void sem_wait(binary_semaphore s)
{
      if(s.value == one)
           s.value = zero;
      else
      {
              /* place this process in s.queue */
              /* block this process */
      }
}
Here, according to the prototype, if the value of semaphore is one, it is changed to zero indicating that the semaphore is blocked.

In our case we are blocking the chopsticks towards the left and the right of the philosopher.

For example, for philosopher P0, we are blocking chopstick C0 and C4.

Then, we are allowing the philosophers to eat.

Finally, we are freeing the semaphores by calling the sem_post() function so that the other threads that are placed on the queue can use the resources.

The prototype for the sem_post() function is:

int sem_post(sem_t *sem);
If it returns a positive value, the semaphore is unlocked successfully.

For a binary semaphore, the sem_post() function works as:

void sem_post(semaphore s)
{
      if(s.queue is empty)
            s.value=one;
      else
      {
            /* remove a process P from s.queue */
            /* place process P on ready list */
      }
}
and for a counting semaphore, the sem_post() function is:

void sem_post(semaphore s)
{
      s.count++;
      if(s.count <= 0)
      {
            /* remove a process P from s.queue */
            /* place process P on ready list */
      }
}
Using the above functions, we free all the semaphores so that they can be used by other threads.

sem_post(&chopstick[(phil+1)%5]);
sem_post(&chopstick[phil]);
sem_post(&room);
The same thing happens for all 5 philosophers.

After all the 5 are done, we join the threads back to the main process.

for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
So, this is how we can implement the solution to the dining philosophers problem using semaphores.

At the end, you should get an output which looks like this:

Philosopher 4 has entered room
Philosopher 4 is eating
Philosopher 2 has entered room
Philosopher 2 is eating
Philosopher 3 has entered room
Philosopher 1 has entered room
Philosopher 2 has finished eating
Philosopher 4 has finished eating
Philosopher 3 is eating
Philosopher 1 is eating
Philosopher 0 has entered room
Philosopher 3 has finished eating
Philosopher 1 has finished eating
Philosopher 0 is eating
Philosopher 0 has finished eating
The sequence does not matter. It can be different on different machines.

The only thing is to make sure that all philosophers are entering the room, performing the eating operation and leaving the room and also that no two philosophers are using the same chopstick at the same time.

Do let me know if you face any problems and feel free to leave a feedback.

Hope this helps you!