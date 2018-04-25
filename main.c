#include "krnl.h"
#include <util/delay.h>
#include <avr/io.h>    
#include "ina219.h"


#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)


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


void uart_init() {
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = (BAUDRATE);
    UCSR0A &= ~(_BV(U2X0));
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8-bit data
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // Enable RX and TX
}

void uart_putchar(char c) {
    while (!(UCSR0A & (1 << UDRE0)))
        ; // Wait while register is free
    UDR0 = c;
}

void print_value(uint8_t val) {
  switch (val) {
      case 0:
        uart_putchar('0');
        break;
      case 1:
        uart_putchar('1');
        break;
      case 2:
        uart_putchar('2');
        break;
      case 3:
        uart_putchar('3');
        break;
      case 4:
        uart_putchar('4');
        break;
      case 5:
        uart_putchar('5');
        break;
      case 6:
        uart_putchar('6');
        break;
      case 7:
        uart_putchar('7');
        break;
      case 8:
        uart_putchar('8');
        break;
      case 9:
        uart_putchar('9');
        break;
      case 0x0A:
        uart_putchar('A');
        break;
      case 0x0B:
        uart_putchar('B');
        break;
      case 0x0C:
        uart_putchar('C');
        break;
      case 0x0D:
        uart_putchar('D');
        break;
      case 0x0E:
        uart_putchar('E');
        break;
      case 0x0F:
        uart_putchar('F');
        break;
    }
}

void main()
{
  uint16_t cal = 29826;
  uint16_t addr = 0x40;
  uint16_t voltage;

  uart_init();
  i2c_init();
  configuration(391, addr);
  calibrate(cal, addr);
  int i;

  _delay_ms(100);

  voltage = read_voltage_mV(addr);
  
  _delay_ms(10);

  print_value((voltage >> 8) & 0x0F);
  print_value((voltage >> 4) & 0x0F);
  print_value(voltage & 0x0F);
  uart_putchar('\n');

  // init krnl so you can create 2 tasks, no semaphores and no message queues
  //k_init(2,0,0); 

// two task are created
//               |------------ function used for body code for task
//               |  |--------- priority (lower number= higher prio
//               |  | |------- array used for stak for task 
//               |  | |   |--- staksize for array s1

  //pt1=k_crt_task(t1,11,s1,200); 
  //pt2=k_crt_task(t2,11,s2,200);
  
  
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

  //k_start(1); // start kernel with tick speed 1 milli seconds
}
