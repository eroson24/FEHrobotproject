/****************************************/
/*      Proteus Exploration #2          */
/*      OSU FEH Spring 2025             */
/*      Mark Oyster, Erol Sonmez,       */
/*      Reagan Massey, Austin Toczynski */
/*      02/14/2025  Version 3.0.1       */
/****************************************/

//include preprocessor directives

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
FEHMotor tread_motor(FEHMotor::Motor0, 9.0);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);
FEHMotor left_motor(FEHMotor::Motor2, 9.0);
FEHMotor back_motor(FEHMotor::Motor3, 9.0);

//declare CdS cell sensor
AnalogInputPin CdS_cell(FEHIO::P3_7);

/*
//declare optosensors (UNUSED)
AnalogInputPin optosensor_left(FEHIO::P0_0);
AnalogInputPin optosensor_middle(FEHIO::P0_2);
AnalogInputPin optosensor_right(FEHIO::P0_7);
*/

void moveRobotTime(int strength, double time, char direction[]) {

  //because the robot has three wheels evenly spaced,
  //the robot can move in six different directions.

  //move forward for time seconds
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }

  //move back right for time seconds
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(strength);
    back_motor.SetPercent(-strength);
    Sleep(time);
  }
  //move back left for time seconds
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(-strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  //move backwards for time seconds
  else if (strcmp(direction, "backward") == 0){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(-strength);
    Sleep(time);
  }
  //move forward and to the right for time seconds
  else if (strcmp(direction, "frontRight") == 0){
    back_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }
  //move forward and to the left for time seconds
  else if (strcmp(direction, "frontLeft") == 0){
    back_motor.SetPercent(strength);
    right_motor.SetPercent(-strength);
    Sleep(time);
  }
    //turn off motors
    right_motor.Stop();
    left_motor.Stop();
    back_motor.Stop();

}

void moveRobot(int strength, char direction[]) {
  //identical to the moveRobotTime function, but runs indefinitely.
  //for use in loops.

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
    back_motor.SetPercent(strength);
  }
  else if (strcmp(direction, "backward") == 0){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(-strength);
  }
}

void turn(int strengthPercent, double seconds, bool clockwise) {
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
}
  
