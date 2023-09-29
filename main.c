#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


// Macro definitions for bitwise operations on ports and pins.
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)

// Define LED_PIN as pin 6 on PORTD (digital pins 0 to 7 on Arduino)
#define LED_PIN 6

// Define BUTTON_PIN as pin 2 on PORTD
#define BUTTON_PIN 2

// Define a global volatile variable for dutyCycle of the PWM.
volatile double dutyCycle = 95;
ISR(TIMER0_OVF_vect){
}

// Function to check the status of the button and adjust the duty cycle of the LED accordingly.
void checkAndHandleInput() {
    if (BIT_CHECK(PIND, BUTTON_PIN) == 0) {  // Check if the button is pressed (Low when pressed if pulled-up)
        _delay_ms(50);  // Debounce delay
        if (BIT_CHECK(PIND, BUTTON_PIN) == 0) {  // Double check if still pressed
            dutyCycle += 10; // Increase the duty cycle by 10%.
            if (dutyCycle > 100)
                dutyCycle = 5; // Reset duty cycle to 5% if it exceeds 100%.
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

    // PWM configuration using Timer0 in Fast PWM mode.
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);  // Set up Timer0 in Fast PWM mode.
    TIMSK0 = (1 << TOIE0);  // Enable Timer0 overflow interrupt.
    OCR0A = (dutyCycle/100)*255;  // Set initial PWM value.
    sei();  // Enable global interrupts.

    TCCR0B = (1 << CS00); // Start Timer0 with no prescaling.

    while(1){
        checkAndHandleInput(); // Check for button presses and adjust LED brightness.
        _delay_ms(100); // Small delay to avoid hogging CPU resources.
    }

    return 0;
}

