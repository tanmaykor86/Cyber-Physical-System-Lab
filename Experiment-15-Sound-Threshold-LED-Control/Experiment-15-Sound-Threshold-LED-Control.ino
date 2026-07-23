#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead = 0;

const int threshold = 1000;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn all LEDs OFF (active LOW)
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  PDM.onReceive(onPDMdata);

  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM microphone!");
    while (1);
  }

  Serial.println("Sound Threshold LED Control Started");
}

void loop() {

  if (samplesRead) {

    int peak = 0;

    for (int i = 0; i < samplesRead; i++) {
      int sample = abs(sampleBuffer[i]);

      if (sample > peak) {
        peak = sample;
      }
    }

    Serial.print("Sound Level: ");
    Serial.println(peak);

    // Turn OFF all LEDs first
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (peak > threshold) {
      // Loud sound → BLUE LED ON
      digitalWrite(LEDB, LOW);
    } else {
      // Quiet sound → RED LED ON
      digitalWrite(LEDR, LOW);
    }

    samplesRead = 0;
  }
}