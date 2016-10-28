#pragma config(Motor,  port1,           lfWheel,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lbWheel,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           aMotor,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           bMotor,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           cMotor,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           dMotor,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rbWheel,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rfWheel,       tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Vex_Competition_Includes.c"

void xDrive(int pwrA, int pwrB, int s) {
	motor[lfWheel] = motor[lbWheel] = pwrA;
	motor[rfWheel] = motor[rbWheel] = pwrB;
	wait1Msec(s);
}
void arm(int pwr, int s) {
	motor[aMotor] = motor[bMotor] = motor[cMotor] = motor[dMotor] = pwr;
	wait1Msec(s);
}
void pre_auton() { }

task autonomous() { 

	xDrive(63, 63, 1000);
	arm(127, 250);
	motor[claw] = 127;
	wait1Msec(250);
	xDrive(31, 31, 250);
	motor[claw] = -127;
	wait1Msec(250);
	xDrive(31, 31, 100);
	motor[claw] = 127;
	wait1Msec(250);

}

task usercontrol()
{
	while(true) {
		motor[lfWheel] = motor[lbWheel] = vexRT[Ch3] + vexRT[Ch1];
		motor[rfWheel] = motor[rbWheel] = vexRT[Ch3] - vexRT[Ch1];
		
	if(vexRT[Btn8U] == 1) {
		motor[claw] = 63;
}
	else if(vexRT[Btn8D] == 1) {
		motor[claw] = -63;
}
	else {
	motor[claw] = 0;		
}
		if(vexRT[Btn5U] == 1) {
			motor[aMotor] = 127;
			motor[bMotor] = 127;
			motor[cMotor] = 127;
			motor[dMotor] = 127;
	}
		else if(vexRT[Btn5D] == 1) {
			motor[aMotor] = -127;
			motor[bMotor] = -127;
			motor[cMotor] = -127;
			motor[dMotor] = -127;
	}
		else {
			motor[aMotor] = 0;
			motor[bMotor] = 0;
			motor[cMotor] = 0;
			motor[dMotor] = 0;
	}
	

	}
}

void allMotorsOff() { }
void allTasksStop() { }
