#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED 4

typedef enum{
    IDLE, HEATING, PAUSED
} microwaveState;

volatile microwaveState currentState = 0;
volatile uint8_t overflow_counter = 0;
volatile uint8_t secondsLeft = 0;

void timer(){
    TCCR0B |= _BV(CS02) | _BV(CS00);
    TIMSK0 |= _BV(TOIE0);
}
ISR(TIMER0_OVF_vect){
    overflow_counter++;
    if(overflow_counter >= 61){
        overflow_counter = 0;
        if(currentState == HEATING){
            if(secondsLeft > 0){
                secondsLeft--;
            }else{         
                currentState = IDLE;
            } 
        }
        if(currentState == PAUSED){
            PORTD ^= _BV(LED);
        }
    }
}
ISR(INT0_vect){
    currentState = HEATING;
    secondsLeft += 30;
}
ISR(INT1_vect){
    if(currentState == HEATING){
        currentState = PAUSED;
    }else{
        currentState = IDLE;
        secondsLeft = 0;
    }
}

int main() {
    DDRD |= _BV(LED);
    PORTD |= _BV(2) | _BV(3);

    EICRA |= _BV(ISC01) | _BV(ISC11);
    EIMSK |= _BV(INT0) | _BV(INT1);
    timer();
    sei();

    while(1){
        switch(currentState){
            case IDLE:
            PORTD &= ~_BV(LED);
            break;
            case HEATING:
            PORTD |= _BV(LED);
            break;
            case PAUSED:
            break;
        }
    }
}
