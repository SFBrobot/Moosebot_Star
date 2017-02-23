void setDriveBoth(int pwr, int time){
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

void redCubeAuton() {
	deployClaw();
	driveForDist(400, 400);
	driveForDist(800, 0);
	driveForDist(1200, 800);
	setClaw(true); //Grab cube
	wait1Msec(100);
	setPid(&LiftPid, 500); //Reduce resistance by lifting cube off ground
	driveLiftForDist(1600, 400);
	driveForDist(1200, 0);
	throw(); //Lift arm and open claw to throw cube to far zone
	setLift(-63);
	wait1Msec(250);
	setLift(0);
	driveForDist(1800, 600);
	setClaw(true);
	wait1Msec(100);
	driveForDist(1200, 0);
	throw(); //Raise lift and open claw to throw stars
	driveClaw(0);
	setDriveBoth(127, 500);
}
