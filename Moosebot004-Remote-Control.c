#pragma config(Motor,  port1,           lfWheel,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lbWheel,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           aMotor,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           bMotor,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           lClaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rClaw,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           cMotor,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           dMotor,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rbWheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rfWheel,       tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Vex_Competition_Includes.c"

void standard(int pwrA, int pwrB, int s) { // Function for the standard drive of the robot.
	motor[lfWheel] = motor[lbWheel] = pwrA;
	motor[rfWheel] = motor[rbWheel] = pwrB;
	wait1Msec(s);
}
void arm(int pwr, int s) { // Function for the arm of the robot.
	motor[aMotor] = motor[bMotor] = motor[cMotor] = motor[dMotor] = pwr;
	wait1Msec(s);
}
//Bottom motors on each side are inverted. Top one is not.

void clawMovement(int pwr, int s) { // Function for the clawe of the robot.
	motor[lClaw] = pwr;
	motor[rClaw] = pwr;
	wait1Msec(s);
}

void pre_auton() { } // Function to set values before the match starts

task autonomous() { // Function that runs the autonomous program.

	clawMovement(-127, 300); // Opens the claw.
	clawMovement(0, 200); // Stops the claw.
	arm(127, 200); // Raises the arm up.
	arm(0, 350); // Stops the arm.
	arm(-127, 100); // Lowers the arm.
	arm(0, 350); // Stops the arm.
	standard(127, 127, 1400); // Moves the robot forward.
	standard(0, 0, 350); // Stops the robot.
	clawMovement(127, 950); // Closes that claw.
	clawMovement(0, 300);
	clawMovement(50, 250);
	clawMovement(0, 250);
	standard(-127, -70, 250); // Moves the robot backwards while slightly turning left.
	standard(0, 0, 200); // Stops the robot.
	clawMovement(127, 400);
	clawMovement(0, 100);
	standard(-127, -70, 250); // Moves the robot backwards while slightly turning left.
	standard(0, 0, 200); // Stops the robot.
	clawMovement(127, 400);
	clawMovement(0, 100);
	standard(-127, 127, 345); // Turns the robot left a bit.
	standard(0, 0, 200); // Stops the robot.
	standard(-127, -127, 2000); // Moves the robot backwards.
	standard(0, 0, 200); // Stops the robot.
	arm(127, 1500); // Raises the arm.
	arm(0, 200); // Stops the arm.
	clawMovement(127, 750); // Opens the claw.
	clawMovement(0, 250); // Stops the claw.
	clawMovement(-127, 750); // Closes the claw.
	clawMovement(0, 250); // Stops the 
	arm(-127, 1500); // Lowers the arm.
	arm(0, 250); // Stops the arm.

}

task usercontrol() // Function for user control.
{
	while(true) { // Loops the code until the map is over.
		motor[lfWheel] = motor[lbWheel] = vexRT[Ch3] + vexRT[Ch1]; // Formula for arcade.
		motor[rfWheel] = motor[rbWheel] = vexRT[Ch3] - vexRT[Ch1];
	if(vexRT[Btn6U] == 1) { // Checks if a button is pressed, and if so, opens the claw.
		motor[lClaw] = 127;
		motor[rClaw] = 127;
}
	else if(vexRT[Btn6D] == 1) { // Checks if a button is pressed, and if so, closes the claw.
		motor[lClaw] = -127;
		motor[rClaw] = -127;
}
	else { // Checks if no buttons are pressed, and if so, stops the claw.
	motor[lClaw] = 0;
	motor[rClaw] = 0;
}
		if(vexRT[Btn5U] == 1) { // Checks if a button is pressed, and if so, raises the arm.
			motor[aMotor] = 127;
			motor[bMotor] = 127;
			motor[cMotor] = 127;
			motor[dMotor] = 127;
	}
		else if(vexRT[Btn5D] == 1) { // Checks if a button is pressed, and if so, lowers the arm.
			motor[aMotor] = -127;
			motor[bMotor] = -127;
			motor[cMotor] = -127;
			motor[dMotor] = -127;
	}
		else { // Checks if a button is pressed, and if so, stops the arm.
			motor[aMotor] = 0;
			motor[bMotor] = 0;
			motor[cMotor] = 0;
			motor[dMotor] = 0;
	}


	}
}

void allMotorsOff() { }
void allTasksStop() { }
