# ATmega328P Register-Level Programming 

Direct hardware register programming on the ATmega328P microcontroller (Arduino Uno),
bypassing Arduino library abstractions to control peripherals at the hardware level.

Built as a homework assignment for ENCS4380 - Interfacing Techniques | Birzeit University.

---

## 📋 Topics Covered

### Q1 — Hardware & Pin Change Interrupts
- INT0 (Pin 2): toggles LED 1 on rising edge via EICRA + EIMSK
- PCINT0 (Pin 8): toggles LED 2 on any pin change via PCICR + PCMSK0
- No polling — fully interrupt-driven

### Q2 — Timer1 CTC Mode (1 Hz Blinking)
- 16-bit Timer1 in CTC mode
- Prescaler: 256 | OCR1A = 31,249
- Precise 500 ms toggles → 1 Hz LED blink, non-blocking

### Q3 — Timer2 Overflow Mode (Software Counter)
- 8-bit Timer2 with 1024 prescaler
- Overflow every ~16.384 ms → software counts 61 overflows → 1 Hz toggle
- Uses `volatile` counter variable in ISR

### Q4 — Fast PWM Signal Generation
- Timer2 Fast PWM at ~976 Hz
- LED A (Pin 11): 75% duty cycle → OCR2A = 192
- LED B (Pin 3): 25% duty cycle → OCR2B = 64

### Q5 — ADC Dimmer (Potentiometer → LED)
- 10-bit ADC on A0, AVcc reference
- Maps 0–1023 ADC value to 0–255 PWM (divide by 4)
- Timer0 Fast PWM on Pin 5 — smooth LED dimming

---

## 🛠️ Hardware

- Arduino Uno (ATmega328P)
- LEDs, push buttons, potentiometer, resistors
- Simulated in **TinkerCAD**

---

## ⚙️ Key Registers Used

| Peripheral | Registers |
|------------|-----------|
| External Interrupt | EICRA, EIMSK |
| Pin Change Interrupt | PCICR, PCMSK0 |
| Timer1 (CTC) | TCCR1A, TCCR1B, OCR1A, TIMSK1 |
| Timer2 (Overflow/PWM) | TCCR2A, TCCR2B, OCR2A, OCR2B, TIMSK2 |
| Timer0 (PWM) | TCCR0A, TCCR0B, OCR0B |
| ADC | ADMUX, ADCSRA, ADCL, ADCH |

---

## 🚀 How to Run

1. Open any `.ino` file in the Arduino IDE
2. Upload to an Arduino Uno, **or**
3. Paste into [TinkerCAD](https://www.tinkercad.com/) and simulate

No external libraries required — pure register-level C.

---

Birzeit University | December 2025
Instructor: Wasel Ghanem
Student: Aya Abdelrahman Fares
