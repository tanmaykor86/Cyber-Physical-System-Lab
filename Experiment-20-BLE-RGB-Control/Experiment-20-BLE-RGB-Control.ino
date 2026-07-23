#include <Arduino_LSM9DS1.h>
#include <HardwareBLESerial.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();

const int redLED = LEDR;   // Built-in Red LED

void setup() {
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, HIGH);   // OFF initially (Nano 33 BLE LEDs are active LOW)

  while (!bleSerial.beginAndSetupBLE("Chaitanya"));
  while (!IMU.begin());
}

void loop() {
  float x, y, z;

  // Send Accelerometer Data
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    bleSerial.poll();

    Serial.print(x);
    bleSerial.print(x);

    Serial.print('\t');
    bleSerial.print('\t');

    Serial.print(y);
    bleSerial.print(y);

    Serial.print('\t');
    bleSerial.print('\t');

    Serial.println(z);
    bleSerial.println(z);
  }

  // Check for incoming BLE data
  bleSerial.poll();

  if (bleSerial.available()) {
    char cmd = bleSerial.read();

    if (cmd == 'A') {
      digitalWrite(redLED, LOW);      // ON
      Serial.println("Red LED ON");
    }

    else if (cmd == 'B') {
      digitalWrite(redLED, HIGH);     // OFF
      Serial.println("Red LED OFF");
    }
  }

  delay(10);
}