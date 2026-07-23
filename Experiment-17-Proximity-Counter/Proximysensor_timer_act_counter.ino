#include <Arduino_APDS9960.h>

// LED mapping for your board
const int redLED = LEDR;      // RED
const int greenLED = LEDB;    // GREEN

int count = 0;
bool handPresent = true;      // Prevent false count at startup
bool greenState = false;

void setup() {
  Serial.begin(9600);
  delay(2000);   // Wait for Serial Monitor

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Start with RED ON
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);

  if (!APDS.begin()) {
    Serial.println("APDS9960 not found!");
    while (1);
  }

  // Clear any old sensor readings
  while (APDS.proximityAvailable()) {
    APDS.readProximity();
  }

  Serial.println("System Ready");
  Serial.println("Remove your hand to start...");
}

void loop() {

  if (APDS.proximityAvailable()) {

    int proximity = APDS.readProximity();

    // Uncomment this if you want to see the sensor values
    // Serial.println(proximity);

    // Hand removed
    if (proximity < 50) {
      handPresent = false;
    }

    // New hand detection
    if (proximity > 200 && !handPresent) {

      handPresent = true;

      if (!greenState) {

        count++;

        Serial.print("Count: ");
        Serial.println(count);

        if (count == 15) {

          digitalWrite(redLED, HIGH);     // Red OFF
          digitalWrite(greenLED, LOW);    // Green ON

          greenState = true;

          Serial.println("GREEN LED ON");
        }
      }
      else {

        // Reset after next hand detection
        count = 0;
        greenState = false;

        digitalWrite(redLED, LOW);       // Red ON
        digitalWrite(greenLED, HIGH);    // Green OFF

        Serial.println("RESET");
        Serial.println("Count: 0");
      }
    }
  }
}