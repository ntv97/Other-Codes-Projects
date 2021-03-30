##  Project 2 ##

**Introduction**
In this project, we worked with scheduling threads and learned about 
synchonization. We implemented a queue which becomes handy for the later phases
to hold the threads while they wait to be scheduled. We get to see how threads
get scheduled nonpreemptive in phase 2 and then preemptive in phase 4. We also
saw how semaphores work in threads in phase 3.   


**Queue Implementation**
	The motivation for implementing our queue is revolved around the 
requirement of the operations being O(1). Originally, we had the idea of having
just one struct to represent our queue and a pointer as part of the queue
always pointing to the head. We realized that this did not fulfill the time
complexity requirement because each time we need to add an item, the queue 
would iterate through the nodes and that would result in O(n) time. So we 
decided to have a node object linked list where each node held a data item and
a queue object with a length and a head pointing to the head of the node and a
tail pointing to the last node. This meets the time complexity because each
time we need to enqueue, the tail only needs to move to the next node and
the initialize the data. And each time we need to dequeue the head already 
points to the oldest element and it just needs to return the item and remove 
it. These operations are O(1). Essentially, the head become very useful in the 
later phases when we want to get the oldest thread in the ready queue and 
the tail makes it possible to add new threads to the appropriate queue. 
The functions for the queue are very typical to what we learn in data 
structures class. 
	For our queue tester in addition to the two tests provided for 
us, we created some tests to check if the enqueue, dequeue, iteration, delete,
and destroy works. The resuse test is to check if we can successfully enqueue
all the data item into the queue without erorrs and in the correct order, and
the dequeue makes sure we can get and remove all items, then enqueue everything
again. We check if this worked by asserting its length. The test iter function
tests the queue iter function by passing in the inc_item function. The test 
shows it works for the first element with the assert statement but we can also
check by iterating the print function on the queue. In test_delete,
we test to see if the queue is able to remove the first, middle, and last
element and it did. We can test to see if the queue's destroy function work 
because the function always dequeues all the elements and makes sure its safe 
to destroy it. If we remove the dequeue statement and try to destroy an empty 
queue, it would not work just like how the assignment is designed.


**Uthread**
	To represent our threads, we have a struct object with a state, 
context, and stack. We use an 'enum' type to represent the state of each thread
rather than a character array or string because the space complexity is more
favorable. We have two global static queues, one for the threads ready to run
and one for the threads that have exited. The last static global variables we
have is for the currently running thread. We declare these variables static 
because we want to restrict access to these data specifically to this file
and since most function require access to these data, making them global makes
things simpler. Since the current thread is static, the 'uthread_current()'
allows us to get the current running thread when we need it in 'sem.c'.
	After we create the first thread, the idle thread, and threads start
yielding, more and more threads are being created and pushed into the ready
queue to be scheduled to run. In our 'uthread_yield' function we get the oldest
thread in the ready queue to be the current thread, switch its state from ready
to running, and put the previous thread into ready state and back into the 
ready queue if its state was running before. Then we context switch between the
previous and current threads. There are two other functions that require
context switching, 'uthread_exit' and 'uthread_block'. When a thread exits or
block, we change its state and call 'uthread_yield' and inside uthread yield
if the thread's state is exit, it will be put into the exited_q where it will
be deallocated. If a thread is blocked, we already enqueued it into the queue
of our semaphore in phase 3 so it only context switch with the next current 
thread inside the yield function. The three functions essentially have the same
goal, except determining what queue it needs to be returned to in order to 
decide what happens to it is different. These differences is handled by the if
statements inside the yield function.
	Threads inside the exited_q occasionally get cleaned (deallocate their
parts) inside the idle loop in the 'uthread_start' function where there is a
continuous alternating between yielding and cleaning the zombie threads in
the exited queue. At the end of the while loop of yielding and cleaning zombie
threads, we have another while loop to make sure all the threads inside the
exited_q gets deallocated. It is very possible that when the ready queue is 
empty, that there are still exited threads remaining in its queue and having
this while loop takes care of it.
	One notable thing to note in this uthread file is that for many 
