#include <Servo.h>.
#include <LiquidCrystal.h>.

Servo servoMotor;                           //Create the Servo object
LiquidCrystal lcd(52, 50, 48, 46, 44, 42);  // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

int delayTime = 5;  //Delay value to wait for the servo to reach the 1 angle difference
long d;             //Distance from 1st sensor calculated
long d2;
// Defines Tirg and Echo pins of the Ultrasonic Sensor1
int trigPin1 = 10;
int echoPin1 = 11;
// Defines Tirg and Echo pins of the Ultrasonic Sensor1
int trigPin2 = 12;
int echoPin2 = 13;  //Distance from 2nd sensor calculated
int buzzer = 36;
int ledGREEN = 28;   //pin1 is green
int ledYELLOW = 30;  //pin1 is yellow
int ledRED = 32;     //pin2 is red
long duration1, duration2;
int distance, criticalDistance, distance2;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);       //Attach the servo to the Digital PWM pin 2
  pinMode(trigPin1, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);   // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);   // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);    //Set the buzzer as an output
  pinMode(ledGREEN, OUTPUT);  //Set the Led1(Red LED) as an output
  pinMode(ledYELLOW, OUTPUT);
  pinMode(ledRED, OUTPUT);
  lcd.begin(20, 4);
  //Initialize the Serial communication at 9600 bauds


  //servoMotor.write(180);  //Rotate the servo to the 180?
  //delay(1000);            //Wait for the servo to reach 180?
  //servoMotor.write(0);    //Rotate the servo to the 0?
  //delay(1000);            //Wait for the servo to reach 0?

  criticalDistance = 20;
}

