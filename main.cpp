/****************************************/
/*      Proteus Exploration #2          */
/*      OSU FEH Spring 2025             */
/*      Mark Oyster, Erol Sonmez,       */
/*      Reagan Massey, Austin Toczynski */
/*      02/14/2025  Version 3.0.1       */
/****************************************/

/* Include preprocessor directives */
#include <string.h>
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
#include <string.h>
#include <stdio.h>

//declare motors.
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
FEHMotor back_motor(FEHMotor::Motor2,9.0);
FEHMotor tread_motor(FEHMotor::Motor3,9.0);

DigitalInputPin distance_sensor(FEHIO::P1_0);

void moveRobot(int strength, double time, char direction[]) {

  //move forward for time
  if (strcmp(direction, "forward") == 0){
    right_motor.SetPercent(-strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }
  //move back right for time
  else if (strcmp(direction, "backRight") == 0){
    right_motor.SetPercent(strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  //move back left for time
  else if (strcmp(direction, "backLeft") == 0){
    left_motor.SetPercent(strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }
  else if (strcmp(direction, "backward") == 0){
    left_motor.SetPercent(-strength);
    right_motor.SetPercent(strength);
    Sleep(time);
  }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

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


int main(void)
{
  /*
  RCS.InitializeTouchMenu("0910B8VYV");
  int lever = RCS.GetLever();
  LCD.WriteLine(RCS.Time());
  */
 LCD.Clear();
 LCD.SetBackgroundColor(BLACK);
 LCD.SetFontColor(WHITE);
 
  int objectInRange = distance_sensor.Value();
  while (true){
    objectInRange = distance_sensor.Value();
    
    LCD.WriteLine(objectInRange);
  }

  
  // declare constants
  int strength = 60;
  double time = 2.75;
  char Forward[] = "forward";
  char Backward[] = "backward";
  float x, y;
  
  

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

