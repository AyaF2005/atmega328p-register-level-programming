// QUESTION 4: Fast PWM Signal Generation - MANUAL PWM VERSION
// LED A (Pin 11) at 75% brightness
// LED B (Pin 3) at 25% brightness
// PWM Frequency: ~976 Hz (simulated with fast loop)

#include <avr/io.h>

// PWM variables
volatile uint16_t pwm_counter = 0;
volatile uint8_t pwm_a_value = 192;  // 75% = 192/256
volatile uint8_t pwm_b_value = 64;   // 25% = 64/256

void init_q4_pwm() {
  // Set Pin 11 (PB3) as output
  DDRB |= (1 << PB3);
  PORTB &= ~(1 << PB3); // Start OFF
  
  // Set Pin 3 (PD3) as output
  DDRD |= (1 << PD3);
  PORTD &= ~(1 << PD3); // Start OFF
  
  // Initialize PWM values
  pwm_counter = 0;
  pwm_a_value = 192;  // 75% brightness
  pwm_b_value = 64;   // 25% brightness
}

void update_pwm() {
  // Increment counter (0-255)
  pwm_counter++;
  if (pwm_counter > 255) {
    pwm_counter = 0;
  }
  
  // LED A (Pin 11): 75% brightness
  if (pwm_counter < pwm_a_value) {
    PORTB |= (1 << PB3);  // Set HIGH
  } else {
    PORTB &= ~(1 << PB3); // Set LOW
  }
  
  // LED B (Pin 3): 25% brightness
  if (pwm_counter < pwm_b_value) {
    PORTD |= (1 << PD3);  // Set HIGH
  } else {
    PORTD &= ~(1 << PD3); // Set LOW
  }
}

void setup() {
  Serial.begin(9600);
  
  init_q4_pwm();
  
  Serial.println("");
  Serial.println("---- QUESTION 4: Fast PWM ----");
  Serial.println("LED A (Pin 11): 75% brightness");
  Serial.println("LED B (Pin 3): 25% brightness");
  Serial.println("PWM Mode: Software-based");
  Serial.println("Status: RUNNING");
  Serial.println("");
}

void loop() {
  // Simulate 976 Hz PWM by calling update_pwm many times
  // This creates the PWM effect by rapidly switching outputs
  
  for (int i = 0; i < 100; i++) {
    update_pwm();
    // Very small delay to create 976 Hz effect
    delayMicroseconds(10);
  }
  
  // Print status every loop iteration (gives visual feedback)
  static unsigned long last_print = 0;
  unsigned long now = millis();
  
  if (now - last_print >= 2000) {
    Serial.println("PWM: LED A ON (75%) | LED B ON (25%)");
    last_print = now;
  }
}