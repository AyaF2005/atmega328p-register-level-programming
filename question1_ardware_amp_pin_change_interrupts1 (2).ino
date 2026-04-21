// QUESTION 1: Hardware & Pin Change Interrupts - FULLY FIXED
// Button A (Pin 2) -> LED 1 (Pin 13) [Rising Edge]
// Button B (Pin 8) -> LED 2 (Pin 12) [Any Change]

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t led1_state = 0;
volatile uint8_t led2_state = 0;

void init_q1_interrupts() {
  // ===== LED CONFIGURATION =====
  // Set LED pins as outputs
  DDRB |= (1 << PB5); // Pin 13 (LED 1) as output
  DDRB |= (1 << PB4); // Pin 12 (LED 2) as output
  
  // Start BOTH LEDs OFF
  PORTB &= ~(1 << PB5); // LED 1 OFF
  PORTB &= ~(1 << PB4); // LED 2 OFF
  
  led1_state = 0;
  led2_state = 0;
  
  // ===== BUTTON A CONFIGURATION (INT0 - Pin 2) =====
  // Set Pin 2 as input
  DDRD &= ~(1 << PD2);
  
  // Enable internal pull-up on Pin 2
  PORTD |= (1 << PD2);
  
  // Configure INT0 for rising edge
  EICRA = 0x00; // Clear EICRA first
  EICRA |= (1 << ISC01) | (1 << ISC00); // ISC01=1, ISC00=1 = Rising edge
  
  // Enable INT0 interrupt
  EIMSK = 0x00; // Clear EIMSK first
  EIMSK |= (1 << INT0);
  
  // ===== BUTTON B CONFIGURATION (PCINT0 - Pin 8) =====
  // Set Pin 8 as input
  DDRB &= ~(1 << PB0);
  
  // Enable internal pull-up on Pin 8
  PORTB |= (1 << PB0);
  
  // Enable Pin Change Interrupt on Port B
  PCICR = 0x00; // Clear PCICR first
  PCICR |= (1 << PCIE0); // Enable PCIE0 for Port B
  
  // Enable PCINT0 (Pin 8)
  PCMSK0 = 0x00; // Clear PCMSK0 first
  PCMSK0 |= (1 << PCINT0);
  
  // ===== ENABLE GLOBAL INTERRUPTS =====
  sei();
}

// ISR for INT0 (Button A on Pin 2 - Rising Edge)
ISR(INT0_vect) {
  // Debounce delay
  _delay_ms(20);
  
  // Toggle LED 1 (Pin 13 / PB5)
  PORTB ^= (1 << PB5);
  led1_state = !led1_state;
  
  Serial.print("Button A Pressed - LED 1: ");
  Serial.println(led1_state ? "ON" : "OFF");
}

// ISR for PCINT0 (Button B on Pin 8 - Any Change)
ISR(PCINT0_vect) {
  // Debounce delay
  _delay_ms(20);
  
  // Toggle LED 2 (Pin 12 / PB4)
  PORTB ^= (1 << PB4);
  led2_state = !led2_state;
  
  Serial.print("Button B Changed - LED 2: ");
  Serial.println(led2_state ? "ON" : "OFF");
}

void setup() {
  Serial.begin(9600);
  delay(500);
  
  init_q1_interrupts();
  
  Serial.println("----- QUESTION 1: Pin Change Interrupts ----- ");
  Serial.println("Button A (Pin 2) -> LED 1 (Pin 13) [Rising Edge]");
  Serial.println("Button B (Pin 8) -> LED 2 (Pin 12) [Any Change]");
  Serial.println("");
  Serial.println("Press buttons to toggle LEDs...");
}

void loop() {
  // Everything handled by interrupts
  // Main loop remains empty
}