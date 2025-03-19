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

//function for finding actual power from proteus battery level
float actualPower(float desiredPower) {
  float batteryVoltage = Battery.Voltage();
  if (batteryVoltage > 11.5){
    batteryVoltage == 11.5;
  }
  float actualPower = ((11.5/batteryVoltage) * desiredPower);
  return actualPower;
  }
  
  //Declare CdS cell sensor
  
  
  int main(void)
  {
     AnalogInputPin CdS_cell(FEHIO::P0_0);
     
  

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
    const float NINETY_DEGREE_TURN = .35;
    const float FOURTYFIVE_DEGREE_TURN = .17;
    char Forward[] = "forward";
    char Backward[] = "backward";
    char backRight[] = "backRight";
    char backLeft[] = "backLeft";
    float x, y;
    int buttonSide = 0;
    Sleep(.1);
    float strength = 100;
    double time = .1;

   /*
   //code for testing CdS Cell lights maximums and minimums
    CdS_Value = CdS_cell.Value();
    float CdSMax = CdS_Value;
    float CdSMin = CdS_Value;
   while (1){
    CdS_Value = CdS_cell.Value();
    
    if (CdS_Value < CdSMin){
      CdSMin = CdS_Value;
    } 
    if (CdS_Value > CdSMax){
      CdSMax = CdS_Value;
    }

    LCD.WriteRC(CdS_Value,6,8);
    LCD.Write("Min: ");
    LCD.WriteLine(CdSMin);
    LCD.Write("Max: ");
    LCD.WriteLine(CdSMax);
    
    Sleep(.1);
    LCD.Clear();
   }
   */
   //Max CdsValue no light: 1.611
   //Min CdsValue no light: .737

   //Max CdsValue course blue light: 1.451
   //Min CdsValue course blue light: .711

   //Max CdsValue light blue light: 2.740
   //Min CdsValue light blue light: 1.806

   //Max CdsValue blue light: .056
   //Min CdsValue blue light: 1.456
  
    
    //wait until red light turns on to start
    while (CdS_Value > RED_VALUE)
    {
    CdS_Value = CdS_cell.Value();
    }
    
    //Turn from start area
    turn(strength, NINETY_DEGREE_TURN, true);
    Sleep(1.0);
    //move to center of ramp
    time = .2;
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);

    //turn towards ramp
    turn(strength, FOURTYFIVE_DEGREE_TURN, false);
    Sleep(1.0);
    time = 2.18;
  
    //move up ramp
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);
  
    //turn towards humidifier area
    time = NINETY_DEGREE_TURN;
    turn(strength, time, false);
    Sleep(1.0);
    
  
    //move to light sensor, stops when after .88 seconds and cds cell detects light
    right_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
    Sleep(.88);
    
    int lightTracker = 1;
    while (lightTracker == 1){
      CdS_Value = CdS_cell.Value();
      if (CdS_Value < RED_VALUE || CdS_Value > BLUE_VALUE)
    {
      LCD.WriteLine("CdS Value: ");
      LCD.WriteLine(CdS_Value);
      right_motor.Stop();
      left_motor.Stop();
      lightTracker = 0;
    }
    Sleep(.01);
    
    }
    

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
    Sleep(3.0);

    //move to be in line with correct button, display color to press on screen
    time = .11;
    if (CdSAvg <= RED_VALUE)
    {
      LCD.SetBackgroundColor(RED);
      LCD.Clear();
      LCD.WriteRC("RED", 6, 8);
      LCD.WriteRC("backRight", 8, 8);
      
      moveRobotTime(strength, time, backRight);
    }
    else{
      LCD.SetBackgroundColor(BLUE);
      LCD.Clear();
      LCD.WriteRC("BLUE", 6, 8);
      LCD.WriteRC("backLeft", 8, 8);
      moveRobotTime(strength, time, backLeft);
    }
    Sleep(1.0);
   

    //push button
    time = .6;
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);
    
    //Bonus points from here
   
    //move back to ramp
    time = 1.05;
    moveRobotTime(strength, time, Backward);
    Sleep(1.0);
  
    //turn towards ramp
    time = NINETY_DEGREE_TURN;
    turn(strength, time, false);
    Sleep(1.0);
  
    //go down ramp to start area
    time = 2.16;
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);
  
    //turn towards starting area
    //this section will make sure the robot hits the stop button if it misses the first time
    time = NINETY_DEGREE_TURN;
    turn(strength, time, true);
    Sleep(1.0);
  
    //move into starting area and press button
    time = .2;
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);
    time = NINETY_DEGREE_TURN;
    turn(strength, time, false);
    Sleep(1.0);
    time = .2;
    moveRobotTime(strength, time, Forward);
    Sleep(1.0);
    moveRobotTime(strength, time, Backward);
    Sleep(1.0);
    right_motor.Stop();
    left_motor.Stop();
    
   
/*
  RCS.InitializeTouchMenu("0910B8VYV");
  int lever = RCS.GetLever();
  LCD.WriteLine(RCS.Time());
  */

  return 0;
    
}

