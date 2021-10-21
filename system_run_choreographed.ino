

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
int homeCount=0; //This counts the number of times you've homed. it was a debungging tool, probably don't need it now
#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
long newPosition;
long oldPosition  = -999;
const int homeSwitch = 8; //Pin that the home switch is attached to. It's just a button
const long liftValue = 7500; //This is the value the encoder will try to hit, you might want to change it if the lift arms are pushing the turet up too hard, or not enough
bool turretState; //(HIGH is up, LOW is down)

  bool homeSwitchState;
  bool prevHomeSwitchState;


void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
  pinMode(homeSwitch,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  

  Home();
  
}



void loop() {
  
int turret_rotate=random(500,3000);
int turret_direction =random(0,2);
if (turret_direction==0){
  TurretCW();
}
else{
  TurretCCW();
}
delay(turret_rotate);
TurretHalt();

RaiseGun();
FireGun();
delay(random(250,2000));
CeaseFire();
LowerGun();

//if (turret_direction==0){
//  TurretCCW();
//}
//else{
//  TurretCW();
//}
//delay(turret_rotate);
//TurretHalt();
delay(1500);
  
 
    
}


//FUNCTIONS-----------------


void RaiseGun(){
  while(turretState==LOW){
    if (turretState==LOW && newPosition<(liftValue)){
    Raise();
    newPosition = myEnc.read();
    if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    }
  }
    else if (turretState==LOW && newPosition>=liftValue){
      turretState=HIGH;
      Halt();
    }
  }
}

void LowerGun(){
  while(turretState==HIGH){
   if (turretState==HIGH && newPosition>100){
    Lower();
    newPosition = myEnc.read();
    if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
      }
    }
    else if (turretState==HIGH && newPosition<=100){
      turretState=LOW;
      Halt();
    }
  }
 }

void readHomeSwitch(){
  homeSwitchState=digitalRead(homeSwitch);
}

void Home(){
  readHomeSwitch();
  if(homeSwitchState==LOW){
  while (homeSwitchState==LOW){
    readHomeSwitch();
    Lower();
  }
  }
  Halt();
  myEnc.write(0);
  Serial.print("Home Reached - ");
  Serial.println(homeCount);
  homeCount = homeCount+1;
  
}

void Raise(){
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void Lower(){
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

void Halt(){
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void TurretCW(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}

void TurretCCW(){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
}

void TurretHalt(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void FireGun(){
  digitalWrite(10,HIGH);
}

void CeaseFire(){
  digitalWrite(10,LOW);
}
