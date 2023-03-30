Problem Definition 
Due to the current and ongoing Covid-19 pandemic, many otherwise populated areas have been shut down or given restricted access. Specifically with study spaces on campus, capacity limits have been set on rooms to ensure everyone is able to maintain proper social distances. Often rooms/buildings are left unlocked when they should not be in use or have reached capacity due to occupants visiting intermittently. This creates a nearly unrealistic job for staff responsible for keeping track of the change in occupancy of rooms. Our system helps with ease of use of these campus facilities for both the students and staff to lower the amount of confusion and increase the efficiency of the facility and allow staff to focus on other tasks. It should also be noted that this system is versatile enough to be applied to other areas dealing with capacity restraints in similar ways.  

Functional Description
This system will use two pressure plates and a display to monitor the capacity of the room. At both sides of the door there will be a pressure plate acting as an analog input. Depending on which one detects a weight on it first and last, it will allow the microcontroller to determine if a person has entered or exited the room. The microcontroller will keep track of the number of people in the room and compare it to a user input set by an administrator. Once the set capacity is reached, the door will lock from the outside (digital output) and also display on a sign (7 segment display) that the room has reached capacity. Additionally, an LED light above the door lock will be turned on to indicate a locked door. This will continuously run and keep updating as people come in and out. 

Assumptions:
●	Room has one entry/exit point 

Identify I/O Requirements 
This system requires two inputs and two outputs. The first input will be a user input to set the capacity of the room so the system is aware of when to activate the lock. In this case, the user will be a member of the staff (ie. custodial staff, building owner). The second input needed is a digital input for the pressure sensors located in the room by the door. The two outputs needed are the door locking mechanism and the LED display on the door which indicates that the room is full and the number of people in the room. 

Initial Software Design
1)	What initialization does your software need to perform?
The software needs to hold a counter that holds the number of people in the room. If the room is at capacity the software then needs to lock the door and display a sign that says the room is at capacity.

2)	How are your various inputs sampled? How is the data communicated to the rest of the software?
Inputs are samples from the motion sensors. This motion sensor sends digital signals that can then be read by the software. Depending on which motion sensors get triggered first and last, the software will then be able to increment or decrement the running counter.

3)	How are your various outputs computed?
Since the lock and display are digital signals, computing the output is relatively easy. Once the counter has reached the max capacity value the lock and display will turn on. 

4)	What does your software spend most of its time doing? Can it run forever?
The software spends most of its time in an infinite while loop. Every loop cycle it will check if the motion sensors have been set off, if so it will then increment or decrement the counter. The while loop is also constantly checking if the counter has reached its max capacity. 

Prototyping Plan

The prototyping plan will use 2 switch buttons to emulate the pressure plates. There are 4 possible inputs. The microcontroller will constantly check these switch buttons. Obviously, if the 2 inputs are 0 and 0, then nothing will happen. Depending on which of the 2 switch buttons are pushed first and last, a counter in the code will update. Once the counter has reached the limit set by an administrator, the door will lock from the outside and will display a message saying “FULL”. To emulate the door lock, we will light up an LED, as they are both digital outputs (on/off or unlocked/locked). The display will be the seven segment display. How success would be verified is if we can see the counter display the number of people in the room. If the first switch is pressed and then the second, we should see the seven segment display increment its value. If we see the second switch pressed and then the first, we should see the seven segment display decrease in value. For prototyping purposes we set the max capacity to 5. If the counter reaches 5 people, we should see the display say “FULL” and the LED’s to turn on. If the room is full and somebody leaves, we should see the seven segment display show the new value of people in the room and the LEDs should turn off. IF this is successful, then we have a successful prototype.