int main(void)
{
    //declare light sensor input values
    const float RED_VALUE = .1;
    const float BLUE_VALUE = .7;
    
    //clear screen for writing
   
    LCD.SetFontColor(WHITE);
    LCD.Clear();

    //initialize RCS connection
    RCS.InitializeTouchMenu("0910B8VYV");
    Sleep(.1);
   
    //declare constants
    float CdS_Value = 10;
    //declare optosensor variables
    float leftOpto = -1, midOpto = -1, rightOpto = -1;
    //declare turn values
    const float NINETY_DEGREE_TURN = 0.49;
    const float FOURTYFIVE_DEGREE_TURN = 0.5 * NINETY_DEGREE_TURN;
    //declare max value detected by optosensors (when the floor is gray, typically)
    //this is used for the optosensors, which are unused in this code. 
    const float MAXGRAYFLOOR = 3.3;
    
    char courseLetter = RCS.CurrentRegionLetter();
    char forward[] = "forward";
    char backward[] = "backward";
    char backRight[] = "backRight";
    char backLeft[] = "backLeft";
    char frontLeft[] = "frontLeft";
    char frontRight[] = "frontRight";
    float x, y;
    float strength = 70;
    
  //note: for tread: positive value is up (clockwise)  
  
  /*
  START!!!
  */
  
  //wait until red light turns on to start
  while (CdS_Value > RED_VALUE)
  {
    CdS_Value = CdS_cell.Value();
  }
  
  //push start button
  moveRobotTime(20, .5, backward);
  Sleep(.2);

  /*
  Compost Bin
  */
   
  //go forward from start area
  moveRobotTime(50, 1.0, forward);
  Sleep(.05);

  //turn to be parallel to bin
  turn(strength, FOURTYFIVE_DEGREE_TURN, false);
  Sleep(.05);

  //move to be in line with bin grips
  if (courseLetter == 'F') {
    moveRobotTime(50, 1.25, forward);
  } else if (courseLetter == 'C')
  {
    moveRobotTime(50, 1.0, forward); 
  } else {
  moveRobotTime(50, 1.34, forward);
  }
  Sleep(.05);

  //turn to face bin
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //move to bin
  moveRobotTime(20, 2.5, forward);
  Sleep(.05);

  //rotate bin clockwise
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move away from bin
  moveRobotTime(20, .5, backward);
  Sleep(.05);

  //reset tread
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move to bin
  moveRobotTime(20, .7, forward);
  Sleep(.05);

  //rotate bin clockwise
  tread_motor.SetPercent(-50);
  Sleep(1.0);
  tread_motor.SetPercent(0);
  Sleep(.05);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.0);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move away from bin
  moveRobotTime(20, .5, backward);
  Sleep(.05);

  //reset tread
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move to bin
  moveRobotTime(20, .7, forward);
  Sleep(.05);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);
  
  /*
  Apple Bucket Table
  */

  //move a little back left so robot doesn't bump into stump
  moveRobotTime(50, .5, backLeft);

  //move away from bin until center is in line with basket
  moveRobotTime(50, 1.05, backward);
  Sleep(.05);

  //turn to face basket
  turn(strength, NINETY_DEGREE_TURN * 0.96, true);
  Sleep(.05);

  //back up a little bit
  moveRobotTime(50, 0.3, backward);
  Sleep(.05);

  //lower tread motor
  tread_motor.SetPercent(-40);
  Sleep(2.65);    
  tread_motor.SetPercent(0);

  //move to basket
  moveRobotTime(50, 0.5, forward);
  Sleep(.05);

  //bring tread motor back up with apple basket
  tread_motor.SetPercent(40);
  Sleep(0.82);

  //keep tread motor running on low power to keep apple basket up
  tread_motor.SetPercent(15);

  //go to bottom of ramp
  moveRobotTime(50, 1.0, backLeft);
  moveRobotTime(50, 3.0, backward);
  Sleep(.05);

  //go slightly forward
  moveRobotTime(50, 0.2, forward);
  Sleep(.05);

  //turn to face ramp
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(0.2);

  //go up ramp
  //give slightly less strength to right motor
  right_motor.SetPercent(-90);
  left_motor.SetPercent(100);
  Sleep(2.5);
  right_motor.SetPercent(0);
  left_motor.SetPercent(0);

  //turn slightly to the right
  //if the robot is on course B, turns more.
  if (!courseLetter == 'B') {
  turn(strength, 0.13, true);
  Sleep(.05);
} else {
  turn(strength, 0.18, true);
  Sleep(0.05);
}

  //use table to align straight with wall
  moveRobotTime(50, 0.5, forward);
  Sleep(.05);

  //use tread to put apple basket down on table
  tread_motor.SetPercent(-20);
  Sleep(0.64);
  tread_motor.SetPercent(0);
  Sleep(1.0);

  //move back a little bit
  moveRobotTime(50, 0.42, backward);
  Sleep(.05);

  //put hook facing back
  tread_motor.SetPercent(45);
  Sleep(2.0);
  tread_motor.SetPercent(0);

  //go forward and to the right a little to align with table 
  //to ensure CdS cell consistency
  moveRobotTime(50, 0.25, frontRight);
  Sleep(.05);

  //go forward again to hit table
  moveRobotTime(50, 1.2, forward);
  Sleep(.05);
  
  //move back a little bit
  moveRobotTime(50, 0.58, backward);
  Sleep(.05);

  //rotate 90 degrees counterclockwise
  turn(strength, NINETY_DEGREE_TURN, false);

  //move back to align with wall
  moveRobotTime(50, 1.4, backward);
  Sleep(0.5);

  /*
  Humidifier
  */

  //go forward to CdS cell
  moveRobotTime(50, 1.85, forward);
  Sleep(.05);

  //turn backwards
  turn(strength, NINETY_DEGREE_TURN * 2, true);
  
  //UNUSED OPTOSENSOR CODE
  /*
  //move backward
  moveRobot(30, backward);

  //move forward until optosensors detect the black line
  while (midOpto < MAXGRAYFLOOR || rightOpto < MAXGRAYFLOOR){
    midOpto = optosensor_middle.Value();
    rightOpto = optosensor_right.Value();
  }

  //stop when optosensors detect line
  right_motor.Stop();
  left_motor.Stop();
  Sleep(.05);

  //move forward so center of robot is over black line
  moveRobotTime(50, .3, forward);
*/

  //takes average of 300 CdS cell values
  float CdSAvg = 0;
  for (int i = 0; i < 300; i++){
    CdS_Value = CdS_cell.Value();
    CdSAvg += CdS_Value;
    Sleep(.01);
   }
  CdSAvg /= 300;

  //write value to screen
  LCD.Clear();
  LCD.Write("CdS Averaged Value: ");
  LCD.WriteLine(CdSAvg);
  Sleep(.5);

  //move to be in line with correct button, display color to press on screen
  bool isBlue = false;
  if (CdSAvg <= RED_VALUE)
  {
    LCD.SetBackgroundColor(RED);
    LCD.Clear();
    LCD.WriteRC("RED", 6, 8);
    moveRobotTime(strength, .11, frontLeft);
  }
  else {
    LCD.SetBackgroundColor(BLUE);
    LCD.Clear();
    LCD.WriteRC("BLUE", 6, 8);
    moveRobotTime(strength, .13, frontRight);
    isBlue = true;
  }
  Sleep(.5);

  //push button
  moveRobotTime(strength, 2.0, backward);
  Sleep(.2);

  /*
  Fertilizer Levers
  */

  //get lever from the RCS
  int lever = RCS.GetLever();
  float backToLeverTime = 0;
     
  //check which lever to flip and display letter to screen
  bool leverIsAC;
  //if lever is B
  if (lever == 1)
  {
    backToLeverTime = 0.22;
    LCD.SetBackgroundColor(FORESTGREEN);
    LCD.Clear();
    LCD.WriteRC("B", 6, 8);
    leverIsAC = false;
  }
  //if lever is A or C
  else
  {
    backToLeverTime = 0.52;
    LCD.SetBackgroundColor(PURPLE);
    LCD.Clear();
    LCD.WriteRC("C", 6, 8);
    leverIsAC = true;
  }

  Sleep(.2);

  //move back to be parallel to correct lever location
  moveRobotTime(50, backToLeverTime, forward);
  Sleep(.05);

  //face levers
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);
  
  //go forward
  //if the button is blue and lever is A or C
  if (isBlue && leverIsAC) {
    moveRobotTime(50, 1.1, forward);
  //if the button is blue and lever is B
  } else if (isBlue && !leverIsAC) {
    moveRobotTime(50, .9, forward);
  //if the button is red and lever is A or C
  } else if (!isBlue && leverIsAC) {
    moveRobotTime(50, .86, forward);
  //if the button is red and lever is B
  } else {
    moveRobotTime(50, .50, forward);  
  }

  //tread push down on lever
  tread_motor.SetPercent(-60);
  Sleep(2.9);
  tread_motor.SetPercent(0);
  Sleep(0.5);

  //turn little bit to the right
  turn(strength, 0.1, true);
  Sleep(0.2);

  tread_motor.SetPercent(-60);
  Sleep(.4);
  tread_motor.SetPercent(0);
  Sleep(0.5);

  //turn little bit to the left
  turn(strength, 0.09, false);

  //wait five seconds
  Sleep(5.1);

  //bring tread up to pull up lever
  tread_motor.SetPercent(60);
  Sleep(0.7);
  tread_motor.SetPercent(0);
  Sleep(0.2);

  //turn right a little then left
  turn(strength, 0.15, true);
  Sleep(0.3);

  //bring tread up, it is no longer needed
  tread_motor.SetPercent(40);
  Sleep(1.5);
  tread_motor.SetPercent(0);

  //turn left after
  turn(strength, 0.15, false);
  Sleep(.05);

  //go to window
  //move backward to be approximately in line with humidifier
  if (leverIsAC) {
    moveRobotTime(50, 1.1, backward);
    Sleep(.05);
  } else {
    moveRobotTime(50, 1.0, backward);
    Sleep(.05);
  }

  //turn to face humidifier
  turn(strength, NINETY_DEGREE_TURN * 0.8, false);
  Sleep(.05);

  //move to back wall to align robot straight
  moveRobotTime(50, 3.0, backward);
  Sleep(.05);

  //move forward a little bit
  moveRobotTime(50, 0.2, forward);
  Sleep(.05);

  //turn to align with table
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(.05);

  //go to table
  moveRobotTime(50, 2.0, forward);
  Sleep(.05);

  //move back a little bit
  moveRobotTime(50, 0.4, backward);
  Sleep(.05);

  //rotate 90 degrees counterclockwise
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //move back to align with wall
  moveRobotTime(50, 2.0, backward);
  Sleep(0.5);

  /*
  Window
  */

  //go forward a little bit
  moveRobotTime(50, 0.8, forward);
  Sleep(.05);

  //turn to face window
  turn(strength, FOURTYFIVE_DEGREE_TURN, false);
  Sleep(.05);

  //go forward to window
  moveRobotTime(50, 1.1, forward);
  Sleep(.05);

  //once touching handle, turn to go straight
  turn(strength, FOURTYFIVE_DEGREE_TURN, true);
  Sleep(.05);

  //backleft a little to make sure B8 is in line with handle
  moveRobotTime(50, .2, backLeft);
  Sleep(.05);

  //open window fully
  moveRobotTime(50, 0.8, forward);
  Sleep(.05);

  //move backright from window slightly
  moveRobotTime(50, .35, backRight);
  Sleep(.05);

  //go forward slightly
  moveRobotTime(50, 1.0, forward);
  Sleep(.05);

  //move backleft to window slightly
  moveRobotTime(50, .35, backLeft);
  Sleep(.05);

  //close window
  moveRobotTime(50, 1.2, backward);
  Sleep(.05);

  //go forward slightly
  moveRobotTime(50, .5, forward);
  Sleep(.05);

  //move backright from window slightly
  moveRobotTime(50, .8, backRight);
  Sleep(.05);

  //move backward to align with wall
  moveRobotTime(50, 2.0, backward);
  Sleep(.05);

  //go forward slightly
  moveRobotTime(50, .35, forward);
  Sleep(.05);

  //turn to face ramp
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //until program ends, go straight and go back right every once in a while
  //this is to hit the button to end the run
  while (true) {
    moveRobotTime(50, 5.0, forward);
    moveRobotTime(50, 0.5, backRight);
  }

  //done. woo-hoo!!!
  return 0;
}