int run;
int stepTime = 1200;
// Turn delay to allow for decel/accel
int turnDelay = 2000;
// defines pins numbers

const int stepX = 2;
const int dirX  = 5;
const int stepY = 3;
const int dirY  = 6;
const int stepZ = 4;
const int dirZ  = 7;
const int enPin = 8;
void setup() {

  // Sets the two pins as Outputs

  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);

  pinMode(stepY,OUTPUT);
  pinMode(dirY,OUTPUT);

  pinMode(stepZ,OUTPUT);
  pinMode(dirZ,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);

  digitalWrite(dirX,HIGH);
  digitalWrite(dirY,LOW);
  digitalWrite(dirZ,HIGH);

}

void loop() {
  String readString;
  String Q;
  run = 0;
  //High = CW
  //LOW = CCW
  digitalWrite(dirX,LOW);
  digitalWrite(dirY,LOW);
  digitalWrite(dirZ,LOW);
  // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  //800 pulses = 4 rotations = 5.4 inches of wire. 
  
  //Currently manual input. Communication between Arduinos and BlackBox was not complete.
  //Input 1, 2, 3 or 4 into the serial monitor to activate dispenser.
  while (Serial.available()) {
      delay(1);
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      if (isControl(c)) {
        //'Serial.println("it's a control character");
        break;
      }
      readString += c; //makes the string readString
      run = 1;    
    } else {
      Serial.println('No');
    }
  } 
  Q = readString;
  if (run==1){
    if (Q=="1") {         
      Serial.println("Dispensing Wire " + Q);
      prime(1);
      dispense(1, 19);
      delay(turnDelay);
      dispense(1, 9);
      delay(turnDelay);
      dispense(1, 5);
      retract(1);
    } else if (Q=="2"){         
      Serial.println("Dispensing Wire " + Q);
      prime(2);
      dispense(2, 19);
      delay(turnDelay);
      dispense(2, 9);
      delay(turnDelay);
      dispense(2, 4);
      retract(2);
    } else if (Q=="3"){         
      Serial.println("Dispensing Wire " + Q);
      prime(3);
      dispense(3, 19);
      delay(turnDelay);
      dispense(3, 9);
      delay(turnDelay);
      dispense(3, 7);
      delay(turnDelay);
      dispense(3, 2);
      retract(3);
    } else if (Q=="4"){         
      Serial.println("Dispensing Wire " + Q);
      prime(2);
      dispense(2, 19);
      delay(turnDelay);
      dispense(2, 10);
      delay(turnDelay);
      dispense(2, 6);
      retract(2);
    } else if (Q=="Test"){         
      Serial.println("Testing");
    } else {
      Serial.println("Unrecognised command");
    }
  } 
}

//Prime used to make up for the distance between cutter and end of nozzle. 
void prime(int wire) {
  if (wire == 1) {
    //Prime Wire
    for(int x = 0; x < 3000; x++) {
      digitalWrite(dirX,HIGH);
      digitalWrite(stepX,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepX,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 2) {
    //Prime Wire
    for(int x = 0; x < 3000; x++) {
      digitalWrite(dirZ,HIGH);
      digitalWrite(stepZ,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepZ,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 3) {
    //Prime Wire
    for(int x = 0; x < 3000; x++) {
      digitalWrite(dirY,HIGH);
      digitalWrite(stepY,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepY,LOW);
      delayMicroseconds(stepTime);
    }
  } else {
  }
  Serial.println("Done Priming");
}

//Length in inches
//Wire by gauge 1 = x, 2 = z, 3 = y.
void dispense(int wire, int length) {
  int steps;
  //800 pulses = 4 rotations = 4 inches of wire. 
  steps = length*800/5;
  if (wire == 1) {
    //Dispense wire
    for(int x = 0; x < steps; x++) {
      digitalWrite(dirX,HIGH);
      digitalWrite(stepX,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepX,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 2) {
    //Dispense wire
    for(int x = 0; x < steps; x++) {
      digitalWrite(dirZ,HIGH);
      digitalWrite(stepZ,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepZ,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 3) {
    //Dispense wire
    for(int x = 0; x < steps; x++) {
      digitalWrite(dirY,HIGH);
      digitalWrite(stepY,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepY,LOW);
      delayMicroseconds(stepTime);
    }
  } else {
  }
  Serial.println("Done Dispensing");
}
//Retract wire back to the initial position 
void retract(int wire) {
  if (wire == 1) {
    //Wait for Cutter
    delay(20000);
    //Retract Wire
    for(int x = 0; x < 1000; x++) {
      digitalWrite(dirX,LOW);
      digitalWrite(stepX,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepX,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 2) {
    //Wait for Cutter
    delay(20000);
    //Retract Wire
    for(int x = 0; x < 1000; x++) {
      digitalWrite(dirZ,LOW);
      digitalWrite(stepZ,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepZ,LOW);
      delayMicroseconds(stepTime);
    }
  } else if (wire == 3) {
    //Wait for Cutter
    delay(20000);
    //Retract Wire
    for(int x = 0; x < 1000; x++) {
      digitalWrite(dirY,LOW);
      digitalWrite(stepY,HIGH);
      delayMicroseconds(stepTime);
      digitalWrite(stepY,LOW);
      delayMicroseconds(stepTime);
    } 
  } else {
  }
  Serial.println("Done Retracting");
  
}