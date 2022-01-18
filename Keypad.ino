// for servo wire connection
// brown-brown
// red-red
// orange-green

#include<Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 3;
String passwordGiven = "555";
String passwordTaken = "";
int passwordLength = 3;
int count = 0;
int pos = 0; //Servi Position
bool doorLocked = false;
String tempPassword = "";

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Connection to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(11);

}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();
  if (customKey) {
    tempPassword = tempPassword + customKey;
    Serial.println("tempPassword(1st): " + tempPassword);
  }

  if (tempPassword == "*") {
      passwordGiven = "";
      int count2 = 0;
        while(passwordLength != count2) {
          char newCustomKey = customKeypad.getKey();
          Serial.println("newcustomkey: " + newCustomKey);
          count2++;
          if (newCustomKey) {
            passwordTaken = passwordTaken + newCustomKey;
            Serial.println("passwordTaken: " + passwordTaken);
            delay(100);
          }
      }
      passwordGiven = passwordTaken;
      delay(5000);
    }

  if (tempPassword == "#") {

//    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      myservo.write(pos);              // tell servo to go to position in variable 'pos'
//      delay(15);                       // waits 15 ms for the servo to reach the position
//    }
    //myservo.writeMicroseconds(2200);
    myservo.writeMicroseconds(2030);
    tempPassword = "";
    passwordTaken = "";
    Serial.println("passwordTaken(for #): " + passwordTaken);
    delay(5000);
  }

  else {
    if (customKey) {
      passwordTaken = passwordTaken + customKey;
      Serial.println("passwordTaken(for pass): " + passwordTaken);
      count++;
      delay(100);
    }

    if (count == passwordLength) {
      if (passwordGiven == passwordTaken) {
        Serial.println("Correct Password");

//        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//          myservo.write(pos);              // tell servo to go to position in variable 'pos'
//          delay(15);                     // waits 15 ms for the servo to reach the position
//        }

        //myservo.writeMicroseconds(600);
        myservo.writeMicroseconds(920);
        delay(5000);

        tempPassword = "";
        count = 0;
        passwordTaken  = "";
        delay(100);
      }
      else {
        Serial.println("Incorrect Password");
        tempPassword = "";
        count = 0;
        passwordTaken = "";
        delay(100);
      }
      delay(100);
    }
  }

}
