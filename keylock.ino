#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#include <Wire.h>
#include <Keypad.h>

Servo ServoMotor;

char* password = "12345";

// constants for row and column size
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

// connections to arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int RedpinLock = 12;
int GreenpinUnlock = 10;

void setup() {
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);

  // setup serial monetor
  lcd.backlight();
  lcd.init();
  lcd.setCursor(0, 1);
  lcd.print("*********");
  Serial.begin(9600);
  ServoMotor.attach(11);
  LockedPosition(true);

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  
  // get key value if pressed
  char customKey = customKeypad.getKey();
    
  if (customKey != NO_KEY) {
    // print key value to serial moneter
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(customKey);
    
    Serial.println(customKey);
  }
//-----------------------------------------------------
  //char key = keypad.getKey();
  if (customKey == '*' || customKey == '#') {
    position = 0;
    LockedPosition(true);
  }
  if (customKey == password[position]) {
    position ++;
  }
  if (position == 5) {
    LockedPosition(false);
  }
  delay(100);
  }
  void LockedPosition(int locked) {
    if (locked) {
      digitalWrite(RedpinLock, HIGH);
      digitalWrite(GreenpinUnlock, LOW);
      ServoMotor.write(11);
  } else {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90);
  }

}
