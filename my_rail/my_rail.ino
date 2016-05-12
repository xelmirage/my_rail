#include <Wire.h> 
#include <Stepper.h>
#include <LiquidCrystal_I2C.h>

#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_CENTER 5

#define STAT_IDLE 0
#define STAT_INTVL 1
#define STAT_EXP 2
#define STAT_STEP 3






uint8_t uiKeyCodeFirst = KEY_NONE;
uint8_t uiKeyCodeSecond = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;


uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;


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
int totalstep = 0;
void forward()
{
  
}



void uiStep(void) {
  uiKeyCodeSecond = uiKeyCodeFirst;
  int x, y, z, stick_value;
  x = analogRead (JoyStick_X) - 512;
  y = analogRead (JoyStick_Y) - 512;
  z = digitalRead (JoyStick_Z);

  if (abs(x) > 250 || abs(y) > 250)
  {
    if (abs(x) > abs(y))
    {
      if (x > 0)
      {
        uiKeyCodeFirst = KEY_RIGHT;
      }
      else if (x < 0)
      {
        uiKeyCodeFirst = KEY_LEFT;
      }


    }
    else if (abs(x) < abs(y))
    {
      if (y > 0)
      {
        uiKeyCodeFirst = KEY_UP;
      }
      else if (y < 0)
      {
        uiKeyCodeFirst = KEY_DOWN;
      }

    }
  }
  else if (z == 0)
  {
    uiKeyCodeFirst = KEY_CENTER;
  }
  else
  {
    uiKeyCodeFirst = KEY_NONE;
  }
  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = KEY_NONE;







}
void drawMenu(void) {
  uint8_t i, h;
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("INTVL  EXP  STEP");
  
  
}
void updateMenu(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;

  switch ( uiKeyCode ) {
    case KEY_UP:

      menu_redraw_required = 1;
      break;
    case KEY_DOWN:

      menu_redraw_required = 1;
      break;
    case KEY_LEFT:

      menu_redraw_required = 1;
      break;
    case KEY_RIGHT:

      menu_redraw_required = 1;
      break;
    case KEY_CENTER:
      isRun = !isRun;
      menu_redraw_required = 1;
      break;
  }
}


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
  attachInterrupt(0, keypressed, RISING);
  attachInterrupt(1, triggerkeypressed, RISING);
  isRun = false;
}

void loop() {
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = digitalRead (JoyStick_Z);


  if (isRun == true)
  {
    // step one revolution  in one direction:

    myStepper.step(1);
    totalstep++;

    // step one revolution in the other direction:
    lcd.clear();
    lcd.print(totalstep);
    if (totalstep == 5)
    {
      lcd.clear();
      lcd.print("shot");
      delay(500);
      digitalWrite(triggerPin, HIGH);
      delay(200);
      digitalWrite(triggerPin, LOW);
      totalstep = 0;
      delay(500);
      lcd.clear();
      lcd.print("forward");
    }
    delay(1000);
  }
  else
  {
    uiStep();
	

    if (  menu_redraw_required != 0 ) {
      lcd.clear();
      lcd.print(uiKeyCode);
      menu_redraw_required = 0;
    }
    updateMenu();
  }
  drawMenu();
  //updateMenu();

}
void keypressed()
{
  isRun = false;
}
void triggerkeypressed()
{
  int i;
  digitalWrite(triggerPin, HIGH);
  for (i = 1; i < 1000; ++i)
  {

  }
  digitalWrite(triggerPin, LOW);
  
}


