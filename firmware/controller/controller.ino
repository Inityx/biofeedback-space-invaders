int val = 0;

void setup() {
  Serial.begin(19200);
}


void loop() {
  // something something reading analog
  int val = analogRead(A0);

  // just blink led for sanity checking that the chip isnt fucked
  delay(200);
  digitalWrite(11, !digitalRead(11));
  delay(800);
  // smol uart sanity checking
  Serial.println("hello");

  // send back the ADC reads or something whenever we get anything from the master
  // e.g. any byte from the raspi
  if(Serial.available() > 0) {
    byte garbage = Serial.read();
    Serial.println(garbage);
    Serial.println(val);
  }
}

