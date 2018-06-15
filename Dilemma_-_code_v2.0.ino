

const int joystickInputX = A0; // analog input for x-axis
const int joystickInputY = A1; // analog input for y-axis
const int joystickInputSw = A2; // analog input for y-axis
const int bluffGreenOutput = 13; // digital input for Green Bluff LED
const int bluffRedOutput = 12; // digital input for Red Bluff LED
const int playerGreenOutput = 8; // digital input for Green Player LED
const int playerRedOutput = 9; // digital input for Red Player LED
const int resetSw = 2;

int joystickX = 0; // variable to store x value
int joystickY = 0; // variable to store y value
int reset = 0;
int joystickSw = 0; // variable to store joystick switch value

bool joystickLock = false;
bool playerGreen = false;
bool playerRed = false;
bool bluffGreen = false;
bool bluffRed = false;


void setup() {

  pinMode(joystickInputX, INPUT); // setup x input
  pinMode(joystickInputY, INPUT); // setup y input
  pinMode(joystickInputSw, INPUT); // setup switch input
  pinMode(resetSw, INPUT);
  pinMode(bluffGreenOutput, OUTPUT); // setup green bluff LED output
  pinMode(bluffRedOutput, OUTPUT); // setup red bluff LED output
  pinMode(playerGreenOutput, OUTPUT); // setup green player LED output
  pinMode(playerRedOutput, OUTPUT); // setup red player LED output

  Serial.begin(9600); // Setup serial connection for print out to console

}

void loop() {



  reset = digitalRead(resetSw); // Read the value of the switch and assign to the variable joystickSw.
  joystickX = analogRead(joystickInputX) - 512; // Read the value of the x-axis and assign to the variable joystickX. -512 to centre the value
  joystickY = - analogRead(joystickInputY) + 512; // Read the value of the y-axis and assign to the variable joystickY. -512 to centre the value

  Serial.println(reset);

  if (!joystickLock) {

    /* If joystickSw has an absolute value less than 5 (is cliced), then set all LED Outputs to LOW.
        This acts as the reset function for the game. All LEDs turn off to start the next round.
    */



    if (reset == 1) {

      digitalWrite(bluffGreenOutput, LOW);
      digitalWrite(bluffRedOutput, LOW);
      digitalWrite(playerGreenOutput, LOW);
      digitalWrite(playerRedOutput, LOW);

    }

    /* Below is the code that controls the Bluff lights depending on which direction the joystick is rotated.
        Each LED will only turn on after the joystick returns to centre.
    */

    if (abs(joystickX) > 490) {

      Serial.print("X: ");
      Serial.println(joystickX);

      joystickLock = true;

      if (joystickX > 0 && !bluffGreen) { //when joystickX is greater than 0 (rotate right), and bluffGreen is False

        digitalWrite(bluffGreenOutput, HIGH); //
        digitalWrite(bluffRedOutput, LOW); //
        bluffGreen = true;
        bluffRed = false;

      } else if (joystickX < 0 && !bluffRed) {

        digitalWrite(bluffGreenOutput, LOW);
        digitalWrite(bluffRedOutput, HIGH);
        bluffGreen = false;
        bluffRed = true;

      }

    } else if (abs(joystickY) > 490) {

      Serial.print("Y: ");
      Serial.println(joystickY);

      joystickLock = true;

      if (joystickY > 0 && !playerGreen) {

        digitalWrite(playerGreenOutput, HIGH);
        digitalWrite(playerRedOutput, LOW);
        playerGreen = true;
        playerRed = false;

      } else if (joystickY < 0 && !playerRed) {

        digitalWrite(playerGreenOutput, LOW);
        digitalWrite(playerRedOutput, HIGH);
        playerGreen = false;
        playerRed = true;

      }

    }

  } else if (abs(joystickX) < 100 && abs(joystickY) < 100) {

    joystickLock = false;

  }

  // The following delay of 1000ms is only for debugging reasons (it's easier to follow the values on the serial monitor)
  delay(50); // Probably not needed for most applications

}
