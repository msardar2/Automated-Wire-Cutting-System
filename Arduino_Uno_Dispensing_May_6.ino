//DISPENSER CODE
//DISPENSER CODE
//DISPENSER CODE

int Route_Dispensing_key [8] = {0, 1, 2, 3, 4, 5, 6, 7}; //Array to cycle through that will determine the wire and wire length that is dispensed.
int incomingData; //Placeholder value for data coming in from the Arduino Mega.
int Wire_Path_Selection; //Placeholder value for choosing the wire and path from the dispensing key.
int N17const = 163; //0.00612 in/loop OR approx 163 loop/in

const int step_x = 2;
const int dir_x = 5;

const int step_y = 3;
const int dir_y = 6;

const int step_z = 4;
const int dir_z = 7;

const int step_a = 12;
const int dir_a = 13;

void setup() {
  Serial.begin(9600); //Setting baud rate for serial monitor.
  pinMode(step_x, OUTPUT);
  pinMode(dir_x, OUTPUT);
  pinMode(step_y, OUTPUT);
  pinMode(dir_y, OUTPUT);
  pinMode(step_z, OUTPUT);
  pinMode(dir_z, OUTPUT);
  pinMode(step_a, OUTPUT);
  pinMode(dir_a, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    incomingData = Serial.read(); //Reads incoming number from Arduino Mega and assigns incoming data its value.
    Serial.println(incomingData);

    Wire_Path_Selection = Route_Dispensing_key[incomingData];
    prime(Wire_Path_Selection);
    delay(3000); //Delay to match with initial gantry movement
    dispense(Wire_Path_Selection);
    delay(20720); //Delay for cutting.  ((3+3ms)*390*4*2)+1000+1000 = 20720 ms.  See 'Movement' CUTTER loop.
    detach();
    retract(Wire_Path_Selection);
  }
}

// FOR DIRECTIONS: LOW=AWAY, HIGH=TOWARDS
void prime(int Wire_Path_Selection) {
  // C1 -> 1
  if (Wire_Path_Selection == 0) {  //Middle spool
    for(int x = 0; x < N17const*21; x++) {    // Approx 21 inches.
      digitalWrite(dir_y, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_y, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_y, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }
  // C1 -> 2
  if (Wire_Path_Selection == 1) {
    for(int x = 0; x < N17const*21; x++) {    // Approx 21 inches.
      digitalWrite(dir_z, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_z, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_z, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }
  // C1 -> 3
  if (Wire_Path_Selection == 2) {
    for(int x = 0; x < N17const*21; x++) {    //Aprrox 21 inches.
      digitalWrite(dir_a, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_a, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_a, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }
}

void dispense(int Wire_Path_selection) {
  if (Wire_Path_Selection == 0) {   // Selection 0 = Route 1
    // Dispense approx 54 inches for all three for loops.
    // FORWARD FROM START
    for (int x = 0; x < N17const*30; x++) {   //30 inches.
      digitalWrite(dir_y, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_y, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_y, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
    delay(1000);

    // RIGHT FROM CENTER
    for (int x = 0; x < N17const*12; x++) {   //12in
      digitalWrite(dir_y, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_y, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_y, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
    delay(1000);

    // BACKWARDS BEFORE CUT
    for (int x = 0; x < N17const*(12-6.13); x++) {   //12-6.13in to begin wire ending.
      digitalWrite(dir_y, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_y, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_y, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }

  if (Wire_Path_Selection == 1) {
    // Aprrox 54 inches for all three 'for' loops.
    // FORWARD FROM START
    for (int x = 0; x < N17const*30; x++) { //30 inches.
      digitalWrite(dir_z, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_z, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_z, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
    delay(1000);

    // LEFT FROM CENTER
    for (int x = 0; x < N17const*12; x++) {
      digitalWrite(dir_z, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_z, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_z, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
    delay(1000);

    // BACKWARDS BEFORE CUT
    for (int x = 0; x < N17const*(12-6.13); x++) {   // 12-6.13in to begin wire ending.
      digitalWrite(dir_z, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_z, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_z, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }

  if (Wire_Path_Selection == 2) {
    // FORWARD FROM START
    for (int x = 0; x < N17const*36-6.13; x++) {    // 36-6.13in to begin wire ending.
      digitalWrite(dir_a, LOW);
      digitalWrite(dir_x, LOW);
      digitalWrite(step_a, HIGH);
      digitalWrite(step_x, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_a, LOW);
      digitalWrite(step_x, LOW);
      delayMicroseconds(3975);
    }
  }
}

void detach () {
  // Purges cut wire from system onto table.
  for (int x = 0; x < N17const*7; x++) {
    digitalWrite(dir_x, LOW);
    digitalWrite(step_x, HIGH);
    delayMicroseconds(3975);
    digitalWrite(step_x, LOW);
    delayMicroseconds(3975);
  }
}

void retract (int Wire_Path_Selection) {
  // Retracts internal wire 5.5 inches
  if (Wire_Path_Selection == 0) {
    for (int x = 0; x < N17const*5.5; x++) {
      digitalWrite(dir_y, HIGH);
      digitalWrite(step_y, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_y, LOW);
      delayMicroseconds(3975);
    }
  }

  if (Wire_Path_Selection == 1) {
    for (int x = 0; x < N17const*5.5; x++) {
      digitalWrite(dir_z, HIGH);
      digitalWrite(step_z, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_z, LOW);
      delayMicroseconds(3975);
    }
  }

  if (Wire_Path_Selection == 2) {
    for (int x = 0; x < N17const*5.5; x++) {
      digitalWrite(dir_a, HIGH);
      digitalWrite(step_a, HIGH);
      delayMicroseconds(3975);
      digitalWrite(step_a, LOW);
      delayMicroseconds(3975);
    }
  }
}