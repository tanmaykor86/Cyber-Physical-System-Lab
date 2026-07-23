void setup() {
  Serial.begin(9600);

  // Set ADC resolution to 12 bits (0–4095)
  analogReadResolution(12);
}

void loop() {
  int sensorValue = analogRead(A6);

  // Convert ADC value to voltage
  float voltage = (sensorValue * 3.3) / 4095.0;

  Serial.print("ADC Value: ");
  Serial.print(sensorValue);

  Serial.print("   Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(500);
}