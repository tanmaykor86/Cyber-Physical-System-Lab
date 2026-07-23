#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("Tilt Detection Started");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {

    IMU.readAcceleration(x, y, z);

    if (x > 0.7) {
      Serial.println("Tilted Right");
    }
    else if (x < -0.7) {
      Serial.println("Tilted Left");
    }
    else {
      Serial.println("Flat");
    }

    delay(300);
  }
}