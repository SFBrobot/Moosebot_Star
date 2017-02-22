

#include "cubeAutons.h"

void deployClaw() {
	setLift(127);
	wait1Msec(400);
	setLift(0);
	wait1Msec(20);
	setLift(-127);
	wait1Msec(250);
	setLift(0);
}

void auton() {
	deployClaw();
	for(int i = 0; i < autonSteps; i++) {
		setPidTarg(&DrivePidL, autonTargs[0][i]);
		setPidTarg(&DrivePidR, autonTargs[1][i]);
		while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
			setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc], dt));
			setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc], dt));
			wait1Msec(20);
		}
	}
}