void loop() {
  for (int i = 1; i < 180; i++) {  //Move the Servo 180 degrees forward

    distance = readSensor1();  //Read the sensors
    //delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
    distance2 = readSensor2();

    // Serial.print(i);            //Print the angle
    // Serial.print(",");          //Print a ","
    // Serial.print(distance);     //Print the 1st distance
    // Serial.print(",");          //Print a ","
    // Serial.println(distance2);  //Print the 2nd distance with end line
    //servoMotor.write(i);        //Set the sensor at the angle
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("!");
    Serial.print(distance2);
    Serial.print(".");
    servoMotor.write(i);  //Set the sensor at the angle
    //delay(delayTime);           //Wait for the servo to reach i?


    if (distance <= criticalDistance || distance2 <= criticalDistance) {

      if (distance <= criticalDistance / 2 || distance2 <= criticalDistance / 2) {
        // distance = readSensor1();  //Read the sensors
        //  delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
        // distance2 = readSensor2();

        tone(buzzer, 3000);  // Send 2KHz sound signal...
        digitalWrite(ledGREEN, LOW);
        digitalWrite(ledYELLOW, LOW);
        digitalWrite(ledRED, HIGH);
        delay(30);
        noTone(buzzer);               // Stop sound...
        lcd.setCursor(0, 0);          // positionner le cursor a 0,0
        lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance);          // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);          // positionner le cursor a 0,0
        lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        //delay(10);
        lcd.setCursor(0, 2);
        lcd.print("Angle : ");
        lcd.print(i);
        lcd.print(" deg ");
        lcd.setCursor(0, 3);
        lcd.print("Range");
        //delay(10);
        //lcd.setCursor(0, 3);
        //clear the 4th line before printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   //delay(100);
        // }
        // //lcd.print("");
        // lcd.setCursor(0, 3);
        // lcd.print("Critical Range!!");
        // delay(5);
        // //lcd.print("");
        // //clear the 4th line after printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   //delay(100);
        // }
        // delay(30);

      } else {
        // digitalWrite(buzzer, HIGH);
        digitalWrite(ledRED, LOW);
        digitalWrite(ledYELLOW, HIGH);
        digitalWrite(ledGREEN, LOW);
        // distance = readSensor1();  //Read the sensors
        //  delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
        // distance2 = readSensor2();

        //digitalWrite(buzzer, LOW);
        tone(buzzer, 1000);  // Send 2KHz sound signal...
        delay(30);
        noTone(buzzer);               // Stop sound...
        lcd.setCursor(0, 0);          // positionner le cursor a 0,0
        lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance);          // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);          // positionner le cursor a 0,0
        lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        //delay(10);
        lcd.setCursor(0, 2);
        lcd.print("Angle : ");
        lcd.print(i);
        lcd.print(" deg ");
        lcd.setCursor(0, 3);
        lcd.print("Range");
        //delay(10);
        // lcd.setCursor(0, 3);
        // lcd.print("");
        // lcd.print("Danger Range!");
        // delay(5);
        // lcd.print("");
        // delay(30);
        // //clear the 4th line before printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   delay(100);
        // }
        // //lcd.print("");
        // lcd.setCursor(0, 3);
        // lcd.print("Danger Range!");
        // delay(5);
        // //lcd.print("");
        // //clear the 4th line after printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   delay(100);
        // }
      }
    } else {
      // digitalWrite(buzzer, LOW);
      digitalWrite(ledYELLOW, LOW);
      digitalWrite(ledRED, LOW);
      digitalWrite(ledGREEN, HIGH);
    }
    // distance = readSensor1();  //Read the sensors
    //  delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
    // distance2 = readSensor2();

    delay(30);
    lcd.setCursor(0, 0);          // positionner le cursor a 0,0
    lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
    lcd.print(distance);          // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");            // Printe l'unité sur LCD
    delay(10);
    lcd.setCursor(0, 1);          // positionner le cursor a 0,0
    lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
    lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");            // Printe l'unité sur LCD
    //delay(10);
    lcd.setCursor(0, 2);
    lcd.print("Angle : ");
    lcd.print(i);
    lcd.print(" deg ");
    lcd.setCursor(0, 3);
    lcd.print("Range");
    //delay(30);
    //delay(10);
    // lcd.setCursor(0, 3);
    // lcd.print("");
    // lcd.print("Out Of Range");
    // delay(5);
    // lcd.print("");
    // //clear the 4th line before printing the message
    // for (int i = 0; i <= 15; i++) {
    //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
    //   lcd.print("");
    //   delay(100);
    // }
    // //lcd.print("");
    // lcd.setCursor(0, 3);
    // lcd.print("Out Of Range");
    // delay(5);
    // //lcd.print("");
    // //clear the 4th line after printing the message
    // for (int i = 0; i <= 15; i++) {
    //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
    //   lcd.print("");
    //   delay(100);
    // }
  }
  for (int i = 180; i > 1; i--) {  //Move the Servo 180 degrees backward
                                   //Read the sensors
    distance2 = readSensor2();
    //delay(100);  //As two sensors can interfere with each other, we need a delay of 100ms
    distance = readSensor1();
    // Serial.print(i);            //Print the angle
    // Serial.print(",");          //Print a ","
    // Serial.print(distance);     //Print the 1st distance
    // Serial.print(",");          //Print a ","
    // Serial.println(distance2);  //Print the 2nd distance with end line
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print("!");
    Serial.print(distance2);
    Serial.print(".");
    servoMotor.write(i);  //Set the sensor at the angle
    //delay(delayTime);           //Wait for the servo to reach i?

    if (distance <= criticalDistance || distance2 <= criticalDistance) {

      if (distance <= criticalDistance / 2 || distance2 <= criticalDistance / 2) {

        // distance2 = readSensor2();
        //      delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
        // distance = readSensor1();

        tone(buzzer, 3000);  // Send 1KHz sound signal...
        digitalWrite(ledGREEN, LOW);
        digitalWrite(ledYELLOW, LOW);
        digitalWrite(ledRED, HIGH);
        delay(30);
        noTone(buzzer);               // Stop sound...
        lcd.setCursor(0, 0);          // positionner le cursor a 0,0
        lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance);          // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);          // positionner le cursor a 0,0
        lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        //delay(10);
        lcd.setCursor(0, 2);
        lcd.print("Angle : ");
        lcd.print(i);
        lcd.print(" deg ");
        lcd.setCursor(0, 3);
        lcd.print("Range");
        //delay(10);
        // lcd.setCursor(0, 3);
        // lcd.print("");
        // lcd.print("Critical Range!!");
        // delay(5);
        // lcd.print("");
        // delay(30);
        //clear the 4th line before printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   //delay(100);
        // }
        // //lcd.print("");
        // lcd.setCursor(0, 3);
        // lcd.print("Critical Range!!");
        // delay(5);
        // //lcd.print("");
        // //clear the 4th line after printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   //delay(100);
        // }

      } else {
        // digitalWrite(buzzer, HIGH);
        digitalWrite(ledRED, LOW);
        digitalWrite(ledYELLOW, HIGH);
        digitalWrite(ledGREEN, LOW);

        // distance2 = readSensor2();
        // delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
        // distance = readSensor1();

        //digitalWrite(buzzer, LOW);


        tone(buzzer, 1000);  // Send 2KHz sound signal...
        delay(30);
        noTone(buzzer);               // Stop sound...
        lcd.setCursor(0, 0);          // positionner le cursor a 0,0
        lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance);          // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD
        delay(10);
        lcd.setCursor(0, 1);          // positionner le cursor a 0,0
        lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
        lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
        lcd.print(" cm ");            // Printe l'unité sur LCD

        lcd.setCursor(0, 2);
        lcd.print("Angle : ");
        lcd.print(i);
        lcd.print(" deg ");
        lcd.setCursor(0, 3);
        lcd.print("Range");
        //delay(10);

        // lcd.setCursor(0, 3);
        // lcd.print("");
        // lcd.print("Danger Range!");
        // delay(5);
        // lcd.print("");
        // //clear the 4th line before printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   delay(100);
        // }
        // //lcd.print("");
        // lcd.setCursor(0, 3);
        // lcd.print("Danger Range!");
        // delay(5);
        // //lcd.print("");
        // //clear the 4th line after printing the message
        // for (int i = 0; i <= 15; i++) {
        //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
        //   lcd.print("");
        //   delay(100);
        // }
        // delay(30);
      }
    } else {
      // digitalWrite(buzzer, LOW);
      digitalWrite(ledYELLOW, LOW);
      digitalWrite(ledRED, LOW);
      digitalWrite(ledGREEN, HIGH);
    }

    // distance2 = readSensor2();
    //  delay(100); //As two sensors can interfere with each other, we need a delay of 100ms
    // distance = readSensor1();
    delay(30);
    lcd.setCursor(0, 0);          // positionner le cursor a 0,0
    lcd.print("Dist 1st sensor:");  // Printe "Distance" sur LCD
    lcd.print(distance);          // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");            // Printe l'unité sur LCD
    delay(10);
    lcd.setCursor(0, 1);          // positionner le cursor a 0,0
    lcd.print("Dist 2nd sensor:");  // Printe "Distance" sur LCD
    lcd.print(distance2);         // Printe la valeur Obtenue sur LCD
    lcd.print(" cm ");            // Printe l'unité sur LCD
    //delay(10);
    lcd.setCursor(0, 2);
    lcd.print("Angle : ");
    lcd.print(i);
    lcd.print(" deg ");
    lcd.setCursor(0, 3);
    lcd.print("Range");
    //delay(30);
    //delay(10);
    // lcd.setCursor(0, 3);
    // lcd.print("");
    // lcd.print("Out Of Range");
    // delay(5);
    // lcd.print("");
    // //clear the 4th line before printing the message
    // for (int i = 0; i <= 15; i++) {
    //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
    //   lcd.print("");
    //   delay(100);
    // }
    // //lcd.print("");
    // lcd.setCursor(0, 3);
    // lcd.print("Out Of Range");
    // delay(5);
    // //lcd.print("");
    // //clear the 4th line after printing the message
    // for (int i = 0; i <= 15; i++) {
    //   lcd.setCursor(i, 3);  // Sets the location at which subsequent text written to the LCD will be displayed
    //   lcd.print("");
    //   delay(100);
    // }
  }
}

int readSensor1() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Serial.println();
  // Serial.print("Duration = ");
  // Serial.println(duration);
  distance = (duration1 * 0.034) / 2;
  // Serial.print("Distance = ");
  // Serial.println(distance);
  return distance;
}

int readSensor2() {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Serial.println();
  // Serial.print("Duration = ");
  // Serial.println(duration);
  distance2 = (duration2 * 0.034) / 2;
  // Serial.print("Distance = ");
  // Serial.println(distance);
  return distance2;
}