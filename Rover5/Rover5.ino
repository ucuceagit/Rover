#include <NewPing.h>

#define  echoR 2
#define  trigR 3
#define  echoM 4
#define  trigM 5
#define  echoL 6
#define  trigL 7

#define  M1DIR 8
#define  M1RUN 9
#define  M2RUN 10
#define  M2DIR 11

#define MAX_DISTANCE 200
#define SAFE_DISTANCE 25

NewPing sonarL(trigL, echoL, MAX_DISTANCE);
NewPing sonarM(trigM, echoM, MAX_DISTANCE);
NewPing sonarR(trigR, echoR, MAX_DISTANCE);


enum{
  LEFT,
  RIGHT,
  FORWARD,
  BACK,
  HALT
}botPosition = LEFT;

void setup() {
  pinMode(M1DIR, OUTPUT);
  pinMode(M1RUN, OUTPUT);
  pinMode(M2RUN, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  Serial.begin(9600);

  
}

void loop() {

  int x = roamAround();

    switch(x){
       case LEFT:
         Serial.println("Moving Left");
         driveLeft();
         delay(1000);
         haltDrive();         
         break;
       case RIGHT:
         Serial.println("Moving Right");
         driveRight();
         delay(1000);
         haltDrive();
         break;
        case FORWARD:
          Serial.println("Moving Forward");
          driveForward();
          delay(1000);
          haltDrive();
          break;
          
        case BACK:
          Serial.println("Moving Forward");
          driveForward();
          delay(1000);
          haltDrive();
          break;
          
        default:
          Serial.println("HALT");
          break;
     }
  delay(50);
}

void driveForward()
{
  analogWrite(M1RUN,200);
  analogWrite(M2RUN,200);
  
  digitalWrite(M1DIR,HIGH);
  digitalWrite(M2DIR,HIGH);
}

void driveBack ()
{
  analogWrite(M1RUN,200);
  analogWrite(M2RUN,200);
  
  digitalWrite(M1DIR,LOW);
  digitalWrite(M2DIR,LOW);
}

void driveLeft()
{
  analogWrite(M1RUN,180);
  analogWrite(M2RUN,200);
    
  digitalWrite(M1DIR,LOW);
  digitalWrite(M2DIR,HIGH);
}

void driveRight()
{
  analogWrite(M1RUN,200);
  analogWrite(M2RUN,180);
    
  digitalWrite(M1DIR,HIGH);
  digitalWrite(M2DIR,LOW);
}

void haltDrive()
{
  digitalWrite(M1RUN,LOW);
  digitalWrite(M2RUN,LOW);
}

int roamAround()
{
   int distL = sonarL.ping_cm();
   int distM = sonarM.ping_cm();
   int distR = sonarR.ping_cm();

   Serial.print(distL); Serial.print(" "); 
   Serial.print(distM); Serial.print(" ");
   Serial.println(distR);

  if(distM <= SAFE_DISTANCE){
    if(distL >=  distR){
       botPosition = LEFT;
    }else{
       botPosition = RIGHT;
    }
  }else if(distL <= SAFE_DISTANCE){
     botPosition = RIGHT;
  }else if(distR <= SAFE_DISTANCE){
    botPosition = LEFT;
  }else{
    botPosition = FORWARD;
  }
  
  return botPosition; 
}

