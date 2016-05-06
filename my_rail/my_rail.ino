#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
const int stepsPerRevolution = 200; // change this to fit the number of steps per revolution
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// for your motor
volatile bool isRun = false;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 5, 6, 7, 8);


int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 3; // key

int triggerPin = 9; // key
int totalstep=0;

void setup() {
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
  pinMode (triggerPin, OUTPUT);

  
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  lcd.init(); // initialize the lcd
  lcd.backlight(); //Open the backlight
  attachInterrupt(0, keypressed,RISING);
  attachInterrupt(1, triggerkeypressed,RISING);
  isRun = true;
}

void loop() {
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
   z = digitalRead (JoyStick_Z);

  
  if (isRun == true)
  {
    // step one revolution  in one direction:
    lcd.clear();
    lcd.print("forward");
    myStepper.step(1);
    totalstep++;

    // step one revolution in the other direction:
    
  }
  if(totalstep==20)
  {
    delay(500);
    digitalWrite(triggerPin,HIGH);
    delay(200);
    digitalWrite(triggerPin,LOW);
    totalstep=0;
    delay(500);
  }

delay(10);

  
}
void keypressed()
{
  isRun = false;
}
void triggerkeypressed()
{
  int i;
  digitalWrite(triggerPin,HIGH);
  for(i=1;i<1000;++i)
  {
    
  }
  digitalWrite(triggerPin,LOW);
}


