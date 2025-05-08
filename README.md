# FEH 1282.01H Robot Project – Team B8

<img src="/images/robot_cinematic.jpg" alt="A picture of the team's robot with trees in the background." width="600" height="600"/>

## Overview

This project is the culmination of the ENGR 1282 honors engineering course sequence at tOSU. The team was **Erol Sonmez**, **Reagan Massey**, **Mark Oyster**, and **Austin Toczynski**. The robot was designed for the ENGR 1282.01H class in SP25.

Our team's goal was to design, build, and program a robot using the [FEH Proteus Controller](https://u.osu.edu/fehproteus/) to navigate and complete tasks an obstacle course that simulates a robot completing necessary maintenance tasks to maintain a garden.

## Demo Video 
You can see a demo video of the robot [here](https://www.youtube.com/shorts/MFslPQSs1EE)! Missing from the video is the beginning where the robot pushed the red button to start the run, navigated to the compost bin, and turned the compost bin for the first time. The video begins when the robot started turning the compost bin back. 

This is an example of a near perfect run, a 91/100. The only points missing are for pulling the incorrect lever and for not flipping the fertilizer lever back up, both of which are secondary / bonus points. 

## Design

The thing that makes our team's robot the most unique is the hexagonal chassis, and the robot having three wheels. By activating two wheels at any given time to go forward or backwards in any direction, the robot has three different axes of movement / six different directions it can move. Below is an initial CAD model of the chassis, as well as a visualization of the directions of movement and their names in the code.

<img src="/images/robot_initialChassis.png" alt="An initial CAD model of the team's hegagonal chassis, and the motors that control each of the three wheels." width=60% height=60%/>

<img src="/images/robot_directions.png" alt="A drawing showing the six different directions of movement on three axes on top of a drawing of the robot." width=60% height=60%/>

The vertical tread mechanism was another unique feature of the robot. This allowed us to easily interface with the friction pad of the compost drum. We decided to attach a hook to the tread mechanism which allowed us to pick up and put down the apple basket and pull the levers. The tread and hook combination allowed us to accomplish three of the five primary tasks on the course. 

Below is an initial CAD model of the tread mechanism, as well as the final CAD model. The Erector set pieces used in the initial model were too bulky and unstable, as well as an inefficient use of space.

<img src="/images/robot_initialTreads.png" alt="A CAD model of the initial tread design for the robot. The tread is held up using Erector set pieces." width=60% height=60%/>

<img src="/images/robot_finalTreads.png" alt="A CAD model of the final tread design for the robot. The tread is held up using two wooden panels at the sides" width=60% height=60%/>

Finally, below is a rendering of the final CAD model of the robot (not including the B8 sign), as well as a physical cardboard mockup created in the early phases of the project.

<img src="/images/robot_finalCADrender.png" alt="A CAD model of the final model of the robot, excluding the B8 sign." width=60% height=60%/>

<img src="/images/robot_physicalMockup.png" alt="A cardboard model of the robot." width=60% height=60%/>


## Strategy

A picture of the course can be found below.

<img src="/images/robot_courseoverhead.png" alt="An overhead view of the course the robot navigates." width=60% height=60%/>

- Each robot begins in position (1) by pushing the red button when the red light activates. After this, our team's robot completes the task at position (2), which is spinning a compost drum. For bonus points, our team spins the compost drum back to its original position after spinning it all the way. 

- Next, the robot picks up the apple basket at position (3) with the hook mechanism attached to the vertical tread of the robot, and go up the ramp. Our team had the choice between placing the basket in the crate at position (7), or the table at position (8). We chose to put the apple basket on the table.

- Afterwards, the robot would go to the fertilizer buttons at position (5). By using the CdS cell to analyze what color the light by the buttons is (red or blue), the robot pushes the correct color button.

- Then, the robot navigated to position (6) and flipped the correct lever of the three based on input from the RCS (Robot Communication System). Any of the levers being flipped granted the team points for the task, but flipping the correct lever granted the team bonus points. Due to time limitations and challenges with precision for this task, the team flipped the correct lever only if the lever was B or C, and otherwise defaulted to flipping C. 

- Finally, the robot navigated to position (4) to open the window completely, and then close it for bonus points. Afterwards, the robot navigated back to position (1) and pushes the red button to end the run.

### A summary of the tasks and how the robot accomplished them
- Pressing start / stop button: _Running into the buttons with the front wheel_
- Rotating the compost bin: _The vertical tread mechanism_
- Picking up and putting down the apple basket: _The hook attached to the tread_
- Pushing the humidifier button: _Detecting color with CdS cell, then running into correct button with the front wheel_
- Flipping the lever: _The hook attached to the tread._
- Opening / closing window: _The "B8" team plaque attached to the side of the robot_

## Programming

## Features

## Technologies Used

- **FEH Proteus Controller** – Motor and sensor interface
- **C++ / Github / Visual Studio Code** – Programming the robot
- **FEH Library** – Built-in functions for use with the Proteus Controller
- **Onshape** – CAD design of chassis and attachments

## Sources


