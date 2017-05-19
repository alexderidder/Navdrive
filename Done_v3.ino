

/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/


#include <Servo.h>
#include <NewPing.h>

#define SONAR_NUM 2     // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

const int targetDistance = 60; 
const int targetDistanceWall = 50;

int scan;
bool straight = false;
boolean followwall = true;
boolean a = true;
int b  = 500;
boolean turning = false;
Servo leftMotor; 
Servo rightMotor;

int motorNeutral = 93;
int baseMotorSpeed = 3;


int leftMotorSpeed = motorNeutral;
int rightMotorSpeed = motorNeutral;;
NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 3, MAX_DISTANCE), // FRONTSENSOR, trigger, echo
  NewPing(4, 4, MAX_DISTANCE) // RIGHTSENSOR
};
int frontDistance = 400;
int rightDistance = targetDistanceWall;

//time
unsigned long timeSerialDelay = 0;

const int loopPeriod = 100; 
unsigned long timeLoopDelay   = 0;


void setup() {
   Serial.begin(115200);
    
  leftMotor.attach(9); 
  rightMotor.attach(10);
  leftMotor.write(motorNeutral);
   rightMotor.write(motorNeutral);
 delay(5000); 
  
}



void loop() {
  if(millis() - timeLoopDelay >= loopPeriod){

   
    readUltrasonicSensors();
   
    
   
    Serial.print("Distance front ");
    Serial.println(frontDistance);
    Serial.print("Onderkant ");
    Serial.println(scan);
Serial.print("Distance right ");
    Serial.println(rightDistance);
  Serial.println(leftMotor.read());
  Serial.println(rightMotor.read());

  if(scan < 150){
    turnLeft2();
    straight = true;
  }
  else if(frontDistance <= targetDistance  && frontDistance > 0){
       turnLeft();
       straight = false;
        followwall = true;
  }
  else if(straight == true) {
    driveStraight();
  }

    else if(rightDistance > 120 &&  followwall == true && rightDistance != -1){
    
    turnRight();
    followwall = false;
  }
  
  
  
  else if(rightDistance <= 150 && rightDistance > 0){
    
     followWall();
     followwall = true;
    //driveStraight();
  }

  else{
    driveStraight();
  }
  
 
  
    timeLoopDelay = millis();
  }
}

void turnLeft(){
    
   turning = true;
   leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral - 2*baseMotorSpeed);
    delay(400);
   leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral );
    delay(800);

    leftMotor.write(motorNeutral + baseMotorSpeed);
    rightMotor.write(motorNeutral - 2*baseMotorSpeed);
    delay(800);

    
    standStill();
}

void turnLeft2(){

    leftMotor.write(motorNeutral + baseMotorSpeed);
    rightMotor.write(motorNeutral - 2*baseMotorSpeed);
    delay(500);
   turning = true;
   leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral - 2*baseMotorSpeed);
    delay(400);
   leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral );
    delay(1200);

    

    
    standStill();
}

void standStill(){
  leftMotor.write(motorNeutral);
   rightMotor.write(motorNeutral);
   
}

void turnArround(){
  turnLeft();
  turnLeft();
}

void driveStraight(){
  leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral + 2*baseMotorSpeed -1);
    delay(500);
    standStill();
}
void turnRight(){
    
    leftMotor.write(motorNeutral - baseMotorSpeed);
    rightMotor.write(motorNeutral + 2*baseMotorSpeed-1);
    delay(600);
 
   leftMotor.write(motorNeutral);
    rightMotor.write(motorNeutral + 2*baseMotorSpeed );
    delay(1500 );
    standStill();
}

void readUltrasonicSensors()
{ 
  frontDistance = 490;
  rightDistance = 490;
  scan = analogRead(0);
  a = true;
  
   for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    b =  sonar[i].ping_cm() *10;
    if(a == true){
     
    if(b > 0 && b < 2000){
    frontDistance =  b;
    }
    
    a = false;
    }
    else{
     
      if(b > 0 && b < 2000){
        
    rightDistance = b;
      }
    }
  }

  


  

  
  
}


void followWall()
{


    if(targetDistanceWall == rightDistance){

    leftMotorSpeed  = motorNeutral - baseMotorSpeed;
    rightMotorSpeed = motorNeutral + 2*baseMotorSpeed;
    
    }

    else if(targetDistanceWall < rightDistance){
     leftMotorSpeed  = motorNeutral - baseMotorSpeed + 1 ;
    rightMotorSpeed = motorNeutral + 2*baseMotorSpeed ;
      
    }

    else{
      
    leftMotorSpeed  = motorNeutral - baseMotorSpeed;
    rightMotorSpeed = motorNeutral +   2*baseMotorSpeed - 2;
    
    }

    

      leftMotor.write(leftMotorSpeed);
    rightMotor.write(rightMotorSpeed);
     delay(300);
    standStill();
}

