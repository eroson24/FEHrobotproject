/********************************/
/*      Proteus Test Code       */
/*     OSU FEH Spring 2020      */
/*        Drew Phillips         */
/*    02/03/20  Version 3.0.1     */
/********************************/

// AM 02/03/20

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
    */

    servo.TouchCalibrate();
}