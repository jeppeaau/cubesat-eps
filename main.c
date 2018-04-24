#include "krnl.h"
#include <util/delay.h>
#include <avr/io.h>    


// A small krnl program with two independent tasks

struct k_t *pt1, // pointer to hold reference
  *pt2;          // to taskdescriptor for t1 and t2  
 
char s1[200]; // stak for task t1
char s2[200]; // stak for task t2
 
void t1(void)
{
  // a task must have an endless loop
  // if you end and leave the task function - a crash will occur!!
  // so this loop is the code body for task 1


  DDRB    |= ((1 << DDB5));
  while (1) 
  {  
    PORTB ^= ((1 <<  PB5));
    _delay_ms (500); 
  }               
}

void t2(void)
{
  // and task body for task 2
  // runs independent of task t1
  DDRB    |= ((1 << DDB4));
  while (1) 
  {  
    PORTB ^= ((1 <<  PB4));
    _delay_ms (500);  
  }  
}

void main()
{

  // init krnl so you can create 2 tasks, no semaphores and no message queues
  k_init(2,0,0); 

// two task are created
//               |------------ function used for body code for task
//               |  |--------- priority (lower number= higher prio
//               |  | |------- array used for stak for task 
//               |  | |   |--- staksize for array s1

  pt1=k_crt_task(t1,11,s1,200); 
  pt2=k_crt_task(t2,11,s2,200);
  
  
  // NB-1 remember an Arduino has only 2-8 kByte RAM
  // NB-2 remember that stak is used in function calls for
  //  - return address
  //  - registers stakked
  //  - local variabels in a function
  //  So having 200 Bytes of stak excludes a local variable like ...
  //    int arr[400];  
  // krnl call k_unused_stak returns size of unused stak
  // Both task has same priority so krnl will shift between the
  // tasks every 10 milli second (speed set in k_start)

  k_start(1); // start kernel with tick speed 1 milli seconds
}
