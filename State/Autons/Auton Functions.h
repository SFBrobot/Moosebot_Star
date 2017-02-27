void driveForTime(int pwr, int time){
	setDriveL = setDriveR = (pwr);
	wait1Msec(time);
	setDriveL = setDriveR = 0;
}

void driveForDist(int lDist, int rDist){
	setPid(&DrivePidL, lDist); //Advance left drive to middle tape line
	setPid(&DrivePidR, rDist); //Advance right drive to middle tape line
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
}

void driveLiftForDist(int lDist, int rDist){
	setPid(&DrivePidL, lDist); //Advance left drive to turn right (facing away from fence)
	setPid(&DrivePidR, rDist); //Reverse right drive to turn right
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setLift(upPid(&LiftPid, SensorValue[liftEnc]));
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
}

void driveClaw(int claw){
	setPid(&LiftPid, 0); //Lower lift
	while(!LiftPid.bIsOnTarg) { //Wait until lift is down
		setLift(upPid(&LiftPid, SensorValue[liftEnc]);
		wait1Msec(20);
	}
}

void driveRobot(int lpwr, int rpwr, int time){
	setDriveL(lpwr);
	setDriveR(rpwr);
	wait1Msec(time);
	setDriveBoth(0);
}
