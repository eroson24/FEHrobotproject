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
#include <FEHRPS.h>
#include <FEHSD.h>
#include <string.h>
#include <stdio.h>

FEHServo servo(FEHServo::Servo7); // declare servo arm

//declare bumpers
DigitalInputPin frontRightBumper(FEHIO::FEHIOPin);
DigitalInputPin frontLeftBumper(FEHIO::FEHIOPin);
DigitalInputPin backRightBumper(FEHIO::FEHIOPin);
DigitalInputPin backLeftBumper(FEHIO::FEHIOPin);

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

    //declare digital input pins on P0_0-3 for bumpers
    //switches return 1 (true) when not being pressed
    //switches return 0 (false) when being pressed
    DigitalInputPin frontRightBumper(FEHIO::P0_0);
    DigitalInputPin frontLeftBumper(FEHIO::P0_1);
    DigitalInputPin backRightBumper(FEHIO::P0_2);
    DigitalInputPin backLeftBumper(FEHIO::P0_3);

    //assign boolean values for bumpers
    bool frontRightBumpValue = frontRightBumper.Value();
    bool frontLeftBumpValue = frontLeftBumper.Value();
    bool backRightBumpValue = backRightBumper.Value();
    bool backLeftBumpValue = backLeftBumper.Value();

    //Screen is 319 pixels from left to right (x-value)
    //Screen is 239 pixels from top to bottom (y-value)
    LCD.Clear(BLUE);
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(117,120,102,35);
    LCD.WriteAt("Start",87.5,130);

    //values represent location of touch on proteus screen
    int x_pos, y_pos;
    //waits for user touch
    while (!LCD.Touch(&x_pos,&y_pos)) {
    LCD.Touch(&x_pos,&y_pos);

    //if the user hits the Start button
    if (x_pos >= 117 && x_pos <= 219 && y_pos >= 102 && y_pos <= 137)
    {
        //loop iterates 3 times for three turns
        for (int i = 0; i < 3; i++)
        {
            //robot moves forward until the front bumpers both hit the wall
            while (frontRightBumpValue != 0 && frontLeftBumpValue != 0) {
            rightMotor.SetPercent(25);
            leftMotor.SetPercent(25);
        }
        
        //when both front bumpers are pressed both wheels stop for one second
        rightMotor.SetPercent(0);
        leftMotor.SetPercent(0);
        Sleep (1.0);
        //robot moves backwards
        rightMotor.SetPercent(-10);
        leftMotor.SetPercent(-10);
        Sleep (.5);

        //tracks how many turns the robot has made
        int turnTracker = 0;

        //when the amount of turns the robot has made is even, it turns right
        if (turnTracker % 2 == 0)
        {
        rightMotor.SetPercent(-10);
        leftMotor.SetPercent(10);
        Sleep (1.0);
        }
        //when the amount of turns the robot has made is odd, it turns left
        else if (turnTracker % 2 != 0)
        {
        rightMotor.SetPercent(10);
        leftMotor.SetPercent(-10);
        Sleep (1.0);
        }
        //increment turn amount
        turnTracker++;

        //robot moves backwards until both back bumpers are pressed
        while (backRightBumpValue != 0 && backLeftBumpValue != 0)
        {
        rightMotor.SetPercent(-10);
        leftMotor.SetPercent(-10);
        }
        }
    }
}
}