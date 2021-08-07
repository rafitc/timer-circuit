/*
  DS1307 RTC (Real-Time-Clock) Example

  Uno       A4 (SDA| black), A5 (SCL)
  Mega      20 (SDA), 21 (SCL)
  Leonardo   2 (SDA),  3 (SCL)
 */

#include <Wire.h>
#include <DS1307.h>

int state ; 
uint8_t currentHour ;
uint8_t resetHour = 7;

int relay_one = 9; //Relay One 
int relay_two = 10; //Rekay Two

int led_1 = 7; //led ~ relay one 
int led_2 = 11; //led ~ relay two 

DS1307 rtc;


void setup()
{
  Serial.begin(9600);
  /*only set the date+time one time*/
  pinMode(relay_one, OUTPUT);
  pinMode(relay_two, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);

  /*stop/pause RTC*/
  // rtc.stop();
  
  /*start RTC*/
  rtc.start();
  digitalWrite(relay_two, !LOW);
  digitalWrite(relay_one, !LOW);
  Serial.println("initialising ");
  //timeReset();
}


void loop()
{
  
  uint8_t sec, min, hour, day, month;
  uint16_t year;

  /*get time from RTC*/
  rtc.get(&sec, &min, &hour, &day, &month, &year);
  currentHour = hour;
  /*wait a second*/
  delay(1000);
  Serial.println(currentHour);
  state =  currentHour%2;
  
  digitalWrite(relay_one, !state);
  digitalWrite(led_1, state);


  if(currentHour<=7){
    digitalWrite(relay_two, !HIGH);
    digitalWrite(led_2, HIGH);
  }
  else if((currentHour>=8) && (currentHour<=13)){
    digitalWrite(relay_two, !LOW);
    digitalWrite(led_2, LOW);
  }
  else{
    timeReset();
  }
}


void timeReset(){
  Serial.println("Reset");
  rtc.set(0, 0, 1, 13, 10, 2020); /*08:00:00 24.12.2014 //sec, min, hour, day, month, year*/
}
