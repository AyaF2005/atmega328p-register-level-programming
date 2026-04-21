// QUESTION 3: Timer2 Overflow Mode (Software Counter) - FULLY FIXED
// LED on Pin 13 blinks at approximately 1 Hz using overflow interrupts

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;
const uint8_t OVERFLOW_TARGET = 61; // ~1 second (1000ms / 16.384ms)
volatile uint8_t led_state = 0;

void init_q3_timer2() {
  // ===== LED CONFIGURATION =====
  // Set Pin 13 (PB5) as output
  DDRB |= (1 << PB5);
  
  // Start LED OFF
  PORTB &= ~(1 << PB5);
  led_state = 0;
  overflow_count = 0;
  
  // ===== TIMER2 CONFIGURATION =====
  // Clear all Timer2 control registers
  TCCR2A = 0x00;
  TCCR2B = 0x00;
  
  // Clear counter register
  TCNT2 = 0x00;
  
  // Timer2 is 8-bit: counts from 0-255 (256 total values)
  // With prescaler 1024:
  // Time per overflow = (1/16MHz) * 1024 * 256 = 16.384ms
  
  // Set Prescaler to 1024
  // CS22 = 1, CS21 = 0, CS20 = 1
  TCCR2B |= (1 << CS22) | (1 << CS20);
  
  // ===== INTERRUPT CONFIGURATION =====
  // Enable Timer2 Overflow Interrupt
  TIMSK2 = 0x00; // Clear first
  TIMSK2 |= (1 << TOIE2);
  
  // Enable global interrupts
  sei();
}

// ISR for Timer2 Overflow (fires every 16.384ms)
ISR(TIMER2_OVF_vect) {
  overflow_count++;
  
  // Check if we've reached the target number of overflows
  if (overflow_count >= OVERFLOW_TARGET) {
    // Toggle LED on Pin 13 (PB5)
    PORTB ^= (1 << PB5);
    led_state = !led_state;
    
    Serial.print("Timer2 Overflow Count Reached (");
    Serial.print(OVERFLOW_TARGET);
    Serial.print(") - LED: ");
    Serial.println(led_state ? "ON" : "OFF");
    
    // Reset overflow counter
    overflow_count = 0;
  }
}

void setup() {
  Serial.begin(9600);
  delay(500);
  
  init_q3_timer2();
  
  Serial.println("----- QUESTION 3: Timer2 Overflow Mode ----- ");
  Serial.println("LED blinking at ~1 Hz on Pin 13");
  Serial.println("");
  Serial.println("Timer2 Configuration:");
  Serial.println("  - Prescaler: 1024");
  Serial.println("  - Counter: 8-bit (0-255)");
  Serial.println("  - Time per overflow: 16.384ms");
  Serial.println("  - Software counter target: 61 overflows");
  Serial.println("  - Total time: ~1000ms");
  Serial.println("");
  Serial.println("LED should blink: ON for ~1 second, OFF for ~1 second, repeat...");
}

void loop() {
  // Everything handled by Timer2 overflow interrupt
  // Main loop remains empty
}