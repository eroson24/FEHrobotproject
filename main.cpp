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


//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor2,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
DigitalInputPin distanceSensor(FEHIO::P3_0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts, bool rightTurn) //using encoders
{
 //Reset encoder counts
 right_encoder.ResetCounts();
 left_encoder.ResetCounts();
 //Set both motors to desired percent
 if (rightTurn) {
 right_motor.SetPercent(-25);
 left_motor.SetPercent(25);
} else {
    right_motor.SetPercent(25);
    left_motor.SetPercent(-25); 
}
 //While the average of the left and right encoder is less than counts,
 //keep running motors
 while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

 //Turn off motors
 right_motor.Stop();
 left_motor.Stop();
}

int main(void)
{

    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    move_forward(25, 450);
    
    if (distanceSensor.Value() != 0) {
        // if wall isnt detected
        while (distanceSensor.Value() != 0) 
        {
            // keep moving backwards until it is
            move_forward(25, 1);
        }
    } else { // else if wall is detected
        while (distanceSensor.Value() == 0) 
        {
            // moves forwards until it isnt
            move_forward(-25, 1);
        }
        
    }
}