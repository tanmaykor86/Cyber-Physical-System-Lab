#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn all LEDs OFF (active LOW)
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while (1);
  }

  Serial.println("Proximity Sensor Started");
}

void loop() {
  if (APDS.proximityAvailable()) {

    int proximity = APDS.readProximity();

    Serial.print("Proximity: ");
    Serial.println(proximity);

    // Turn OFF all LEDs
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (proximity < 100) {
      // RED
      digitalWrite(LEDR, LOW);
    }
    else if (proximity < 200) {
      // GREEN
      digitalWrite(LEDG, LOW);
    }
    else {
      // BLUE
      digitalWrite(LEDB, LOW);
    }

    delay(100);
  }
}