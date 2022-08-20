const int microphonePin = A0;
int last_time;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int mn = 1024;
  int mx = 0;

  for (int i = 0; i < 10000; ++i) {
//    Serial.println(millis() - last_time);
//    last_time = millis();
    int val = analogRead(microphonePin);

    mn = min(mn, val);
    mx = max(mx, val);
  }

  int delta = mx - mn;

  Serial.print("Min=");
  Serial.print(mn);
  Serial.print(" Max=");
  Serial.print(mx);
  Serial.print(" Delta=");
  Serial.println(delta);
}
