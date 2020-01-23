#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#define echo A0
#define triger A1
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

SoftwareSerial mySerial(10, 11);
int maximumRange = 200;
int minimumRange = 00;
long duration, distance;
void setup () {
  Serial.begin(9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);
  mp3_set_volume (25);
  pinMode(echo, INPUT);
  pinMode(triger, OUTPUT);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  delay(100);
}

void loop () {
  digitalWrite(triger, LOW);
  delayMicroseconds(2);
  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW);
  int distance1 = pulseIn(echo, HIGH);
  distance = distance1 / 58.8;
  Serial.print(distance1);
  Serial.print(" ");
  Serial.println(distance);
   display.clearDisplay();
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,5);
  display.print("Nilai Jarak : ");
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,15);
  display.print(distance);
  display.display();
  if (distance <= 30) {
    mp3_play (0);
    delay (3000);
  }

  if (distance >= 50 && distance <= 60) {
    mp3_play (1);
    delay (3000);
  }
  
  else{
  mp3_stop();
  //delay (60000);
  }
  //delay(1000);
}
