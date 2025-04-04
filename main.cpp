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
    const float NINETY_DEGREE_TURN = 0.46;
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
   
  //go forward from start area
  moveRobotTime(50, 1.0, Forward);
  Sleep(.2);

  //turn to be parallel to bin
  turn(strength, FOURTYFIVE_DEGREE_TURN, false);
  Sleep(.2);

  //move to be in line with bin grips
  moveRobotTime(50, 1.1, Forward);
  Sleep(.2);

  //turn to face bin
  turn(strength, NINETY_DEGREE_TURN, false);
  Sleep(.2);

  //move to bin
  moveRobotTime(20, 2.4, Forward);
  Sleep(.2);

  //rotate bin clckwise
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);

  //move back
  moveRobotTime(20, .5, Backward);

  //reset tread
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);

   //move back
  moveRobotTime(20, .5, Forward);

  //rotate bin clckwise
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);

  //move back
  moveRobotTime(20, .5, Backward);

  //reset tread
  tread_motor.SetPercent(-50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);

  //move back
  moveRobotTime(50, .5, Forward);
  
  //rotate bin counterclockwise
  tread_motor.SetPercent(50);
  Sleep(1.5);
  tread_motor.SetPercent(0);
  Sleep(.3);

  //move back
  moveRobotTime(50, .5, Backward);

  //turn towards start
  turn(strength, NINETY_DEGREE_TURN, false);

  //move to start
  moveRobotTime(50, 1.43, Forward);

  //turn towards button
  turn(strength, FOURTYFIVE_DEGREE_TURN, true);

  //push button
  moveRobotTime(50, 1.5, Forward);

  //back up
  moveRobotTime(50, .3, Backward);


  
  
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