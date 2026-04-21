// QUESTION 2: Timer1 CTC Mode (1 Hz Blinking) - FULLY FIXED
// LED on Pin 9 blinks at exactly 1 Hz (500ms ON, 500ms OFF)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t led_state = 0;

void init_q2_timer1() {
  // ===== LED CONFIGURATION =====
  // Set Pin 9 (PB1) as output
  DDRB |= (1 << PB1);
  
  // Start LED OFF
  PORTB &= ~(1 << PB1);
  led_state = 0;
  
  // ===== TIMER1 CONFIGURATION =====
  // Clear all Timer1 control registers
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  
  // Clear counter register
  TCNT1 = 0x0000;
  
  // Set CTC Mode (Clear Timer on Compare Match)
  // WGM13 = 0, WGM12 = 1, WGM11 = 0, WGM10 = 0
  TCCR1B |= (1 << WGM12);
  
  // Set Prescaler to 256
  // CS12 = 1, CS11 = 0, CS10 = 0
  TCCR1B |= (1 << CS12);
  
  // Calculate OCR1A for 500ms interrupt
  // Formula: OCR1A = (Clock / (Prescaler * Frequency)) - 1
  // OCR1A = (16,000,000 / (256 * 2)) - 1 = 31,249
  // (2 Hz because we toggle twice per second for 1 Hz blink)
  OCR1A = 31249;
  
  // ===== INTERRUPT CONFIGURATION =====
  // Enable Output Compare A Match Interrupt
  TIMSK1 = 0x00; // Clear first
  TIMSK1 |= (1 << OCIE1A);
  
  // Enable global interrupts
  sei();
}

// ISR for Timer1 Compare Match A (fires every 500ms)
ISR(TIMER1_COMPA_vect) {
  // Toggle LED on Pin 9 (PB1)
  PORTB ^= (1 << PB1);
  led_state = !led_state;
  
  Serial.print("Timer1 Compare Match - LED: ");
  Serial.println(led_state ? "ON" : "OFF");
}

void setup() {
  Serial.begin(9600);
  delay(500);
  
  init_q2_timer1();
  
  Serial.println("---- QUESTION 2: Timer1 CTC Mode ----");
  Serial.println("LED blinking at 1 Hz on Pin 9");
  Serial.println("OCR1A = 31,249 | Prescaler = 256 | Frequency = 2 Hz (toggles)");
  Serial.println("");
  Serial.println("LED should blink: ON for 500ms, OFF for 500ms, repeat...");
}

void loop() {
  // Everything handled by Timer1 interrupt
  // Main loop remains empty
}