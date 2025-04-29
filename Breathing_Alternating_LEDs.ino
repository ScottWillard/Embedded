const int ledPin1 = 9;    // First LED on PWM pin 9
const int ledPin2 = 10;   // Second LED on PWM pin 10

int brightness = 0;       // Current brightness level for first LED
int fadeAmount = 15;       // Amount to change the brightness each cycle

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  analogWrite(ledPin1, brightness);           // Set brightness for first LED
  analogWrite(ledPin2, 255 - brightness);      // Set opposite brightness for second LED

  brightness += fadeAmount;                   // Change the brightness

  // Reverse the direction if we reach the limits
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;                  // Reverse fade direction
  }

  delay(25); // Adjust delay for fade speed
}
