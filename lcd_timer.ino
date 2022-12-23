#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int reset = 4;
int secButton = 5;
int minButton = 6;
int start = 7;

int TimeMins = 0;

int mins = 60;
int sec = 1;
int duration = 0;

int row = 8;

void setup() {
 
  // Button 
  pinMode(reset, INPUT_PULLUP);
  pinMode(secButton, INPUT_PULLUP);
  pinMode(minButton, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);

  // Serial monitor
  Serial.begin(9600);

  //LCD Display
  lcd.begin();
  lcd.clear();
  
  // put your main code here, to run repeatedly:
  lcd.print("Timer: ");
  lcd.setCursor(8,0);
}
/*
Use a struct whose properties are the wait time for that position 
and how much you add every click to the total time.
*/

void msertyhger() {
  if (digitalRead(secButton) == LOW) {
    duration += sec;
    delay(250);
  }
  if (digitalRead(minButton) == LOW) {
    TimeMins = (duration + 60) / 60;
  //  TimeSec = (duration + 60) - (60 * TimeMins);
    lcd.setCursor(row, 0);
    lcd.print(TimeMins);
    lcd.setCursor(row++, 0);
    lcd.print(":");
    row++;
    delay(250);
  }

  if (digitalRead(start) == LOW) { 
    delay(250);
    while (TimeMins != 0) {
      while (duration != 0) {
        lcd.print(duration);
        duration--;
        delay(1000);
      }
      TimeMins--;
    }
  }
  
  /*
  while (TimeMins != 0) {
    while (duration != 0) {
      duration--;
      delay(1000);
      lcd.setCursor(10, 0);
      lcd.print(duration);  
    }
    TimeMins--;
    lcd.setCursor(8, 0);
    lcd.print(TimeMins);
    lcd.setCursor(9,0);
    lcd.print(":");
    delay(1500);
  }*/
}

void loop() {
  if (digitalRead(reset) == LOW) {
    duration, TimeMins = 0;
    row = 8;
  }
  if (digitalRead(secButton) == LOW) {
    duration += sec;
    delay(250);
  }
  if (digitalRead(minButton) == LOW) {
    TimeMins++;
    lcd.setCursor(7, 0);
    lcd.print(TimeMins);
    if (TimeMins == 1) {
      lcd.setCursor(row++, 0);
      lcd.print(":");
      row++;
    }
    delay(250);    
  }
  
  if (digitalRead(start) == LOW) {
    delay(250);
    while (TimeMins > -1) {
      while (duration > -1) {
        lcd.setCursor(row, 0);
        lcd.print(duration);
        duration--;
        delay(1000);
      }
      lcd.setCursor(7, 0);
      TimeMins--;
      lcd.print(TimeMins);
      duration = 60;
    }
  }
  lcd.setCursor(row, 0);
  lcd.print(duration);
}
