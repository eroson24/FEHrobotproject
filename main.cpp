/****************************************/
/*      Proteus Exploration #2          */
/*      OSU FEH Spring 2025             */
/*      Mark Oyster, Erol Sonmez,       */
/*      Reagan Massey, Austin Toczynski */
/*      02/14/2025  Version 3.0.1       */
/****************************************/

/* Include preprocessor directives */

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
#include <FEHRCS.h>
#include <FEHSD.h>
#include <stdio.h>
#include <string.h>


//declare motors.
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
FEHMotor back_motor(FEHMotor::Motor2,9.0);
FEHMotor tread_motor(FEHMotor::Motor3,9.0);



void moveRobotTime(int strength, double time, char direction[]) {

  //move forward for time
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }
  //move back right for time
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  //move back left for time
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  else if (strcmp(direction, "backward") == 0){
    left_motor.SetPercent(strength);
    right_motor.SetPercent(strength);
    Sleep(time);
  }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

}

void moveRobot(int strength, char direction[]) {

  //move forward for time
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(strength);
  }
  //move back right for time
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
  }
  //move back left for time
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
  }
  else if (strcmp(direction, "backward") == 0){
    left_motor.SetPercent(strength);
    right_motor.SetPercent(strength);
  }
}

// declare optosensor
AnalogInputPin optosensor(FEHIO::P1_0);

// detectLine function for robot
bool detectLine(int voltage) {
    bool voltageDetected;
    if (optosensor.Value() > voltage) {
        voltageDetected = true;
    } else {
        voltageDetected = false;
    }
    return voltageDetected;
}

//clockwise is true
// turn function for robot
int turn(int strengthPercent, double seconds, bool clockwise) {
    if (clockwise) {
        right_motor.SetPercent(strengthPercent);
        left_motor.SetPercent(strengthPercent);
        back_motor.SetPercent(strengthPercent);
        Sleep(seconds);
        right_motor.SetPercent(0);
        left_motor.SetPercent(0);
        back_motor.SetPercent(0);
    } else {
        right_motor.SetPercent(-strengthPercent);
        left_motor.SetPercent(-strengthPercent);
        back_motor.SetPercent(-strengthPercent);
        Sleep(seconds);
        right_motor.SetPercent(0);
        left_motor.SetPercent(0);
        back_motor.SetPercent(0);
    }
    return 0;
}

float actualPower(float desiredPower) {
float actualPower = (11.5/Battery.Voltage()) * desiredPower;
return actualPower;
}

//Declare CdS cell sensor
AnalogInputPin CdS_cell(FEHIO::P0_0);

int main(void)
{
  //Clear Screen for writing
  LCD.Clear();
  LCD.SetFontColor(WHITE);

  // declare constants
  float CdS_Value = 0;
  const float RED_VALUE = .3;
  const float BLUE_VALUE = .4;
  
  const float NINETY_DEGREE_TURN = .5;
  char Forward[] = "forward";
  char Backward[] = "backward";
  float x, y;

  float strength = actualPower(50);
  double time = .5;

  //wait until red light turns on to start
  while (CdS_Value < RED_VALUE)
  {
  CdS_Value = CdS_cell.Value();
  }
  //Press start button
  moveRobotTime(strength, time, Backward);
  Sleep(1.0);
  moveRobotTime(strength, time, Forward);

  //Turn towards ramp
  time = 0.2;
  turn(strength, time, true);
  time = 5.0;

  //move towards and up ramp
  moveRobotTime(strength, time, Forward);

  //turn towards humidifier area
  time = NINETY_DEGREE_TURN;
  turn(strength, time, false);

  //move to light sensor, stops when cds cell detects light
  CdS_Value = CdS_cell.Value();
  while (CdS_Value == 0)
  {
    CdS_Value = CdS_cell.Value();
    moveRobot(strength, Forward);
  }
  right_motor.Stop();
  left_motor.Stop();

  //displays light color to screen and decides which direction to move
  char humidifierButton[10];
  if (CdS_Value == RED_VALUE)
  {
    LCD.SetBackgroundColor(RED);
    LCD.WriteRC("RED", 7, 8);
    char humidifierButton[] = "backRight";
  }
  else if (CdS_Value == BLUE_VALUE)
  {
    LCD.SetBackgroundColor(BLUE);
    LCD.WriteRC("BLUE", 7, 8);
    char humidifierButton[] = "backLeft";
  }

  //move to correct button side
  time = 0.5;
  moveRobotTime(strength, time, humidifierButton);

  //push button
  time = 3.0;
  moveRobotTime(strength, time, Forward);
  Sleep(1.0);

  //Bonus points from here

  //move back to ramp
  time = 5.0;
  moveRobotTime(strength, time, Backward);

  //turn towards ramp
  time = NINETY_DEGREE_TURN;
  turn(strength, time, false);

  //go down ramp to start area
  time = 5.0;
  moveRobotTime(strength, time, Forward);

  //turn towards starting area
  time = NINETY_DEGREE_TURN;
  turn(strength, time, true);

  //find stop light
  
/*
  RCS.InitializeTouchMenu("0910B8VYV");
  int lever = RCS.GetLever();
  LCD.WriteLine(RCS.Time());
  */
  /*
  // milestone 1 part 1 code
  while(!LCD.Touch(&x, &y));
  moveRobot(strength, time, Forward);

  // milestone 1 part 2 code
  while(!LCD.Touch(&x, &y));
  moveRobot(strength, time, Forward);
  moveRobot(strength, time, Backward);
  */
    
  return 0;
}

