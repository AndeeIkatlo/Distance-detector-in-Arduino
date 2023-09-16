#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 200

int buzzerPin = 11;
int ledPins[] = {7, 6, 5};
int thresholdDist1 = 10; // All LEDs blinking
int thresholdDist2 = 20; // Two LEDs blinking
int thresholdDist3 = 30; // One LED blinking
int maxDistance = 40; // Maximum distance for no blinking or beeping

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Calculate distance in centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= thresholdDist1) {
    beep(100); // Fast beep
    blinkAll(100); // All LEDs blink fast
  } else if (distance <= thresholdDist2) {
    beep(500); // Medium beep
    blinkTwo(500); // Two LEDs blink at medium speed
  } else if (distance <= thresholdDist3) {
    beep(1000); // Slow beep
    blinkOne(1000); // One LED blinks at slow speed
  } else if (distance <= maxDistance) {
    noTone(buzzerPin);
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void beep(unsigned int duration) {
  tone(buzzerPin, 1100); // Beep at 1100 Hz
  delay(duration);
  noTone(buzzerPin);
}

void blinkAll(unsigned int duration) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(duration);
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void blinkTwo(unsigned int duration) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(duration);
  for (int i = 0; i < 2; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void blinkOne(unsigned int duration) {
  digitalWrite(ledPins[0], HIGH);
  delay(duration);
  digitalWrite(ledPins[0], LOW);
}
