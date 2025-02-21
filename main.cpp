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

//declare motors
FEHMotor vexMotor(FEHMotor::Motor0,9.0);

int main(void)
{
    float x, y; //for touch screen

    vexMotor.SetPercent(0);
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(10);
    LCD.Write("10% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(20);
    LCD.Write("20% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(30);
    LCD.Write("30% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(40);
    LCD.Write("40% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(50);
    LCD.Write("50% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(60);
    LCD.Write("60% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(70);
    LCD.Write("70% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(80);
    LCD.Write("80% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(90);
    LCD.Write("90% speed");
    while(!LCD.Touch(&x,&y));

    Sleep(1.0);
    LCD.Clear();
    vexMotor.SetPercent(100);
    LCD.Write("100% speed");
    while(!LCD.Touch(&x,&y));
    
    return 0;
}