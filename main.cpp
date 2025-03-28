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
FEHMotor tread_motor(FEHMotor::Motor0,9.0);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor2,9.0);
FEHMotor back_motor(FEHMotor::Motor3,9.0);

//Declare CdS cell sensor
AnalogInputPin CdS_cell(FEHIO::P2_0);

// declare optosensors
AnalogInputPin optosensor_left(FEHIO::P0_0);
AnalogInputPin optosensor_middle(FEHIO::P0_2);
AnalogInputPin optosensor_right(FEHIO::P0_7);

void moveRobotTime(int strength, double time, char direction[]) {

  //move forward for time
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }
  //move back right for time
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(strength);
    back_motor.SetPercent(-strength);
    Sleep(time);
  }
  //move back left for time
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  else if (strcmp(direction, "backward") == 0){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(-strength);
    Sleep(time);
  }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    back_motor.Stop();

}

void moveRobot(int strength, char direction[]) {

  //move forward for time
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
  }
  //move back right for time
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(strength);
    back_motor.SetPercent(-strength);
  }
  //move back left for time
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(-strength);
    back_motor.SetPercent(-strength);
  }
  else if (strcmp(direction, "backward") == 0){
    left_motor.SetPercent(-strength);
    right_motor.SetPercent(strength);
  }
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

//function for finding actual power from proteus battery level
float actualPower(float desiredPower) {
  float batteryVoltage = Battery.Voltage();
  if (batteryVoltage > 11.5){
    batteryVoltage == 11.5;
  }
  float actualPower = ((11.5/batteryVoltage) * desiredPower);
  return actualPower;
  }
  
  
  
  int main(void)
  {
    // declare light sensor input pin
    const float RED_VALUE = .1;
    const float BLUE_VALUE = .7;
    
    //Clear Screen for writing
   
    LCD.SetFontColor(WHITE);
    LCD.Clear();
    Sleep(.1);
   
    // declare constants
    float CdS_Value = 10;
    //for 25 power
    const float NINETY_DEGREE_TURN = 0.68;
    const float FOURTYFIVE_DEGREE_TURN = 0.5 * NINETY_DEGREE_TURN;
    char Forward[] = "forward";
    char Backward[] = "backward";
    char backRight[] = "backRight";
    char backLeft[] = "backLeft";
    float x, y;
    int buttonSide = 0;
    Sleep(.1);
    float strength = 70;
    double time = 0.5;



  //wait until red light turns on to start
  while (CdS_Value > RED_VALUE)
  {
    CdS_Value = CdS_cell.Value();
  }
    //Go forward from start area
    moveRobotTime(50, 2.35, Forward);
    
    //Turn from start area
    turn(strength, FOURTYFIVE_DEGREE_TURN, false);
    
    //Go forward towards apple basket. Robot should be on black
    // tape after this point. 
    moveRobotTime(50, 0.2, Forward);

    // go back
    moveRobotTime(50, 0.8, Backward);
    Sleep(0.2);

    //lower tread motor
    tread_motor.SetPercent(-40);
    Sleep(0.5);
    tread_motor.SetPercent(0);

    // go back forward
    moveRobotTime(50, 0.65, Forward);

    //wait
    Sleep(0.2);

    tread_motor.SetPercent(40);
    Sleep(0.9);
    tread_motor.SetPercent(0);

    // go to bottom of ramp
    moveRobotTime(50, 0.5, backLeft);
    moveRobotTime(50, 3.0, Backward);

    // turn to face ramp
    turn(strength, NINETY_DEGREE_TURN, true);

    // go up ramp
    moveRobotTime(100, 2.5, Forward);

    // use tread to put apple basket down on table
    tread_motor.SetPercent(-40);
    Sleep(0.2);
    tread_motor.SetPercent(0);

    // go backwards slightly
    moveRobotTime(50, 0.5, Backward);

    // turn to face buttons
    turn(strength, NINETY_DEGREE_TURN, false);

    // go forward until right optosensor detects <3.0
    while (optosensor_right.Value() > 3.0)
    {
        moveRobot(50, Forward);
    }

    // turn 45 degrees to face levers
    turn(strength, FOURTYFIVE_DEGREE_TURN, true);

    // go forward a little bit
    moveRobotTime(50, 0.2, Forward);

    // turn approximately 25 degrees to face levers
    turn(strength, NINETY_DEGREE_TURN / 3.6, true);

    // tread push down on lever
    tread_motor.SetPercent(-40);
    Sleep(0.5);
    tread_motor.SetPercent(0);

    // turn approximately 25 degrees to face levers
    turn(strength, NINETY_DEGREE_TURN / 3.6, true);

    // bring tread down under lever
    tread_motor.SetPercent(-40);
    Sleep(0.5);
    tread_motor.SetPercent(0);

    // turn approximately 25 degrees to face levers
    turn(strength, NINETY_DEGREE_TURN / 3.6, false);

    // wait five seconds for bonus
    Sleep(5.0);

    // bring tread up to pull up lever
    tread_motor.SetPercent(40);
    Sleep(0.5);
    tread_motor.SetPercent(0);

    /*
    //Begin line following algorithm
    while (optosensor_left.Value() > 3.328 || optosensor_middle.Value() > 3.328 || optosensor_right.Value() > 3.328)
    {
        moveRobot(50, Backward);
        optosensor_left.Value();
        optosensor_middle.Value();
        optosensor_right.Value();
    }
        */
    
    



  RCS.InitializeTouchMenu("0910B8VYV");
  int lever = RCS.GetLever();
  LCD.WriteLine(RCS.Time());

  return 0;
    
}