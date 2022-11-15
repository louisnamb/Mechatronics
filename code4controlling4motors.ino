/* ------------------------------------------------------- //
   529814H - Mechatronics
   Cleaning rover code
  // ------------------------------------------------------- */

/*               Variable initialisation                   */
/* ------------------------------------------------------- */
/* ************** Rover's Variables ********************** */
int en1 = 2;
int en2 = 3;
int en3 = 4;
int en4 = 5;

/* ************** RGB LED's Variables ********************* */
const int RED_PIN = 8; //red wire
const int GREEN_PIN = 7;  //white wire
const int BLUE_PIN = 6;  //blue wire

/* ********** Ultrasonic senor's Variables **************** */
#define echoPin 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 12 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel
unsigned int distance; // variable for the distance measurement

/* ************** Piezo buzzer's Variables **************** */
const int buzzer = 9; //piezo buzzer pin

/* ************** Miscellaneous  Variables **************** */
long nowMillis;
int num = 0;
int first = 0;

/*               Function initialisation                    */
/* -------------------------------------------------------- */
/* **************** Rover's Movement ********************** */
void halt(int time) {
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite(en3, LOW);
  digitalWrite(en4, LOW);
  delay(time);
}

void turn_right() {
  digitalWrite(en1, HIGH);
  digitalWrite(en2, LOW);      //   Right Turn  Output Left Hand side
  digitalWrite(en3, LOW);    //   Right Turn  Output Right Hand side
  digitalWrite(en4, HIGH);
}

void backward() {
  //analogWrite(13, 180);
  digitalWrite(en1, HIGH);     //  Backwards    Forwards Output Left Hand side
  digitalWrite(en2, LOW);
  digitalWrite(en3, HIGH);    //   Backwards    Backwards Output Right Hand side
  digitalWrite(en4, LOW);
}

void turn_left() {
  //analogWrite(13, 180);
  digitalWrite(en1, LOW);
  digitalWrite(en2, HIGH);     // Left Turn    Output Left Hand side
  digitalWrite(en3, HIGH);     //  Left turn   Output Right Hand side
  digitalWrite(en4, LOW);
}

void forward() {
  digitalWrite(en1, LOW);     //  Forwards   Backwards Output Left Hand side
  digitalWrite(en2, HIGH);
  digitalWrite(en3, LOW);    //  Forwards   Forwards Output Right Hand side
  digitalWrite(en4, HIGH);
}

/* ******************* Range Detector ********************* */
// Range detector with sound for range less than 25cm
int range_detectr() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Receive the signal
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  delay(10);
  if ((distance > 0) && (distance <= 35)) {
    halt(1500);
    RGB_color(255, 0, 0); // Red
    piezobuzzer(500);
    return (1);
  }
  Serial.print("\nGood distance\n");
  RGB_color(0, 255, 0); // Green
  return (0);
}

/* ******************* Piezo buzzer sound ***************** */
void piezobuzzer(int time) {
  tone(buzzer, 700); // Send 1KHz sound signal...
  delay(time);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(time);        // ...for 1sec
  noTone(buzzer);
}

/* ******************* RGB LED lights ********************* */
void RGB_color(int RED_VAL, int GREEN_VAL, int BLUE_VAL) {
  analogWrite(RED_PIN, RED_VAL);
  analogWrite(GREEN_PIN, GREEN_VAL);
  analogWrite(BLUE_PIN, BLUE_VAL);
}

void timer_func(int time) {
  nowMillis = millis();
  if (nowMillis % time == 0)
  {
    piezobuzzer(500);
    Serial.print("Time: ");
    Serial.print(nowMillis);
    Serial.println("s\n");
  }
}
/*                            Setup                        */
/* ------------------------------------------------------- */
void setup() {
  // Movement setup
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(en4, OUTPUT);

  // Piezo buzzer setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  // Serial Monitor setup (can delete)
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

/*                            Loop                         */
/* ------------------------------------------------------- */

void loop() {
  first++;
  if (++first == 1)
    delay(3000);
  while (range_detectr() == 0) {
    forward();
  }
  delay(5);
  turn_left();
  turn_left();
  delay(5);
  forward();/*
  turn_left();
  while ((range_detectr() == 1) && (first == 1)) 
    turn_right();
  first = 0;*/
}
