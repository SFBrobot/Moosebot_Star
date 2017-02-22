#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    peBatt,         sensorAnalog)
#pragma config(Sensor, in2,    rLine,          sensorLineFollower)
#pragma config(Sensor, in3,    mLine,          sensorLineFollower)
#pragma config(Sensor, in4,    lLine,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  lClawPn,        sensorDigitalOut)
#pragma config(Sensor, dgtl2,  rClawPn,        sensorDigitalOut)
#pragma config(Sensor, dgtl3,  lDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftEnc,        sensorQuadEncoder)
#pragma config(Motor,  port1,           frWheel,       tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight)
#pragma config(Motor,  port2,           brWheel,       tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           trLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           mrLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           brLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           tlLift,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           mlLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           blLift,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           blWheel,       tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          flWheel,       tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#include "includes.h"

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

Toggle LiftTog;

Pid LiftPid,
	DrivePidL,
	DrivePidR;

void pre_auton()
{
  //autonCt = lcdAuton();
  startTask(battLvls);

  initPid(&LiftPid, 127, .1, .001, .01);
  initPid(&DrivePidR, 127, .1, .001, .01);
  initPid(&DrivePidL, 127, .1, .001, .01);

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
  redCubeAuton();
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
  int timeLast,
  	time,
  	dt,
  	sticks[4] = { 0, 0, 0, 0 };


	startTask(battLvls);

	while(true) {
		timeLast = time;
		time = nSysTime;
		dt = time - timeLast;
		upPid(&LiftPid, SensorValue[liftEnc], dt);

		upTog(&LiftTog, (vexRT[Btn5U] ^ vexRT[Btn5D]));

		for(int i = 0; i < 4; i++)
			sticks[i] = (fabs(vexRT[i]) > 15)
				? vexRT[i]
				: 0;

		setDrive(sticks[2] + sticks[0], sticks[2] - sticks[0]);

		if(falling(&LiftTog))
			setPidTarg(&LiftPid, SensorValue[liftEnc]);

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
				setClaw(true);
			else
				setClaw(false);
		}

		wait1Msec(20);

	}
}
