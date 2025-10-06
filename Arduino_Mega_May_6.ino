
//Including LCD Display Library.
#include <LiquidCrystal.h>

//Initialize the LCD library by associating any needed LCD interface with the arduino pin number it is connected to.
const int rs = 10, en = 9, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String Routes [4] = {"C1 -> 1", "C1 -> 2", "C1 -> 3", "Center"}; //Array containing list of available routes to cycle through for the LCD display.

int cycle_val = 0; //Integer used to index through Routes Array.
int ready_button = 2; //Assigning ready button to digital pin 8.
int button_cycle_up = 3; //Assigning cycle up button to digital pin 9.
int button_cycle_down = 4; //Assigning cycle down button to digital pin 10.
int button_ready_state; //Variable used to determine state of ready button.
int button_up_state; //Variable used to determine state of cycle up button.
int button_down_state; //Variable used to determine state of cycle down button.

int FAN_CONTROL_1 = 12;
int FAN_CONTROL_2 = 13;


void setup() {
  lcd.begin(16, 2); //Define size of LCD
  Serial1.begin(9600); //Set baud rate of outgoing serial communication channel 1.
  Serial2.begin(9600); //Set baud rate of outgoing serial communication channel 2.
  pinMode(ready_button, INPUT); //Set ready button as input with pull up resistance.
  pinMode(button_cycle_up, INPUT); //Set cycle up button as input with pull up resistance.
  pinMode(button_cycle_down, INPUT); //Set cycle down button as input with pull down resistance.
  pinMode(FAN_CONTROL_1, OUTPUT);
  pinMode(FAN_CONTROL_2, OUTPUT);
  digitalWrite(FAN_CONTROL_1, HIGH);
  digitalWrite(FAN_CONTROL_2, HIGH);
}

void loop() {
  lcd.setCursor(0, 0); //Sets LCD cursor to 0,0.
  lcd.print("Select Route     "); //Writes Select Route on top row.
  lcd.setCursor(0, 1); //Sets LCD cursor to 0,1.
  lcd.print(Routes[cycle_val] + "     "); //Writes the desired route from the Routes array based on the value of cycle_val.
  button_up_state = digitalRead(button_cycle_up); //Reads the voltage from up button.
  button_down_state = digitalRead(button_cycle_down); //Reads the voltage from down button.
  button_ready_state = digitalRead(ready_button); //Reads the voltage from rady button.

   if (button_up_state == HIGH && button_down_state == LOW && button_ready_state == LOW) { //If the up button is pressed with no other buttons
    cycle_val += 1; //Increase cycle_val by 1.
    if (cycle_val >= 4) { //Keeps cycle_val from going over array indexing values.
      cycle_val = -1; //Sets cycle_val to 0.
    }
    else {
      lcd.setCursor(0, 1); //Sets LCD cursor to 0,1.
      lcd.print(Routes[cycle_val] + "        "); //Writes the desired route from the Routes array based on the value of cycle_val.
      delay(1000); //Delay 1 second.
    }
   }

   if (button_up_state == LOW && button_down_state == HIGH && button_ready_state == LOW) { //If the down button is pressed with no other buttons.
    cycle_val -= 1; //Decrease cycle_val by 1.
    if (cycle_val < 0) { //Keeps cycle_val from going under array indexing values.
      cycle_val = 4; //Sets cycle_val to 7.
    }
    else {
      lcd.setCursor(0, 1); //Sets LCD cursor to 0,1.
      lcd.print(Routes[cycle_val] + "        "); //Writes the desired route from the Routes array based on the value of cycle_val
      delay(1000); //Delay 1 second.
    }
   }

   if (button_up_state == LOW && button_down_state == LOW && button_ready_state == HIGH) { //If the ready button is pressed with no other buttons.
      lcd.clear(); //Clears the LCD display.
      lcd.setCursor(0, 0); //Sets LCD cursor to 0,0.
      lcd.print("Ready?"); //Writes Ready? on the top row of the LCD.
      lcd.setCursor(0, 1); //Sets LCD cursor to 0,1.
      lcd.print("Press and hold"); //Writes Press and hold on the bottom row of the LCD.
      delay(5000); //Delay 5 seconds to allow user to press and hold ready button.
      button_ready_state = digitalRead(ready_button); //Reads voltage of ready button.
      if (button_up_state == LOW && button_down_state == LOW && button_ready_state == HIGH) { //If ready button is held down and no other buttons are pressed.
        lcd.clear(); //Clears the LCD display.
        lcd.setCursor(0, 0); //Sets LCD cursor to 0,0.
        lcd.print("Working...        "); //Writes Working... on the top row of the LCD. 
        lcd.setCursor(0, 1); //Sets LCD cursor to 0,1.
        lcd.print("Please Wait"); //Writes Please Wait on the bottom row of the LCD.
        Serial1.write(cycle_val); //Sends cycle_val to dispensing Arduino Uno
        Serial2.write(cycle_val); //Sends cycle_val to gantry movement Arduino Uno
        delay(100000);
        lcd.clear(); //Clears the LCD display.
      }
      else {
      lcd.clear(); //Clears the LCD display.
      lcd.setCursor(0, 0); //Sets the LCD cursor to 0,0.
      lcd.print("Select Route     "); //Wirtes Select Route on the top row of the LCD.
      }
   }
}
