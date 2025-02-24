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
#include <string.h>
#include <stdio.h>

//declare motors.
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
FEHMotor back_motor(FEHMotor::Motor0,9.0);
FEHMotor tread_motor(FEHMotor::Motor0,9.0);

int main(void)
{
    
    
    return 0;
}


void moveRobot(int strength, double time, int direction) {
  //Reset encoder counts

  /*
  For direction:
  1 is forward
  2 is back right
  3 is back left
  */

  //move forward for time
  if (direction == 1){
    right_motor.SetPercent(strength);
    left_motor.SetPercent(strength);
    Sleep(time);
  }

  //move back right for time
  if (direction == 2){
    right_motor.SetPercent(strength);
    back_motor.SetPercent(strength);
    Sleep(time);
  }

  //move back left for time
  if (direction == 3){
    left_motor.SetPercent(strength);
    back_motor.SetPercent(strength);
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

  

