#include "uart.h"

void uart_init() {
  UBRR0H = (BAUDRATE >> 8);
  UBRR0L = (BAUDRATE);
  UCSR0A &= ~(_BV(U2X0));
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);  // 8-bit data
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);    // Enable RX and TX
}

void uart_putchar(char c) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;  // Wait while register is free
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
