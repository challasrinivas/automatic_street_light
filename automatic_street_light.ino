// 12. SREET LIGHT



#include <SoftwareSerial.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <SimpleTimer.h>

const int voltageSensor = A0;
SimpleTimer timeroperation;
SimpleTimer timer;

int led=6;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int count = 0;
char singleChar;
String readMsg;

int h = 17;
int m = 59;
int s = 50;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value1 = 0;
int timeup = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  timeroperation.setInterval(1000, timeroperfunction);
  timer.setInterval(1000, DigitalClockDisplay);
  lcd.begin(16, 2);                                               
  lcd.clear();     
  
  lcd.setCursor(0, 0);                                           
  lcd.print("  WELCOME TO ");    
  lcd.setCursor(0, 1);
  lcd.print(" THE PROJECT ");   
  delay(2000);
  lcd.clear();           
  Serial.println(" WELCOME TO THE STREET LIGHT PROJECT "); 

}

 void loop() {

  /*FIND INPUT VOLTAGE FROM THE VOLTAGE SENSOR*/ 

  value1 = analogRead(voltageSensor);
  //Serial.print("pin vol:");
  //Serial.println(value1);
  vOUT = (value1 * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("VOLTAGE = ");
  Serial.println(vIN);
  delay(2000); 
  lcd.clear(); 
  lcd.setCursor(0, 1);
  lcd.print("VOLTAGE: ");    
  lcd.print(vIN);lcd.print("V");
  delay(2000);
  lcd.clear(); 
  
/*AUTOMATIC STREET LIGHT BASED ON TIMER*/
  
  // timeropvoideration.run();
  timer.run();
}

void timeroperfunction() {

Serial.println(F("TIMER OPERATION TRIGGER"));

 if ( h == 18 && m == 00 && s == 00)
{
  digitalWrite(led,HIGH);
Serial.println("lights ON");
}
else if (h>17 && h<20){
    analogWrite(led,100);
    Serial.println("LIGHT IS DIM");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" LIGHT IS LOW DIM ");
    delay(2000);
    lcd.clear();
  }
  else if (h>19 && h<22){
    analogWrite(led,200);
    Serial.println("LIGHT IS DIM(MEDIUM)");
    delay(500); lcd.clear();lcd.setCursor(0,0);
  lcd.print("LIGHT IS DIM(MEDIUM)  ");
  delay(2000);
 
  }
  else if ((h>21 && h<25) ||(h>-1 && h<4)){
    analogWrite(led,255);
    Serial.println("LIGHT IS HIGH");
    delay(500);lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LIGHT IS HIGH  ");
    delay(2000);lcd.clear();
  }
else if (h>=4 && h<6) {
    analogWrite(led,200);
    Serial.println("LIGHT IS DIM");
    delay(500);
    lcd.setCursor(0,0);
    lcd.print(" LIGHT IS DIM ");
    delay(2000);lcd.clear();
}
else if(h>5 && h<7){
  analogWrite(led,100);
    Serial.println("LIGHT IS LOW DIM");
    delay(500);lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" LIGHT IS LOW DIM ");
   delay(2000);lcd.clear();
}
    else{
    analogWrite(led,0);
    Serial.println("LIGHT IS OFF");
    delay(500);lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LIGHT IS OFF ");
    delay(2000);lcd.clear();
  }
  }


void DigitalClockDisplay() {
  if(h>23){
    h=0;
  }
 // else{

  s++;
  if (s == 59) {
    s = 0;
    if (m == 59) {
      m = 00;
      h++;
      s = 0;
    } else {
      m++;
      s = 0;
    }
  }
 // }

  lcd.setCursor(4, 1);
  lcd.print(h);
  Serial.print(h);
  printDigits(m);
  printDigits(s);
  Serial.println();
  if (h == 18 && timeup == 0) {
    timeup = 1;
    timer.setTimeout(1000, timeroperfunction);
      }
      }

void printDigits(int digits) {
     Serial.print(":");
     lcd.print(":");
  if (digits < 10) {
    Serial.print('0');
    lcd.print('0');
  }
  Serial.print(digits);
  lcd.print(digits);
}



