# FEH 1282.01H Robot Project – Team B8 🤖

<img src="/images/robot_cinematic.jpg" alt="A picture of our team's robot with trees in the background." width="600" height="600"/>

## Overview 📦

This project is the culmination of the ENGR 1282.01H honors engineering course at The Ohio State University (Spring 2025). Team B8—**Erol Sonmez**, **Reagan Massey**, **Mark Oyster**, and **Austin Toczynski**—designed, built, and programmed an autonomous robot using the [FEH Proteus Controller](https://u.osu.edu/fehproteus/) to complete a themed obstacle course simulating garden maintenance.

## Demo Video 🎥
You can see a demo video of the robot [here](https://www.youtube.com/shorts/MFslPQSs1EE)!

> _Note_: The video begins partway through the run. Missing is the initial compost bin interaction and button press. This run scored a **91/100**, with points only lost for pulling the incorrect lever and not flipping the fertilizer lever back—both bonus point tasks.

## Design 🖌️

Our robot’s standout feature is its **hexagonal chassis** and **three-wheel drive**, giving it six directions of motion, each enabled by selectively activating two wheels at a time. This design improved maneuverability and allowed us to simplify complex pathing logic.

<img src="/images/robot_initialChassis.png" alt="An initial CAD model of the hexagonal chassis, and the motors that control each of the three wheels." width=60% height=60%/>

<img src="/images/robot_directions.png" alt="A drawing showing the six different directions of movement on three axes on top of a drawing of the robot." width=60% height=60%/>

The **vertical tread mechanism** was another key innovation, allowing the robot to interact with multiple objects from the same attachment point. A **hook** mounted to the tread allowed the robot to pick up the apple basket, pull levers, and rotate the compost drum. Below you can see the initial and final models. The initial model was scrapped as using the Erector set pieces was too bulky and insecure.

<img src="/images/robot_initialTreads.png" alt="A CAD model of the initial tread design for the robot. The tread is held up using Erector set pieces." width=50% height=50%/>

<img src="/images/robot_finalTreads.png" alt="A CAD model of the final tread design for the robot. The tread is held up using two wooden panels at the sides" width=50% height=50%/>

Finally, below is a physical cardboard mockup created in the early phases of the project, as well as a rendering of the final CAD model.

<img src="/images/robot_physicalMockup.jpg" alt="A cardboard model of the robot." width=50% height=50%/>

<img src="/images/robot_finalCADrender.png" alt="A CAD model of the final model of the robot, excluding the B8 sign." width=50% height=50%/>

## Strategy ♟️

<img src="/images/robot_courseoverhead.png" alt="An overhead view of the course the robot navigates." width=80% height=80%/>
The robot navigated the course as follows:

1. **Start** at position (1) by pressing the red button.
2. **Compost bin** (2): rotated using the tread, then spun back for bonus points.
3. **Apple basket** (3): lifted using the hook, transported up the ramp, and placed on the table (8).
4. **Fertilizer button** (5): used a CdS cell to detect the correct button (red/blue) and pushed it.
5. **Lever flipping** (6): used RCS input to flip the appropriate lever. If uncertain, defaulted to lever C.
6. **Window opening/closing** (4): completed using the mounted B8 plaque.
7. **Return** to (1) and press the red button to end the run.

### Summary of Tasks & Mechanisms

| Task                       | Mechanism/Method                           |
|---------------------------|---------------------------------------------|
| Start/Stop Button         | Front wheel collision                       |
| Compost Bin Rotation      | Vertical tread mechanism                    |
| Apple Basket Pickup       | Hook on tread                               |
| Fertilizer Button Press   | CdS cell color detection + wheel press      |
| Lever Flip                | Hook on tread                               |
| Window Open/Close         | Side-mounted team plaque                    |

## Programming & Features 🔧

- **Version Control System**: It was our first experience working on an extensive and collaborative software project, and first time using **GitHub** as a version control system.
- **Sensors**: Sensors were used in the code, such as a **CdS Cell** to detect color, and **optosensors** for line following. Code was written for optosensor integration, but commented out before the competition as the hardware was faulty. 
- **Tuning & Calibration**: Extensive real-world testing was used to fine-tune encoder thresholds, light detection, and hook positioning.
- **Error Checking**: Implemented retry loops and distance checks to recover from small positional errors. We used making the robot run against different objects on the course as a way to standardize position between tasks.

## Technologies Used 💻
- **FEH Proteus Controller** – Motor and sensor interface
- **FEH Library** – Built-in functions for use with the Proteus Controller
- **C++ / Github / Visual Studio Code** – Programming the robot
- **Onshape** – CAD design of chassis and attachments

Additional documentation including electrical diagrams, port assignments, project schedule, and the final CAD drawings (.PDF) are available in the `images` folder.

## Sources 🔗
- [FEH Proteus Controller Documentation](https://u.osu.edu/fehproteus/)
- [FEH Course Materials and Guides](https://u.osu.edu/feh/)

