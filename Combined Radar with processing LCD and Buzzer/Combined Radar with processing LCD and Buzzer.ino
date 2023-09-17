// Includes the Servo library
#include <Servo.h>.
#include <LiquidCrystal.h>.

// Defines Tirg and Echo pins of the Ultrasonic Sensor
 int trigPin = 10;
 int echoPin = 11;
 int buzzer = 13;
 int ledGREEN = 6; //pin1 is green
 int ledRED = 7; //pin2 is red
// Variables for the duration and the distance
long duration;
int distance, criticalDistance;

Servo myServo;                        // Creates a servo object for controlling the servo motor
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);   //Set the buzzer as an output
  pinMode(ledGREEN, OUTPUT);  //Set the Led1(Red LED) as an output
  pinMode(ledRED, OUTPUT);
  lcd.begin(16, 2);    // Initialiser l'interface de Lcd avec leurs Dimensions
  myServo.attach(12);  // Defines on which pin is the servo motor attached
  Serial.begin(9600);


  //Set the LED2(GREEN) as an output
  criticalDistance = 20;
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int pos = 15; pos <= 165; pos++) {
    myServo.write(pos);
    // delay(30);
    distance = calculateDistance();  // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree



    Serial.print(pos);       // Sends the current degree into the Serial Port
    Serial.print(",");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance);  // Sends the distance value into the Serial Port
    Serial.print(".");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing

    if (distance <= criticalDistance) {

      if (distance <= criticalDistance / 2) {

        tone(buzzer, 2000);  // Send 1KHz sound signal...
        digitalWrite(ledGREEN, LOW);
        digitalWrite(ledRED, HIGH);
        delay(30);
        noTone(buzzer);           // Stop sound...
        lcd.setCursor(0, 0);      // positionner le cursor a 0,0
        lcd.print("Distance: ");  // Printe "Distance" sur LCD
        lcd.print(distance);      // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");        // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);
        lcd.print("Angle : ");
        lcd.print(pos);
        lcd.print(" deg ");
        // delay(30);

      } else {
        // digitalWrite(buzzer, HIGH);
        digitalWrite(ledRED, LOW);
        digitalWrite(ledGREEN, HIGH);
        delay(30);
        digitalWrite(buzzer, LOW);
        lcd.setCursor(0, 0);      // positionner le cursor a 0,0
        lcd.print("Distance: ");  // Printe "Distance" sur LCD
        lcd.print(distance);      // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");        // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);
        lcd.print("Angle : ");
        lcd.print(pos);
        lcd.print(" deg ");
        // delay(30);
      }
    } else {
      // digitalWrite(buzzer, LOW);
      digitalWrite(ledGREEN, LOW);
      digitalWrite(ledRED, LOW);
    }

    lcd.setCursor(0, 0);      // positionner le cursor a 0,0
    lcd.print("Distance: ");  // Printe "Distance" sur LCD
    lcd.print(distance);      // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");        // Printe l'unité sur LCD
    delay(10);
    lcd.setCursor(0, 1);
    lcd.print("Angle : ");
    lcd.print(pos);
    lcd.print(" deg ");
    delay(30);
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int pos = 165; pos > 15; pos--) {
    myServo.write(pos);
    // delay(30);
    distance = calculateDistance();


    Serial.print(pos);       // Sends the current degree into the Serial Port
    Serial.print(",");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance);  // Sends the distance value into the Serial Port
    Serial.print(".");       // Sends addition character right next to the previous value needed later in the Processing IDE for indexing


    if (distance <= criticalDistance) {

      if (distance <= criticalDistance / 2) {

        tone(buzzer, 10);  // Send 1KHz sound signal...
        digitalWrite(ledGREEN, LOW);
        digitalWrite(ledRED, HIGH);
        delay(30);
        noTone(buzzer);           // Stop sound...
        lcd.setCursor(0, 0);      // positionner le cursor a 0,0
        lcd.print("Distance: ");  // Printe "Distance" sur LCD
        lcd.print(distance);      // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");        // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);
        lcd.print("Angle : ");
        lcd.print(pos);
        lcd.print(" deg ");
        // delay(30);


      } else {
        digitalWrite(buzzer, HIGH);
        digitalWrite(ledRED, LOW);
        digitalWrite(ledGREEN, HIGH);
        delay(30);
        digitalWrite(buzzer, LOW);
        lcd.setCursor(0, 0);      // positionner le cursor a 0,0
        lcd.print("Distance: ");  // Printe "Distance" sur LCD
        lcd.print(distance);      // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");        // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);
        lcd.print("Angle : ");
        lcd.print(pos);
        lcd.print(" deg ");
        // delay(30);
      }
    } else {
      digitalWrite(buzzer, LOW);
      digitalWrite(ledGREEN, LOW);
      digitalWrite(ledRED, LOW);
    }

    lcd.setCursor(0, 0);      // positionner le cursor a 0,0
    lcd.print("Distance: ");  // Printe "Distance" sur LCD
    lcd.print(distance);      // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");        // Printe l'unité sur LCD
    delay(10);
    lcd.setCursor(0, 1);
    lcd.print("Angle : ");
    lcd.print(pos);
    lcd.print(" deg ");
    delay(30);
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Serial.println();
  // Serial.print("Duration = ");
  // Serial.println(duration);
  distance = (duration * 0.034) / 2;
  // Serial.print("Distance = ");
  // Serial.println(distance);
  return distance;
}