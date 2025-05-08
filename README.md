# FEH Robot Project – Team B8 - Autonomous Course Navigation and Task Execution

<img src="/images/robot_cinematic.jpg" alt="A picture of the team's robot with trees in the background." width="600" height="600"/>

## Overview

This project is the culmination of the ENGR 1282 honors engineering course sequence at tOSU. The team was **Erol Sonmez**, **Reagan Massey**, **Mark Oyster**, and **Austin Toczynski**.

Our team's goal was to design, build, and program a robot using the [FEH Proteus Controller](https://u.osu.edu/fehproteus/) to navigate and complete tasks an obstacle course that simulates a robot completing necessary maintenance tasks to maintain a garden.

## Demo Video 
You can see a demo video of the robot [here](https://www.youtube.com/shorts/MFslPQSs1EE)! Missing from the video is the beginning where the robot pushed the red button to start the run, navigated to the compost bin, and turned the compost bin for the first time. The video begins when the robot started turning the compost bin back. 

This is an example of a near perfect run -- a 91/100! The only points missing are for pulling the incorrect lever and for not flipping the fertilizer lever back up, both of which are secondary / bonus points. 

## Strategy

A picture of the course can be found below.

<img src="/images/robot_courseOverhead.jpg" alt="A picture of the team's robot with trees in the background." width=60% height=60%/>

Each robot begins in position (1) by pushing the red button when the red light activates. After this, our team's robot completes the task at position (2), which is spinning a compost drum. For bonus points, our team spins the compost drum back to its original position after spinning it all the way. 

Next, the robot picks up the apple basket at position (3) with the hook mechanism attached to the vertical tread of the robot, and go up the ramp. Our team had the choice between placing the basket in the crate at position (7), or the table at position (8). We chose to put the apple basket on the table.

Afterwards, the robot would go to the fertilizer buttons at position (5). By using the CdS cell to analyze what color the light by the buttons is (red or blue), the robot pushes the correct color button.

Then, the robot navigated to position (6) and flipped the correct lever of the three based on input from the RCS (Robot Communication System). Any of the levers being flipped granted the team points for the task, but flipping the correct lever granted the team bonus points. Due to time limitations and challenges with precision for this task, the team flipped the correct lever only if the lever was B or C, and otherwise defaulted to flipping C. 

Finally, the robot navigated to position (4) to open the window completely, and then close it for bonus points. Afterwards, the robot navigated back to position (1) and pushes the red button to end the run.

## Design

The thing that makes our team's robot the most unique is the hexagonal chassis, as well as the robot having three wheels. By activating any two wheels at any given time to go forward or backwards in any direction, the robot has three different axes of movement, and six different directions it can move in. Below is an initial CAD model of the chassis, as well as a visualization of the six different directions of movement and what each one was named in the code. 

<img src="/images/robot_initialChassis.jpg" alt="An initial CAD model of the team's hegagonal chassis, and the motors that control each of the three wheels." width=60% height=60%/>

<img src="/images/robot_directions.jpg" alt="A drawing showing the six different directions of movement on three axes on top of a drawing of the robot." width=60% height=60%/>

## Programming

## Features

## Technologies Used

- **FEH Proteus Controller** – Motor and sensor interface
- **C++ / Github / Visual Studio Code** – Programming the robot
- **FEH Library** – Built-in functions for use with the Proteus Controller
- **Onshape** – CAD design of chassis and attachments

## Sources


