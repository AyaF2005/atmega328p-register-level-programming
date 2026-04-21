// QUESTION 5: ADC Dimmer - ULTRA SIMPLE VERSION
// Pure Arduino functions only

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  Serial.println("Q5 START");
}

void loop() {
  // Read potentiometer
  int value = analogRead(A0);
  
  // Convert to brightness (0-255)
  int brightness = value / 4;
  
  // Set LED brightness
  analogWrite(5, brightness);
  
  // Print every 1 second
  static unsigned long last = 0;
  if (millis() - last >= 1000) {
    Serial.print("Value: ");
    Serial.print(value);
    Serial.print(" Brightness: ");
    Serial.println(brightness);
    last = millis();
  }
  
  delay(100);
}