functions, such as yield, we call preempt_disable in the beginning, is because
in these circumstances it is critical that an interrupt does not occur because
then we'll have some data races. In the yield function, it's important to
disable the interrupt because if a thread is in the middle of context switching
and gets an interrupt then one of the thread might of never gotten the chance
to run. This is bad as we wish to have all threads run in a round robin manner.
Also in the exit function, if we we allowed timer interrupts then the thread 
running would not reach the point for it to get enqueued inside the exit queue
and we would have memory leak. The same concept goes for the creating threads
function in which disabling interrupts is very important to ensure all threads
get created. We didn't disable the interrupt at the beginning of the
'zombie_thread', 'uthread_block', and 'uthread_unblock' because they were 
called on functions that already disabled it. Disabling interrupts in these
functions is important because we would not want any hypothetical race 
conditions.


**Semaphore**
	Our implementation of the Semaphore API was quite straightforward, 
given the detailing on the prompt. We gave each semaphore a count (the basic
 metric for a semaphore) and a queue of threads (in order to associate which
blocked threads correlated with a particular semaphore). We must be able to 
identify which threads correspond to a specific semaphore in order to 
accurately unblock the correct thread for the scheduler. If not, the semaphores
will inadvertently unblock the wrong threads and the API will fail. 
	The implementations of sem_down and sem_up follow according to the 
typical natures of semaphores. In sem_down if the sem count is 0, then we'll 
enqueue the current thread into the block queue and call 'uthread_block' 
where the thread swithces its state state and call the yield function to take 
care of the context switching with the next ready thread. In sem_up, since the 
lock is released, the threads that were blocked and enqueued inside the blocked
queue can finally get dequeued and go into the unblock function where it will
become a ready thread, get put back into the ready queue so it can be scheduled
to run when it's turn comes. We disable preemption here so the thats why the 
block and unblock functions in uthread doesn't need to disable it also. 
	

**Preemption**
	In 'preempt.c' we chose to have global variables again because they
were used by several functions. We developed our preemption API by considering 
the objective at hand; dealing with uncooperative threads. With the utilization
of signal handling and a timer, we were able to develop a functioning API which
would yield every 10ms. One notable design construct in preempt.c was that we 
adjusted the input into our timer to account for the change into ms from s, as 
well as considering the HZ we worked at and using T = 1 / f. 
	Our preemption tester verifies the integrity of our preempt.c 
implementation. By creating an infinite loop in the thread without any explicit
calls to yield, the thread will run continuously given no pre-emption.  
However, the scheduler is able to switch from thread 1 to thread 2 and prevent
the starvation of resources. Thread 2 was able to run because of the timer
interrupt and that was able to show that our preempt.c program worked. 


**Limitations** 
	We had some trouble with freeing the memory while working with the 
queue. In our queue_delete function, before we used the free call, we called 
the memset function. We are aware that this seems unnecessary as we're adding 
in additional operations, however, if we remove the memset statements, we get a 
segfault. We tried working around this for a while and couldn't resolve it. If
we remove both memset and free, then the queue function would still work fine, 
however, it would leak memory and we didn't want that.  
	Some of our other limitations lies in 'uthread.c' in the 
'uthread_start' function. The first is that we allocated a queue for the exited
thread and maybe this is a waste of space when they can be deallocated 
immediately. We tried to call a function to deallocate memory for the exited 
threads in the yied function if the thread's state is exited, however, we also 
were getting segfaults for that idea. The final limitation is that as you can 
see we call the 'zombie_thread' in two different while loops. This is a little
redudant, however, we wanted the idle loop to do some cleaning of the zombie
thread once in a while but then we realized that when there are no more threads
scheduled to run, there may still be zombie threads left and that needs to
be taken care of before we destroy the queues. 


**Sources**
Lecture materials/sources and the links given in the homework prompt. 
