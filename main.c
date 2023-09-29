#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)

#define LED_PIN 6

#define BUTTON_PIN 2

volatile double dutyCycle = 95;
ISR(TIMER0_OVF_vect){
}

void checkAndHandleInput() {
    if (BIT_CHECK(PIND, BUTTON_PIN) == 0) {  // Check if the button is pressed (Low when pressed if pulled-up)
        _delay_ms(50);  // Debounce delay
        if (BIT_CHECK(PIND, BUTTON_PIN) == 0) {  // Double check if still pressed
            dutyCycle += 10;
            if (dutyCycle > 100)
                dutyCycle = 5;
            OCR0A = (dutyCycle/100)*255;  // Update the PWM duty cycle
            while(BIT_CHECK(PIND, BUTTON_PIN) == 0);  // Wait for button release to avoid repeated triggers
        }
    }
}

//I dont clear it - CTC
int main(){

    BIT_SET(DDRD, LED_PIN);  // Set led_pin to output mode
    BIT_CLEAR(DDRD, BUTTON_PIN);  // Set BUTTON_PIN to input mode
    BIT_SET(PORTD, BUTTON_PIN);  // Enable internal pull-up resistor for BUTTON_PIN

 
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    OCR0A = (dutyCycle/100)*255;
    sei();

    TCCR0B = (1 << CS00);

    while(1){
        //Check input
        checkAndHandleInput();
        _delay_ms(100);
    }

    return 0;
}

