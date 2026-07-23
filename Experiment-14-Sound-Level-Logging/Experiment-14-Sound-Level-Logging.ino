#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead = 0;

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  PDM.onReceive(onPDMdata);

  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  Serial.println("Microphone Started");
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

    samplesRead = 0;
  }
}