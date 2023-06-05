#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int BUZZER = 13;
const int analogIn = A3;
int lightSensorPin = A1;
int umidade;
int motorPin = 5;
int motorPin2 = 3;
int pinVel = 6;
LiquidCrystal_I2C lcd(0x20,16,2);
int RawValue = 0;
double Voltage = 0;
int analogValue = 0;
int tempC = 0;

void setup(){
  pinMode(A2, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(pinVel, OUTPUT);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}

void loop(){
  analogValue = analogRead(lightSensorPin);
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000;
  tempC = (Voltage - 500) * 0.1;
  
  // TEMPERATURA:
  if(tempC < 10){
    for(int i = 0; i < 6; i++){
      tone(BUZZER, 500);
      lcd.setCursor(0,0);
      lcd.print("Temp. Baixa");
      lcd.setCursor(0,1);
      lcd.print("Temp: ");
      lcd.print(tempC);
      delay(250);
      noTone(BUZZER);
      delay(250);
    }
    lcd.clear();
  }
  else if (tempC > 21) {
    for(int i = 0; i < 6; i++){
      tone(BUZZER, 500);
      lcd.setCursor(0, 0);
      lcd.print("Temp. Alta");
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.print(tempC);
      delay(250);
      noTone(BUZZER);
      delay(250);
    }
    lcd.clear();
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(tempC);
    delay(5000);
    lcd.clear();
  }
  // FIM TEMPERATURA
  
  // ===========================================================
  
  // UMIDADE:
  umidade = analogRead(A0);
  int pwm = 255;
  analogWrite(pinVel, pwm);
  if(umidade > 450){
    for(int i = 0; i < 6; i++){
      digitalWrite(motorPin2, LOW);
      lcd.setCursor(0,0);
  	  lcd.print("Solo Umido");
      delay(250);
    }
    lcd.clear();
  }
  else if(umidade < 450){
    for(int i = 0; i < 6; i++){
      digitalWrite(motorPin, LOW);
      digitalWrite(motorPin2, HIGH);
      tone(BUZZER, 500);
      lcd.setCursor(0,0);
  	  lcd.print("Solo Seco");
      delay(250);
      noTone(BUZZER);
      delay(250);
    }
    lcd.clear();
  }
  // FIM UMIDADE
  
  // ===========================================================
  
  // LUZ:
  if(analogValue < 149){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Luz aceitavel");
    delay(5000);
    lcd.clear();
  }
  else if(analogValue >= 150 && analogValue <= 249){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
    delay(5000);
    lcd.clear();
  }
  else{
    for(int i = 0; i < 6; i++){
      tone(BUZZER, 500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ambiente muito");
      lcd.setCursor(0,1);
      lcd.print("claro");
      delay(250);
      noTone(BUZZER);
      delay(250);
    }
    lcd.clear();
  }
}