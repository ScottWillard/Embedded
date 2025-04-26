/*
  LCD Screen in (f1-f16)
  j1 connected to - rail, j2 connected to + rail, j3 connected to - rail, j4 connected to pin 11, j5 connected to pin 10, j6 connected to pin 9
  j11 connected to pin 2, j12 connected to pin 3, j13 connected to pin 4, j14 connected to pin 5, j15 connected to + rail, j16 connected to - rail
  5v connected to + rail, GND connected to - rail, g33 connected to GND, LED(red) in h33- and h35+, i35 connected to pin7
  220Ω in j35 and j40
  Passive buzzer in j46- and j48+, g46 connected to GND, g48 connected to pin 8
  Ultrasonic sensor in (a60-a63)
  d60 connected to + rail, d61 connected to pin 13, d62 connected to pin 12, d63 connected to - rail
*/

// -------------------------------------------
// Distance Sensor with LED and Buzzer Alarm
// Components: HC-SR04 (ultrasonic sensor), LCD(LCD1602), LED (red), Passive Buzzer
// -------------------------------------------

// Include the LiquidCrystal library to control the LCD
#include <LiquidCrystal.h>

// Initialize the LCD with the interface pins
LiquidCrystal LCD(11, 10, 9, 2, 3, 4, 5);

// Define pin assignments
#define trigPin 13   // HC-SR04 Trigger Pin
#define echoPin 12   // HC-SR04 Echo Pin
#define ledPin 7     // LED output pin
#define buzzerPin 8  // Buzzer output pin

void setup() {
  // Set pin modes
  pinMode(trigPin, OUTPUT);    // Trigger pin as OUTPUT
  pinMode(echoPin, INPUT);     // Echo pin as INPUT
  pinMode(ledPin, OUTPUT);     // LED pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);  // Buzzer pin as OUTPUT

  // Initialize the LCD (16 columns, 2 rows)
  LCD.begin(16, 2);

  // Print static text on the first row
  LCD.setCursor(0, 0);
  LCD.print("Target Distance:");
}

void loop() {
  // Variables to hold time and calculated distance
  long duration, distance;

  // Send a 10-microsecond pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2) / 29.1;

  // Clear and update the second line of the LCD with new distance
  LCD.setCursor(0, 1);
  LCD.print("                ");  // Clear previous reading
  LCD.setCursor(0, 1);
  LCD.print(distance);
  LCD.print(" cm");

  // -------------------------------------------
  // LED Control Logic
  // Turn LED ON if distance is 6 cm or less, otherwise OFF
  // -------------------------------------------
  if (distance <= 6) {
    digitalWrite(ledPin, HIGH);  // Turn ON LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn OFF LED
  }

  // -------------------------------------------
  // Buzzer Control Logic
  // If object is within 20 cm, pulse the buzzer ON and OFF
  // Otherwise keep buzzer OFF
  // -------------------------------------------
  if (distance <= 3) {
    digitalWrite(buzzerPin, HIGH);  // Buzzer ON
    delay(100);                     // Beep duration
    digitalWrite(buzzerPin, LOW);   // Buzzer OFF
    delay(100);                     // Silence between beeps
  } else {
    digitalWrite(buzzerPin, LOW);  // Ensure buzzer is OFF
  }

  // Small delay to control refresh rate
  delay(75);
}
