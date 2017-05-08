#include <inttypes.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "buffer.h"
#include "state.h"
#include "config.h"

#ifndef F_CPU
#error "F_CPU not defined"
#endif

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr);

volatile struct byteBuffer buffer;
struct state state = { 0 };

void state_initial(struct state *state);
void state_pickMotor(struct state *state);
void state_pickNumerator(struct state *state);
void state_pickDenominator(struct state *state);
void state_running(struct state *state);

void uart_putchar(char c) {
        loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
        UDR0 = c;
}


int
main (void)
{
        init(&buffer);
        USART_Init(MYUBRR);
        UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)
        sei();
        state.next = state_initial;
        while(true) {
                for(; state.next; ) {
                        state.next(&state);
                }
                sleep_mode();
        }
}

ISR (USART_RX_vect )
{
        char ReceivedByte;
        ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
        push(&buffer, ReceivedByte);
}

void
USART_Init( unsigned int ubrr)
{
        /*Set baud rate */
        UBRR0H = (unsigned char)(ubrr>>8);
        UBRR0L = (unsigned char)ubrr;
        /*        Enable receiver and transmitter */
        UCSR0B = (1<<RXEN0)|(1<<TXEN0);
        /* Set frame format: 8data, 2stop bit */
        UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


void
state_initial(struct state *state)
{
        if (isEmpty(&buffer)) {

                return;
        }

        uint8_t command;
        if (pop(&buffer, &command)) {
                switch (command) {
                case 1:
                        setNextState(state_pickMotor);
                        break;
                case 2:
                        setNextState(state_running);
                        break;

                }
        }

}

void
state_pickMotor(struct state *state)
{
        if (isEmpty(&buffer)) {
                return;
        }

        uint8_t motor;
        pop(&buffer, &motor);
        statePush(motor);
        setNextState(state_pickNumerator);


        //      uart_putchar('m'); uart_putchar(motor); uart_putchar('\n');
}

void state_pickNumerator(struct state *state){
        if (isEmpty(&buffer)) {
                return;
        }

        uint8_t n;
        pop(&buffer, &n);
        statePush(n);
        setNextState(state_pickDenominator);

//        uart_putchar('n'); uart_putchar(n); uart_putchar('\n');
}

void state_pickDenominator(struct state *state){
        if (isEmpty(&buffer)) {
                return;
        }
        uint8_t m, n, d;

        pop(&buffer, &d);
        statePop(&n);
        statePop(&m);

        setMotorTimer(m, n, d);
        setNextState(state_initial);

        uart_putchar('m'); uart_putchar(m);

        uart_putchar('n'); uart_putchar(n);

        uart_putchar('d'); uart_putchar(d);

        uart_putchar('!');
}


void state_running(struct state *state)
{
        //TODO: start running
}
