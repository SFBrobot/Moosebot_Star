
void redCubeAuton() {
	deployClaw();
	setPid(&DrivePidL, 400); //Advance left drive to middle tape line
	setPid(&DrivePidR, 400); //Advance right drive to middle tape line
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 800); //Advance left drive to turn right
	setPid(&DrivePidR, 0); //Reverse right drive to turn right
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1200); //Advance left drive side to cube
	setPid(&DrivePidR, 800); //Advance right side to cube
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setClaw(true); //Grab cube
	wait1Msec(50);
	setPid(&LiftPid, 500); //Reduce resistance by lifting cube off ground
	setPid(&DrivePidL, 1600); //Advance left drive to turn right (facing away from fence)
	setPid(&DrivePidR, 400); //Reverse right drive to turn right
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setLift(upPid(&LiftPid, SensorValue[liftEnc]));
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1200); //Reverse left drive to back up to fence
	setPid(&DrivePidR, 0); //Reverse right side to back up to fence
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	throw(); //Lift arm and open claw to throw cube to far zone
	setPid(&LiftPid, 0); //Lower lift
	while(!LiftPid.bIsOnTarg) { //Wait until lift is down
		setLift(upPid(&LiftPid, SensorValue[liftEnc]);
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1800); //Advance left drive to drive to back stars
	setPid(&DrivePidR, 600); //Advance right side to drive to back stars
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setClaw(true);
	wait1Msec(50);
	setPid(&DrivePidL, 1200); //Back up to fence (left)
	setPid(&DrivePidR, 0); //back up to fence (right)
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	throw(); //Raise lift and open claw to throw stars
	setPid(&LiftPid, 0); //Lower lift
	while(!LiftPid.bIsOnTarg) { //Wait until lift is down
		setLift(upPid(&LiftPid, SensorValue[liftEnc]);
		wait1Msec(20);
	}
	setDriveL(127);
	setDriveR(127);
	wait1Msec(500);
	setDriveL(0);
	setDriveR(0);
}
