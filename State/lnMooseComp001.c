#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    peBatt,         sensorAnalog)
#pragma config(Sensor, in2,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftAutonClip,  sensorDigitalIn)
#pragma config(Sensor, I2C_1,  rDriveEnc,      sensorNone)
#pragma config(Sensor, I2C_2,  lDriveEnc,      sensorNone)
#pragma config(Sensor, I2C_3,  liftEnc,        sensorNone)
#pragma config(Motor,  port1,           rClaw,         tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           brWheel,       tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           frWheel,       tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port4,           rLift2,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rLift1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           lLift1,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           lLift2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           flWheel,       tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port9,           blWheel,       tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          lClaw,         tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#include "includes.h"

#ifndef LN_UTILS
#define LN_UTILS

#define setDriveR(pwr) motor[frWheel] = \
	motor[brWheel] = \
	pwr

#define setDriveL(pwr) motor[flWheel] = \
	motor[blWheel] = \
	pwr

#define setLift(pwr) motor[tlLift] = \
	motor[mlLift] = \
	motor[blLift] = \
	motor[trLift] = \
	motor[mrLift] = \
	motor[brLift] = \
	pwr

#define setClaw(pwr) SensorValue[lClawPn] = \
	SensorValue[rClawPn] = \
	pwr

void setDrive(int lPwr, int rPwr) {
	setDriveL(lPwr);
	setDriveR(rPwr);
	return;
}

void throw(int timeout = 1000) {
	int timeStart = nSysTime;
	setLift(127);
	do {
		wait1Msec(20);
	} while((nSysTime - timeStart < timeout) || (SensorValue[liftEnc] < 1500));
	setClaw(-127);
	wait1Msec(100);
	setLift(0);
	setClaw(0);
	wait1Msec(20);
	setLift(-127);
	wait1Msec(500);
	setLift(0);
}

#endif


// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  //autonCt = lcdAuton();
	bStopTasksBetweenModes = false;
  startTask(battLvls);

  initPid(&LiftPid, 100, 127, .1, .001, .1);
  initPid(&DrivePidR, 100, 127, .1, .001, .1);
  initPid(&DrivePidL, 100, 127, .1, .001, .1);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	if(SensorValue[leftAutonClip])
	  leftAuton();
	else
		rightAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol() {
  int sticks[4];

	startTask(battLvls);

	while(true) {
		upPid(&LiftPid, SensorValue[liftEnc]);

		upTog(&LiftTog, (vexRT[Btn5U] ^ vexRT[Btn5D]));

		for(int i = 0; i < 4; i++)
			sticks[i] = (fabs(vexRT[i]) > 15)
				? vexRT[i]
				: 0;

		setDrive(sticks[2] + sticks[0], sticks[2] - sticks[0]);

		if(falling(&LiftTog))
			setPid(&LiftPid, SensorValue[liftEnc]);

		if(togVal(&LiftTog)) {
			if(vexRT[Btn5U])
				setLift(127);
			else
				setLift(-127);
		}

		else
			setLift(getPidPwr(&LiftPid));

		if(vexRT[Btn6U] ^ vexRT[Btn6D]) {
			if(vexRT[Btn6U])
				setClaw(127);
			else
				setClaw(-127);
		}
		else
			setClaw(0);

		wait1Msec(20);

	}
}
