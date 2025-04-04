/****************************************/
/*      Proteus Exploration #2          */
/*      OSU FEH Spring 2025             */
/*      Mark Oyster, Erol Sonmez,       */
/*      Reagan Massey, Austin Toczynski */
/*      02/14/2025  Version 3.0.1       */
/****************************************/

/* Include preprocessor directives */

//touch menu key: 0910B8VYV

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
    
   
    // declare constants
    float CdS_Value = 10;
    //declare optosensor variables
    float leftOpto = -1, midOpto = -1, rightOpto = -1;
    //for 25 power
    const float NINETY_DEGREE_TURN = 0.46;
    const float FOURTYFIVE_DEGREE_TURN = 0.5 * NINETY_DEGREE_TURN;
    const float MAXGRAYFLOOR = 3.3;
    
    char Forward[] = "forward";
    char Backward[] = "backward";
    char backRight[] = "backRight";
    char backLeft[] = "backLeft";
    float x, y;
    float strength = 70;
    
  //For tread: positive value is up (clockwise)  


  RCS.InitializeTouchMenu("0910B8VYV");
  Sleep(.1);
  //Start
  
  //wait until red light turns on to start
  while (CdS_Value > RED_VALUE)
  {
    CdS_Value = CdS_cell.Value();
  }

  //push start button
  moveRobotTime(20, .5, Backward);
  Sleep(.2);

  //Compost Bin
   
  //go forward from start area
  moveRobotTime(50, 1.0, Forward);
  Sleep(.05);

  //turn to be parallel to bin
  turn(strength, FOURTYFIVE_DEGREE_TURN, false);
  Sleep(.05);

  //move to be in line with bin grips
  moveRobotTime(50, 1.1, Forward);
  Sleep(.05);

  //turn to face bin
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //move to bin
  moveRobotTime(20, 2.4, Forward);
  Sleep(.05);

  //rotate bin clockwise
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move away from bin
  moveRobotTime(20, .5, Backward);
  Sleep(.05);

  //reset tread
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move to bin
  moveRobotTime(20, .5, Forward);
  Sleep(.05);

  //rotate bin clockwise
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move away from bin
  moveRobotTime(20, .5, Backward);
  Sleep(.05);

  //reset tread
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //move to bin
  moveRobotTime(50, .5, Forward);
  Sleep(.05);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.05);

  //Apple Bucket Table

  //move away from bin until center is in line with basket
  moveRobotTime(50, 2.0, Backward);
  Sleep(.05);

  //turn to face basket
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(.05);

  //lower tread motor
  tread_motor.SetPercent(-40);
  Sleep(0.5);    
  tread_motor.SetPercent(0);

  //move to basket
  moveRobotTime(50, 0.2, Forward);
  Sleep(.05);

  //bring tread motor back up with apple basket
  tread_motor.SetPercent(40);
  Sleep(1.2);
  //keep tread motor running on low power to keep apple basket up
  tread_motor.SetPercent(10);

  // go to bottom of ramp
  moveRobotTime(50, 1.0, backLeft);
  moveRobotTime(50, 3.0, Backward);
  Sleep(.05);

  // go slightly forward
  moveRobotTime(50, 0.2, Forward);
  Sleep(.05);

  // turn to face ramp
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(0.2);

  // go up ramp
  // give slightly less strength to right motor
  right_motor.SetPercent(-95);
  left_motor.SetPercent(100);
  Sleep(2.5);
  right_motor.SetPercent(0);
  left_motor.SetPercent(0);

  // use tread to put apple basket down on table
  tread_motor.SetPercent(-40);
  Sleep(0.32);
  tread_motor.SetPercent(0);

  Sleep(1.0);

  //Apple Bucket Crate

  //bring tread motor back up with apple basket
  tread_motor.SetPercent(40);
  Sleep(.5);
  //keep tread motor running on low power to keep apple basket up
  tread_motor.SetPercent(10);

  //move back left to be in line with crate
  moveRobotTime(50, .5, backLeft);
  Sleep(.05);

  //move forward to crate
  moveRobotTime(50, 2.0, Forward);
  Sleep(.05);

  // use tread to put apple basket down on table
  tread_motor.SetPercent(-40);
  Sleep(1.0);
  tread_motor.SetPercent(0);
   
  // go backwards slightly
  moveRobotTime(50, .3, Backward);
  Sleep(0.1);
 
  //put hook facing back
  tread_motor.SetPercent(60);
  Sleep(2.5);
  tread_motor.SetPercent(0);

  //Window

  //turn around
  turn(strength, NINETY_DEGREE_TURN * 2, false);
  Sleep(.05);

  //move to be in line with humidifier
  moveRobotTime(50, 1.0, Forward);
  Sleep(.05);

  //turn to face window
  turn(strength, FOURTYFIVE_DEGREE_TURN, true);
  Sleep(.05);

  //go forward to window
  moveRobotTime(50, 1.0, Forward);
  Sleep(.05);

  //once touching handle, turn to go straight
  turn(strength, FOURTYFIVE_DEGREE_TURN, true);
  Sleep(.05);

  //open window fully
  moveRobotTime(50, .5, Forward);
  Sleep(.05);

  //move backright from window slightly
  moveRobotTime(50, .2, backRight);
  Sleep(.05);

  //go forward slightly
  moveRobotTime(50, .5, Forward);
  Sleep(.05);

  //move backleft to window slightly
  moveRobotTime(50, .2, backRight);
  Sleep(.05);

  //close window
  moveRobotTime(50, .5, Backward);
  Sleep(.05);

  //go forward slightly
  moveRobotTime(50, .5, Forward);
  Sleep(.05);

  //move backright from window slightly
  moveRobotTime(50, .2, backRight);
  Sleep(.05);

  //Humidifier

  //turn to face humidifier black line
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(.05);

  //move forward
  moveRobot(30, Forward);

  //move forward until optosensors detect the black line
  while (leftOpto < MAXGRAYFLOOR && midOpto < MAXGRAYFLOOR && rightOpto < MAXGRAYFLOOR){
    leftOpto = optosensor_left.Value();
    midOpto = optosensor_middle.Value();
    rightOpto = optosensor_right.Value();
  }

  //stop when optosensors detect line
  right_motor.Stop();
  left_motor.Stop();
  Sleep(.05);

  //move forward so center of robot is over black line
  moveRobotTime(50, .3, Forward);
  Sleep(.05);

  //turn to face humidifier buttons
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //this next part will be an experiment, the robot should go backward until the middle optosensor no longer detects the black line
  //it would then go forward
  //with this method, the value for moving to be over the humidifier light should be consistent
  //there is a decent chance this will not work

  //move backward until mid opto sensor does not detect black line
  //move back
  moveRobot(30, Forward);

  //move backward until mid opto sensor does not detect black line
  while (midOpto > MAXGRAYFLOOR){
    leftOpto = optosensor_left.Value();
    midOpto = optosensor_middle.Value();
    rightOpto = optosensor_right.Value();
  }

  //stop when optosensors detect the gray floor
  right_motor.Stop();
  left_motor.Stop();
  Sleep(.05);

  //move forward to be over humidifier light
  moveRobotTime(50, 1.0, Forward);
  Sleep(.05);

  //takes average of CdS cell values
  float CdSAvg = 0;
  for (int i = 0; i <= 300; i++ ){
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
   
  if (CdSAvg <= RED_VALUE)
  {
    LCD.SetBackgroundColor(RED);
    LCD.Clear();
    LCD.WriteRC("RED", 6, 8);
    moveRobotTime(strength, .11, backRight);
  }
  else{
    LCD.SetBackgroundColor(BLUE);
    LCD.Clear();
    LCD.WriteRC("BLUE", 6, 8);
    moveRobotTime(strength, .11, backLeft);
  }
  Sleep(.5);

  //push button
  moveRobotTime(strength, .6, Forward);
  Sleep(.2);

  //Fertilizer Levers

  // Get lever from the RCS
  int lever = RCS.GetLever();
  float backToLeverTime = 0;
     
  // Check which lever to flip and display letter to screen
  if(lever == 0)
  {
    backToLeverTime = .5;
    LCD.SetBackgroundColor(CORNFLOWERBLUE);
    LCD.Clear();
    LCD.WriteRC("A", 6, 8);
  } 
  else if(lever == 1)
  {
    backToLeverTime = 1.0;
    LCD.SetBackgroundColor(FORESTGREEN);
    LCD.Clear();
    LCD.WriteRC("B", 6, 8);
  }
  else if(lever == 2)
  {
    backToLeverTime = 1.5;
    LCD.SetBackgroundColor(PURPLE);
    LCD.Clear();
    LCD.WriteRC("C", 6, 8);
  }
  Sleep(.2);

  //move back to be parallel to correct lever location
  moveRobotTime(50, backToLeverTime, Backward);
  Sleep(.05);

  //more code might need to be added for lever A since it is quite close to the wall

  //face levers
  turn(strength, NINETY_DEGREE_TURN, true);
  Sleep(.05);

  // go forward 
  moveRobotTime(50, 1.9, Forward);
  Sleep(.05);

  // turn approximately 25 degrees to face levers
  turn(strength, NINETY_DEGREE_TURN / 3.3, true);
  Sleep(.05);

  // tread push down on lever
  tread_motor.SetPercent(-60);
  Sleep(2.0);
  tread_motor.SetPercent(0);

  // turn approximately 25 degrees to move hook under lever
  turn(strength, NINETY_DEGREE_TURN / 3.3, true);
  Sleep(.05);

  // bring tread down under lever
  tread_motor.SetPercent(-40);
  Sleep(0.5);
  tread_motor.SetPercent(0);

  // turn approximately 25 degrees to face levers
  turn(strength, NINETY_DEGREE_TURN / 3.3, false);

  // wait five seconds
  Sleep(5.0);

  // bring tread up to pull up lever
  tread_motor.SetPercent(60);
  Sleep(1.2);
  tread_motor.SetPercent(0);

  // turn approximately 25 degrees to move hook under lever
  turn(strength, NINETY_DEGREE_TURN / 3.3, true);
  Sleep(.05);

  // bring tread up, it is no longer needed
  tread_motor.SetPercent(-40);
  Sleep(0.5);
  tread_motor.SetPercent(0);

  // turn approximately 50 degrees to align straight again
  turn(strength, NINETY_DEGREE_TURN / 3.3, false);
  turn(strength, NINETY_DEGREE_TURN / 3.3, false);
  Sleep(.05);

  //Go back to start

  //move backward to be approximately in line with humidifier
  moveRobotTime(50, 2.0, Backward);
  Sleep(.05);

  //turn to face humidifier
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //move to back wall to align robot straight
  moveRobotTime(50, 1.5, Backward);
  Sleep(.05);

  //move slightly forward
  moveRobotTime(50, .2, Forward);
  Sleep(.05);

  //turn to face ramp
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.05);

  //go down ramp and hit button
  moveRobotTime(50, 2.0, Forward);
  Sleep(.05);
  moveRobotTime(50, .5, Backward);

  //done; Woo-Hoo!!!

  return 0;
    
}