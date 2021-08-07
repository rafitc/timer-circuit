int relay_1 = 3 ;
int relay_2 = 6 ;

int led_1 = 2;
int led_2 = 9;

int flag_1 = 0;
int flag_2 = 0;

int onStartUpFlag = 0;

unsigned long prev_1 = 0, prev_2 = 0;

unsigned long interval_1 = 3600000; //1hr
unsigned long interval_2 = 1800000; //30mnt

void setup() {
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  Serial.begin(9600);

  digitalWrite(relay_1, !HIGH);
  digitalWrite(led_1, HIGH);
  flag_1 = 1;
  digitalWrite(relay_2, !HIGH);
  digitalWrite(led_1, HIGH);
  flag_2 = 1;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(millis());

  //timer One
  if(millis() - prev_1 >= interval_1 && !flag_1){ //One hr
    prev_1 = millis();
    flag_1 = 1;
    digitalWrite(led_1, HIGH);
    digitalWrite(relay_1, !HIGH);
    Serial.println("Relay One ON++");
  }
  if(millis() - prev_2 >= interval_2 && !flag_2){ //30 mnt
    prev_2 = millis();
    flag_2 = 1;
    digitalWrite(led_1, HIGH);
    digitalWrite(relay_2, !HIGH);
    Serial.println("Relay Two ON++");
  }
  if(flag_1){
    if(millis() - prev_1 >= 8000){
      digitalWrite(led_1, LOW);
      digitalWrite(relay_1, !LOW);
      Serial.println("Relay One OFF--");
      prev_1 = millis();
      flag_1 = 0;
    }
  }
  if(flag_2){
    if(millis() - prev_2 >= 7200000){
      digitalWrite(led_2, LOW);
      digitalWrite(relay_2, !LOW);
      Serial.println("Relay Two OFF--");
      prev_2 = millis();
      flag_2 = 0;
    }
  }
}
//2hr ~ 6second 
//1hr ~ 2mnt 
