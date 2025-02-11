/****************************************/
/*      Proteus Test Code R04_1         */
/*      OSU FEH Spring 2025             */
/*      Mark Oyster, Erol Sonmez,       */
/*      Reagan Massey, Austin Toczynski */
/*      02/03/20  Version 3.0.1         */
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

FEHServo servo(FEHServo::Servo7); // declare servo arm

//declare digital input pins on P0_0-3 for bumpers
//switches return 1 (true) when not being pressed
//switches return 0 (false) when being pressed
DigitalInputPin frontRightBumper(FEHIO::P0_0);
DigitalInputPin frontLeftBumper(FEHIO::P0_1);
DigitalInputPin backRightBumper(FEHIO::P0_2);
DigitalInputPin backLeftBumper(FEHIO::P0_3);

//declare motors
FEHMotor rightMotor(FEHMotor::Motor0,9.0);
FEHMotor leftMotor(FEHMotor::Motor1,9.0);

int main(void)
{
    /*
    // declare light sensor input pin
    AnalogInputPin CdS_cell(FEHIO::P2_0);

    // print value of light sensor to screen
    while (1) {
        LCD.Write(CdS_cell.Value());
        Sleep(300);
        LCD.Clear();
    }
    

    servo.TouchCalibrate();
    */

    //wait three seconds before beginning
    Sleep(3.0);
        
    //robot moves forward until the front bumpers both hit the wall
    rightMotor.SetPercent(25);
    leftMotor.SetPercent(25);

    // while wall hasn't been hit with both front bumpers, update bumper values
    while (frontRightBumper.Value() != 0 && frontLeftBumper.Value() != 0) {
    }
       
    //both wheels stop for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot turns on right wheel until 90 degree turn
    rightMotor.SetPercent(-20);
    Sleep(.5);

    //stop robot movement for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot moves backward until the back bumpers both hit the wall
    rightMotor.SetPercent(-25);
    leftMotor.SetPercent(-25);

    // while wall hasn't been hit with both back bumpers, update bumper values
    while (backRightBumper.Value() != 0 && backLeftBumper.Value() != 0) {
    }

    //stop robot movement for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot moves forward until the front bumpers both hit the wall
    rightMotor.SetPercent(25);
    leftMotor.SetPercent(25);

    // while wall hasn't been hit with both front bumpers, update bumper values
    while (frontRightBumper.Value() != 0 && frontLeftBumper.Value() != 0) {
    }

    //both wheels stop for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot turns on left wheel until 90 degree turn
    leftMotor.SetPercent(-20);
    Sleep(.5);

    //stop robot movement for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot moves backward until the back bumpers both hit the wall
    rightMotor.SetPercent(-25);
    leftMotor.SetPercent(-25);

    // while wall hasn't been hit with both back bumpers, update bumper values
    while (backRightBumper.Value() != 0 && backLeftBumper.Value() != 0) {
    }

    //stop robot movement for one second
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
    Sleep(1.0);

    //robot moves forward until the end of the course.
    rightMotor.SetPercent(25);
    leftMotor.SetPercent(25);

    // while wall hasn't been hit with both front bumpers, update bumper values
    while (frontRightBumper.Value() != 0 && frontLeftBumper.Value() != 0) {
    }

    // disable motors. robot has completed the course
    rightMotor.SetPercent(0);
    leftMotor.SetPercent(0);
}