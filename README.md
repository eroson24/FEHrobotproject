# FEH Robot Project – Team B8 - Autonomous Course Navigation and Task Execution

<img src="/images/robot_cinematic.jpg" alt="A picture of the team's robot with trees in the background." width="600" height="600"/>

## Overview

This project is the culmination of the ENGR 1282 honors engineering course sequence at tOSU. The team was **Erol Sonmez**, **Reagan Massey**, **Mark Oyster**, and **Austin Toczynski**.

Our team's goal was to design, build, and program a robot using the [FEH Proteus Controller](https://u.osu.edu/fehproteus/) to navigate and complete tasks an obstacle course that simulates a robot completing necessary maintenance tasks to maintain a garden.

## Demo Video 

## Strategy

A picture of the course can be found below.

![A overhead view of the course the robot had to navigate. The locations of the tasks are numbered.](/images/robot_courseoverhead.png "Title2")

Each robot begins in position (1) by pushing the red button when the red light activates. After this, our team's robot completes the task at position (2), which is spinning a compost drum. For bonus points, our team spins the compost drum back to its original position after spinning it all the way. 

Next, the robot picks up the apple basket at position (3) with the hook mechanism attached to the vertical tread of the robot, and go up the ramp. Our team had the choice between placing the basket in the crate at position (7), or the table at position (8). We chose to put the apple basket on the table.

Afterwards, the robot would go to the fertilizer buttons at position (5). By using the CdS cell to analyze what color the light by the buttons is (red or blue), the robot pushes the correct color button.

Then, the robot navigated to position (6) and flipped the correct lever of the three based on input from the RCS (Robot Communication System). Any of the levers being flipped granted the team points for the task, but flipping the correct lever granted the team bonus points. Due to time limitations and challenges with precision for this task, the team flipped the correct lever only if the lever was B or C, and otherwise defaulted to flipping C. 

Finally, the robot navigated to position (4) to open the window completely, and then close it for bonus points. Afterwards, the robot navigated back to position (1) and pushes the red button to end the run.

## Design

## Programming

## Features

## Technologies Used

- **FEH Proteus Controller** – Motor and sensor interface
- **C++ / Github / Visual Studio Code** – Programming the robot
- **FEH Library** – Built-in functions for use with the Proteus Controller
- **Onshape** – CAD design of chassis and attachments

## Sources


