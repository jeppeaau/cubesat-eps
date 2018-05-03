#include "krnl.h"
#include <util/delay.h>
#include <avr/io.h>
#include "ina219.h"
#include "tmp101.h"
#include "stm.h"
#include "task.h"
#include <avr/eeprom.h>


#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)


// A small krnl program with two independent tasks

struct k_t *pt1, // pointer to hold reference
  *pt2;          // to taskdescriptor for t1 and t2

char state_logic_stak[200]; // stak for task t1
char s2[200]; // stak for task t2



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

int main()
{
  antenna_launch = 

  if(antenna_launch == 1 || total_bootcount == 0)
  {
    global_bootcount = bootcount(1);
  }
  else
  {
    i2c_init();

    // init krnl so you can create 2 tasks, no semaphores and no message queues
    k_init(2,0,0);


  // two task are created
  //               |------------ function used for body code for task
  //               |         |--------- priority (lower number= higher prio
  //               |         |       |------- array used for stak for task
  //               |         |       |            |--- staksize for array s1

  pt1=k_crt_task(state_logic,11,state_logic_stak,200);
  pt2=k_crt_task(t2,11,s2,200);

    k_start(1); // start kernel with tick speed 1 milli seconds

    return 0;
  }  
}
