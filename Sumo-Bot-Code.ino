/* 
 * By: Tanay Patel, Blake Stephenson
 * Feb 6, 2020
 * 
 * Arduino Sumbot's Code for 2020 McMaster SumoBot Competition
 * 
 */

void setup() {
  Serial.begin(9600);
}

//H-Bridge Control Pins
  int IN1 = 6;
  int IN2 = 7;
  int IN3 = 2;
  int IN4 = 4;
  int ENA = 3;
  int ENB = 5;
  int AO = A0;
  int AONE = A1;
  int ATWO = A2;

//Ultra-Sonic Sensor #1 Control
  int ECHO1 = 11;
  int TRIG1 = 10;

  int IRLIMITS = 150;
  int KillDistance = 15;
  int RegSpd = 120;
 
void loop() {
  //Setting Pin-Modes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ECHO1, INPUT);
  pinMode(TRIG1, OUTPUT);

  pinMode(AO, INPUT);
  pinMode(AONE, INPUT);
  pinMode(ATWO, INPUT);

  //Inital Robot Motor Movement.
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, HIGH);
  
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); 
  
  //Initial Delay
  delay(5000);
  
  
  
  while(true){
    float distance1 = getDistance(ECHO1, TRIG1);
    int speed1 = setMotorSpeed(distance1);

    //IR Sensors Input
    int Anal1 = analogRead(AO);
    int Anal2 = analogRead(AONE);
    int Anal3 = analogRead(ATWO);
    Anal1 = analogRead(AO);
    Anal2 = analogRead(AONE);
    Anal3 = analogRead(ATWO);
    Anal1 = analogRead(AO);
    Anal2 = analogRead(AONE);
    Anal3 = analogRead(ATWO);
      
    //Checks If The Bot Is Inside The Track or lifted up.
    bool OutsideBoundary = false;
    OutsideBoundary = InsideBoundaryLine(Anal1, Anal2);
    Serial.println(distance1);
    //Serial.println(Anal2);
    if(OutsideBoundary){
        ExecuteReversing();
        Serial.println("REEEE");
    }


    //Checks if bot sees enemy bot.
    if(distance1 < KillDistance){
      analogWrite(ENA, speed1);
      analogWrite(ENB, speed1);
    }
    else{
      analogWrite(ENA, RegSpd);
      analogWrite(ENB, RegSpd);
    }
    
    delay(5);
  }  
  
}

//Returns Ultra Sonic Sensor reading in CM
float getDistance(int ECHO, int TRIG){
  
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  
  //Ultra-Sonic Input
  digitalWrite(TRIG, LOW);
  delay(10);
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);

  float duration = pulseIn(ECHO, HIGH);
  duration += 40;
  
  float distance = (duration/2) * 343.42 * 0.0001;

  return distance;
}



//Controls Motor Speeds
int setMotorSpeed(float distance){
  int spd = 0;
  
  if(distance < KillDistance){
    spd = 255;
    }
  else{
    spd = RegSpd;
    }
  return spd;
}


//Checks IR Sensor
float InsideBoundaryLine(int Anal1,int Anal2){  
  bool Inside = false;
  if((Anal1 > IRLIMITS) or (Anal2 > IRLIMITS)){
     Inside = true;
  }
  return Inside;
}



//Reverseing Manouver
void ExecuteReversing(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, LOW);

  delay(5);

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  delay(600);

  digitalWrite(IN1, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, HIGH);
}
