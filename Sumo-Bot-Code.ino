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
  int IN1 = 7;
  int IN2 = 8;
  int IN3 = 2;
  int IN4 = 4;
  int ENA = 3;
  int ENB = 5;
  int AO = A0;
  int AONE = A1;
  int ATWO = A2;
  int DO = 9;

//Ultra-Sonic Sensor #1 Control
  int ECHO1 = 13;
  int TRIG1 = 12;

//Ultra-Sonic Sensor #2 Control
  int ECHO2 = 8;
  int TRIG2 = 7;
 
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
  pinMode(ECHO2, INPUT);
  pinMode(TRIG2, OUTPUT);

  pinMode(AO, INPUT);
  pinMode(AONE, INPUT);
  pinMode(ATWO, INPUT);

  //Inital Robot Motor Movement.
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN2, LOW);
  
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); 
  
  //Initial Delay
  delay(5000);
  
  
  
  while(true){
    float distance1 = getDistance(ECHO1, TRIG1);
    int speed1 = setMotorSpeed(distance1);
    int Anal1 = analogRead(AO);
    int Anal2 = analogRead(AONE);
    int Anal3 = analogRead(ATWO);
      
    //Checks If The Car Is Inside The Track
    float OutsideBoundary = InsideBoundaryLine(Anal1, Anal2, Anal3);

    if(OutsideBoundary){
        ExecuteReversing();
    }

    analogWrite(ENA, speed1);

    
    delay(50);
  }  
  
}




//Returns Ultra Sonic Sensor reading in CM
float getDistance(int ECHO, int TRIG){
  
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  
  //Ultra-Sonic Input
  digitalWrite(TRIG, LOW);
  delay(20);
  digitalWrite(TRIG, HIGH);
  delay(20);
  digitalWrite(TRIG, LOW);

  float duration = pulseIn(ECHO, HIGH);
  duration += 40;
  
  float distance = (duration/2) * 343.42 * 0.0001;

  return distance;
}



//Controls Motor Speeds
int setMotorSpeed(float distance){
  int spd = 0;
  
  if(distance < 20){
    spd = 255;
    }
  else if(distance < 40){
    spd = 200;
    }
  else if(distance < 75){
    spd = 170;
    }
  else{
    spd = 90;
    }
  return spd;
}


//Checks IR Sensor
float InsideBoundaryLine(int Anal1,int Anal2,int Anal3){  
  bool Inside = false;
  if((Anal1 < 760) or (Anal2 < 760) or (Anal3 < 760)){
     Inside = true;
  }
  return Inside;
}



//Reverseing Manouver
void ExecuteReversing(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, HIGH);

  delay(10);

  analogWrite(ENA, 255);
  analogWrite(ENB, 120);

  delay(10);

  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN2, HIGH);
}
