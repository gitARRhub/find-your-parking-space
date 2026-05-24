#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

/* ================= LCDs ================= */
LiquidCrystal_I2C lcdPark(0x27, 20, 4);
LiquidCrystal_I2C lcdAir (0x25, 20, 4);

/* ================= SERVO ================= */
Servo gateServo;
#define SERVO_PIN 6
#define GATE_OPEN 90
#define GATE_CLOSE 0

/* ================= IR SENSORS ================= */
int slotIR[6][2] = {
  {22,23},{24,25},{26,27},
  {28,29},{30,31},{32,33}
};
#define ENTRY_IR 34
#define EXIT_IR  35

/* ================= GAS SENSORS ================= */
#define MQ135 A0
#define MQ2   A1

/* ================= OUTPUTS ================= */
#define BUZZER 38
#define EMERGENCY_BTN 39
#define EXHAUST_FAN 46

/* ================= VARIABLES ================= */
bool slotOccupied[6];
bool emergencyActive = false;

int totalEntered = 0, totalExited = 0;

/* Baseline */
int mq135_base = 0, mq2_base = 0;

/* Gas values */
int CO, CO2, NH3, SMK, LPG, N2;
String airStatus;

/* ================= FUNCTIONS ================= */
void operateGate() {
  gateServo.write(GATE_OPEN);
  delay(1200);
  gateServo.write(GATE_CLOSE);
  delay(800);
}

/* ================= SETUP ================= */
void setup() {

  Serial.begin(9600);

  Wire.begin();
  lcdPark.init(); lcdPark.backlight();
  lcdAir.init();  lcdAir.backlight();

  gateServo.attach(SERVO_PIN);
  gateServo.write(GATE_CLOSE);

  for(int i=0;i<6;i++){
    pinMode(slotIR[i][0], INPUT);
    pinMode(slotIR[i][1], INPUT);
    slotOccupied[i] = false;
  }

  pinMode(ENTRY_IR, INPUT);
  pinMode(EXIT_IR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(EXHAUST_FAN, OUTPUT);
  pinMode(EMERGENCY_BTN, INPUT_PULLUP);

  digitalWrite(BUZZER, LOW);
  digitalWrite(EXHAUST_FAN, LOW);

  /* ===== BASELINE CALIBRATION ===== */
  lcdAir.setCursor(0,1);
  lcdAir.print("Calibrating...");
  delay(5000);

  long s1 = 0, s2 = 0;
  for(int i=0;i<50;i++){
    s1 += analogRead(MQ135);
    s2 += analogRead(MQ2);
    delay(50);
  }
  mq135_base = s1 / 50;
  mq2_base   = s2 / 50;

  lcdAir.clear();

  /* ===== STARTUP MESSAGE ===== */
  lcdPark.setCursor(1,1);
  lcdPark.print("FIND YOUR");
  lcdPark.setCursor(1,2);
  lcdPark.print("PARKING SPACE");
  delay(3000);
  lcdPark.clear();
}

/* ================= LOOP ================= */
void loop() {

  /* ===== EMERGENCY CHECK ===== */
  if (digitalRead(EMERGENCY_BTN) == LOW) {
    emergencyActive = true;
  }

  if (emergencyActive) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(EXHAUST_FAN, HIGH);
    gateServo.write(GATE_OPEN);

    lcdPark.clear();
    lcdPark.setCursor(2,1);
    lcdPark.print("EMERGENCY");

    lcdAir.clear();
    lcdAir.setCursor(0,1);
    lcdAir.print("EVACUATE AREA");

    delay(1000);
    return;
  }

  digitalWrite(BUZZER, LOW);

  /* ================= GAS READ (DEMO TUNED) ================= */

  int raw_mq135 = analogRead(MQ135);
  int raw_mq2   = analogRead(MQ2);

  int mq135 = raw_mq135 - mq135_base;
  int mq2   = raw_mq2   - mq2_base;

  if(mq135 < 0) mq135 = 0;
  if(mq2   < 0) mq2   = 0;

  mq135 = constrain(mq135, 0, 400);
  mq2   = constrain(mq2, 0, 400);

  /* Clean air base + smoke increase */
  CO  = 5  + map(mq135, 0, 400, 0, 150);
  CO2 = 400 + map(mq135, 0, 400, 0, 1600);
  NH3 = 10 + map(mq135, 0, 400, 0, 200);

  SMK = 2  + map(mq2, 0, 400, 0, 300);
  LPG = 3  + map(mq2, 0, 400, 0, 250);

  int pollution = (mq135 + mq2) / 2;

  N2 = 78 - map(pollution, 0, 400, 0, 20);

  if(pollution < 40)       airStatus = "GOOD ";
  else if(pollution <150)  airStatus = "MOD  ";
  else                     airStatus = "BAD  ";

  digitalWrite(EXHAUST_FAN, pollution > 150);

  /* ================= SLOT STATUS ================= */
  int freeSlots = 0;
  for(int i=0;i<6;i++){
    if(digitalRead(slotIR[i][0])==LOW &&
       digitalRead(slotIR[i][1])==LOW){
      slotOccupied[i]=true;
    } else {
      slotOccupied[i]=false;
      freeSlots++;
    }
  }

  /* ================= ENTRY / EXIT ================= */
  static bool ep=HIGH, xp=HIGH;
  bool en=digitalRead(ENTRY_IR);
  bool xn=digitalRead(EXIT_IR);

  if(ep==HIGH && en==LOW && freeSlots>0){
    totalEntered++;
    operateGate();
  }
  if(xp==HIGH && xn==LOW){
    totalExited++;
  }
  ep=en; xp=xn;

  /* ================= PARKING DISPLAY ================= */
  lcdPark.setCursor(0,0);
  lcdPark.print("PARKING STATUS     ");

  lcdPark.setCursor(0,1);
  lcdPark.print("G1:");
  lcdPark.print(slotOccupied[0]?"PK":"EM");
  lcdPark.print(" G2:");
  lcdPark.print(slotOccupied[1]?"PK":"EM");
  lcdPark.print(" G3:");
  lcdPark.print(slotOccupied[2]?"PK":"EM");

  lcdPark.setCursor(0,2);
  lcdPark.print("F1:");
  lcdPark.print(slotOccupied[3]?"PK":"EM");
  lcdPark.print(" F2:");
  lcdPark.print(slotOccupied[4]?"PK":"EM");
  lcdPark.print(" F3:");
  lcdPark.print(slotOccupied[5]?"PK":"EM");

  lcdPark.setCursor(0,3);
  lcdPark.print("IN:");
  lcdPark.print(totalEntered);
  lcdPark.print(" OUT:");
  lcdPark.print(totalExited);
  lcdPark.print(" FREE:");
  lcdPark.print(freeSlots);
  lcdPark.print("   ");

  /* ================= AIR DISPLAY ================= */
  lcdAir.setCursor(0,0);
  lcdAir.print("AIR:");
  lcdAir.print(airStatus);
  lcdAir.print("        ");

  lcdAir.setCursor(0,1);
  lcdAir.print("CO:");
  lcdAir.print(CO);
  lcdAir.print(" CO2:");
  lcdAir.print(CO2);
  lcdAir.print("   ");

  lcdAir.setCursor(0,2);
  lcdAir.print("SMK:");
  lcdAir.print(SMK);
  lcdAir.print(" LPG:");
  lcdAir.print(LPG);
  lcdAir.print("   ");

  lcdAir.setCursor(0,3);
  lcdAir.print("NH3:");
  lcdAir.print(NH3);
  lcdAir.print(" N2:");
  lcdAir.print(N2);
  lcdAir.print("   ");

  delay(800);
}